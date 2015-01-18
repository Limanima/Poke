#ifndef _PK_BODYCOLLISIONCALLBACK_H_
#define _PK_BODYCOLLISIONCALLBACK_H_

#include "PK_Object.h"

namespace PK {

class PK_Body;

class PK_IBodyCollisionCallback
{
public:
    virtual ~PK_IBodyCollisionCallback() {}
    virtual void Execute(PK_Body &bodyA) = 0;
};
    
template <class T>
class PK_BodyCollisionCallback : public PK_IBodyCollisionCallback
{
public:
   typedef void (T::*PK_ObjectCallbackMethod)(PK_Body &body);

private:
   T                  *m_pObject;
   PK_ObjectCallbackMethod   m_callbackMethod;

public:
   PK_BodyCollisionCallback(T &object, PK_ObjectCallbackMethod callback)
   {
      m_callbackMethod = callback;
      m_pObject = &object;
   }

   void operator()(PK_Body &body)
   {
      return (m_pObject->*m_callbackMethod)(body);
   }

   void Execute(PK_Body &body)
   {
      return operator()(body);
   }

};
    
} // namespace

#endif
