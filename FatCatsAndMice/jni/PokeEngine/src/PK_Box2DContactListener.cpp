#include "PK_Box2DContactListener.h"
#include "PK_PhysicsManager.h"
#include "PK_Body.h"
#include "PK_Scene.h"

namespace PK {

//
PK_Box2DContactListener::PK_Box2DContactListener(PK_PhysicsManager &manager)
{
  m_pManager = &manager;
} 

//
void PK_Box2DContactListener::BeginContact(b2Contact* contact)
{
  PK_Body * pBodyA = (PK_Body *) contact->GetFixtureA()->GetBody()->GetUserData();
  PK_Body * pBodyB = (PK_Body *) contact->GetFixtureB()->GetBody()->GetUserData();

  PK_tMessage msg;
  msg.uiType = PK_MSG_BODY_COLLISION;
  msg.detail.bodyCollision.pBodyA = pBodyA;
  msg.detail.bodyCollision.pBodyA->Grab();
  msg.detail.bodyCollision.pBodyB = pBodyB;
  msg.detail.bodyCollision.pBodyB->Grab();
  m_pManager->GetScene().AddPostUpdateMessage(msg);
}

//
void PK_Box2DContactListener::EndContact(b2Contact* contact)
{
}

} // namespace
