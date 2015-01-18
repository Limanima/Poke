#ifndef _PK_PARAMETERIZEDCALLBACK_H_
#define _PK_PARAMETERIZEDCALLBACK_H_


namespace PK {

class PK_SceneControl;
template <class PARAM>
class PK_IParameterizedCallback
{
public:
    virtual void Execute(PK_Object &sender, PARAM param) = 0;
};
    

template <class T, typename P>
class PK_ParameterizedCallback : public PK_IParameterizedCallback<P>
{
public:
   typedef void (T::*PK_ObjectCallbackMethod)(PK_Object &sender, P param);

private:
   T                 *m_pReceiver;
   P                  m_param;
   PK_ObjectCallbackMethod  m_callbackMethod;

public:
   PK_ParameterizedCallback(T &object, PK_ObjectCallbackMethod callback)
   {
       m_callbackMethod = callback;
       m_pReceiver = &object;
   }


   void operator()(PK_Object &sender, P param)
   {
      return (m_pReceiver->*m_callbackMethod)(*m_pReceiver, param);
   }

   void Execute(PK_Object &sender, P param)
   {
      return operator()(*((PK_Object *)&sender), param);
   }

};
    
} // namespace

#endif
