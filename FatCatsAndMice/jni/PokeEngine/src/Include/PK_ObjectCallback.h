#ifndef _PK_OBJECTCALLBACK_H_
#define _PK_OBJECTCALLBACK_H_

#include "PK_Object.h"

namespace PK {
  
class PK_IObjectCallback
{
public:
    virtual void Execute(PK_Object &sender) = 0;
    virtual ~PK_IObjectCallback() {}
};
    

template <class T>
class PK_ObjectCallback : public PK_IObjectCallback
{
public:
   typedef void (T::*PK_ObjectCallbackMethod)(PK_Object &sender);

private:
   T                 *m_pObject;
   PK_ObjectCallbackMethod  m_callbackMethod;

public:
   PK_ObjectCallback(T &object, PK_ObjectCallbackMethod callback)
   {
      m_callbackMethod = callback;
      m_pObject = &object;
   }

   void operator()(PK_Object &control)
   {
      return (m_pObject->*m_callbackMethod)(control);
   }

   void Execute(PK_Object &sender)
   {
      return operator()(*((PK_Object *)&sender));
   }

};
    
} // namespace

#endif
