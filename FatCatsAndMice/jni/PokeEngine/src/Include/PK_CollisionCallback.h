#ifndef _PK_COLLISIONCALLBACK_H_
#define _PK_COLLISIONCALLBACK_H_

#include "PK_Object.h"

namespace PK {

class PK_Body;

class PK_ICollisionCallback 
{
public:
    virtual void Execute(PK_Body &bodyA, PK_Body &bodyB) = 0;
};
    
template <class T>
class PK_CollisionCallback : public PK_ICollisionCallback
{
public:
   typedef void (T::*PK_ObjectCallbackMethod)(PK_Body &bodyA, PK_Body &bodyB);

private:
   T                  *m_pObject;
   PK_ObjectCallbackMethod   m_callbackMethod;

public:
   PK_CollisionCallback(T &object, PK_ObjectCallbackMethod callback)
   {
      m_callbackMethod = callback;
      m_pObject = &object;
   }

   void operator()(PK_Body &bodyA, PK_Body &bodyB)
   {
      return (m_pObject->*m_callbackMethod)(bodyA, bodyB);
   }

   void Execute(PK_Body &bodyA, PK_Body &bodyB)
   {
      return operator()(bodyA, bodyB);
   }

};
    
} // namespace

#endif
