#ifndef _PK_MESSAGEBOXCALLBACK_H_
#define _PK_MESSAGEBOXCALLBACK_H_

#include "PK_Object.h"
#include "PK_Types.h"
#include "PK_Callback.h"

namespace PK {

class PK_Body;

class PK_IMessageBoxCallback
{
public:
    virtual ~PK_IMessageBoxCallback() {}
    virtual void Execute(PK_eMsgBoxResult res) = 0;
};
    
template <class T>
class PK_MessageBoxCallback : public PK_IMessageBoxCallback
{
public:
   typedef void (T::*PK_MsgBoxCallbackMethod)(PK_eMsgBoxResult res);
   typedef void (*PK_MsgBoxCallbackMethod_Static)(PK_eMsgBoxResult res);

private:
   T                  *m_pObject;
   PK_MsgBoxCallbackMethod          m_callbackMethod;
   PK_MsgBoxCallbackMethod_Static   m_callbackMethod_static;
public:
   PK_MessageBoxCallback(T &object, PK_MsgBoxCallbackMethod callback)
   {
      m_callbackMethod = callback;
      m_pObject = &object;
   }   
   
   PK_MessageBoxCallback(PK_MsgBoxCallbackMethod_Static callback)
   {
      m_callbackMethod_static = callback;
      m_pObject = NULL;
   }

   void operator()(PK_eMsgBoxResult res)
   {
       if (m_pObject != NULL)
       {
            return (m_pObject->*m_callbackMethod)(res);
       }

       return (*m_callbackMethod_static)(res);
   }

   void Execute(PK_eMsgBoxResult res)
   {
      return operator()(res);
   }

};
    
} // namespace

#endif
