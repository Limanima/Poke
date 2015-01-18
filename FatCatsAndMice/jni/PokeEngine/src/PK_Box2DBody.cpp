#include "PK_Box2DBody.h"
#include "PK_Box2DPhysicsManager.h"
#include "PK_Exceptions.h"
#include "PK_2DSceneControl.h"

namespace PK {
#define MACRO_ASSERT_NOT_DISPOSED \
if (WasDisposed()) \
{ \
   throw PK_SystemException("Cannot get velocity from body because it was disposed.", __FILE__, __LINE__); \
}
     
//
PK_Box2DBody::PK_Box2DBody(b2Body *pBody, PK_Box2DPhysicsManager &manager, const PK_String &sName) :
  PK_Body(PK_Box2DPhysicsManager::ConvertBodyType(pBody->GetType()), sName)
{
  m_pBody = pBody;
  m_pManager = &manager;
} 

//
PK_Vector2 PK_Box2DBody::GetPosition()
{ 
  PK_Vector2 v;
    // FIXME
//#pragma message("SUBSTITUIR PELOS METODOS DE CONVERSAO");
  v.x = m_pBody->GetPosition().x * m_pManager->GetPixelsPerMeter();
  v.y = m_pBody->GetPosition().y * m_pManager->GetPixelsPerMeter();
  if (GetParentControl()->Get2DParent() != NULL)
  {
    v -= GetParentControl()->Get2DParent()->GetPosition();
  }
  return v; 
}

//
void PK_Box2DBody::ApplyForce(const PK_Vector2 &vForce)
{
    // FIXME
//#pragma message("CONVERTER A vForce PARA SISTEMA B2D");
    m_pBody->ApplyForceToCenter(b2Vec2(vForce.x, vForce.y), true);
}
//
void PK_Box2DBody::ApplyForce(const PK_Vector2 &vForce, const PK_Vector2 &vLocation)
{
    m_pBody->ApplyForce(b2Vec2(vForce.x, vForce.y), b2Vec2(vLocation.x, vLocation.y), true);
}

//
void PK_Box2DBody::RemoveFromSimulation()
{
  if (WasDisposed())
  {
    throw PK_SystemException("Body named '%' was already removed from simulation. m_pManager == NULL!", __FILE__, __LINE__, GetName().c_str());
  }
  SetAttachedControl(NULL);
  m_pManager->RemoveBody(*this);
}

//
void PK_Box2DBody::OnRemovedFromBox2DWorld()
{
  if (m_pManager == NULL)
  {
    throw PK_SystemException("Error in OnRemovedFromSimulation(), body name is '%s'. m_pManager == NULL!", __FILE__, __LINE__, GetName().c_str());
  }
  PK_Box2DBody *pBody = (PK_Box2DBody *)m_pBody->GetUserData();
  if (pBody != NULL)
  {
    pBody->Release();
  }

  m_pManager = NULL;
  m_pBody = NULL;
}

//
void PK_Box2DBody::OnControlAttached(PK_2DSceneControl &control)
{
  PK_Box2DBody *pBody = (PK_Box2DBody *)m_pBody->GetUserData();
  if (pBody != NULL)
  {
    pBody->Release();
  }

  m_pBody->SetUserData(this);
  this->Grab();

}

//
PK_Vector2 PK_Box2DBody::GetVelocity()
{
    MACRO_ASSERT_NOT_DISPOSED
    b2Vec2 v = m_pBody->GetLinearVelocity();
    return PK_Vector2(v.x, v.y);
}

//
float PK_Box2DBody::GetMass()
{
    MACRO_ASSERT_NOT_DISPOSED
    return m_pBody->GetMass();
}

//
void PK_Box2DBody::SetLinearDamping(float fDamping)
{
    MACRO_ASSERT_NOT_DISPOSED
    m_pBody->SetLinearDamping(fDamping);
}

void PK_Box2DBody::Rotate(float fAngle)
{
    MACRO_ASSERT_NOT_DISPOSED
    m_pBody->SetTransform(m_pBody->GetPosition(), PK_MathHelper::DegreesToRadians(fAngle));
}

// As coordenadas sao em object space, por isso temos que ter em conta a posicao do pai
void PK_Box2DBody::SetRotation(float degrees)
{
    if (GetParentControl() != NULL)
    {
        GetParentControl()->SetRotation(degrees);
    }
    degrees = PK_MathHelper::DegreesToRadians(degrees);
    m_pBody->SetTransform(m_pBody->GetPosition(), degrees);
}

// As coordenadas sao em object space, por isso temos que ter em conta a posicao do pai
void PK_Box2DBody::SetPosition(float x, float y)
{
    MACRO_ASSERT_NOT_DISPOSED
    if (GetParentControl()->Get2DParent() != NULL)
    {
      PK_Vector2 vParentPos = GetParentControl()->Get2DParent()->GetWorldPosition();
      x += vParentPos.x;
      y += vParentPos.y;
    }
    if (GetParentControl() != NULL)
    {
        GetParentControl()->SetPosition(x, y);
    }
    x = m_pManager->EngineToB2dSystem(x);
    y = m_pManager->EngineToB2dSystem(y);

    
    m_pBody->SetTransform(b2Vec2(x, y), m_pBody->GetAngle());
}

//
void PK_Box2DBody::SetWorldPosition(float x, float y)
{
    MACRO_ASSERT_NOT_DISPOSED

    x = m_pManager->EngineToB2dSystem(x);
    y = m_pManager->EngineToB2dSystem(y);

    m_pBody->SetTransform(b2Vec2(x, y), m_pBody->GetAngle());
}

// 
void PK_Box2DBody::SetCollisionMask(unsigned short uiMask, int iPartIdx)
{
    int i = 0;
    for (b2Fixture* f = m_pBody->GetFixtureList(); f; f = f->GetNext(), i++)
    {
         if (iPartIdx == i || iPartIdx == -1)
         {
             b2Filter filter = f->GetFilterData();
             filter.maskBits = uiMask;
             f->SetFilterData(filter);
             if (i !=-1)
             {
                return;
             }
         }
    }

    if (i != 1)
    {
        throw PK_SystemException("Could not set collison mask on body because the part index is out of range. Index was '%d' body name is '%s'.", 
            __FILE__, __LINE__, iPartIdx, GetName().c_str());
    }
}


} // namespace
