#include "PK_Box2DPhysicsManager.h"
#include "PK_Box2DBody.h"
#include "PK_Box2DRenderer.h"
#include "PK_Exceptions.h"
#include "PK_MathHelper.h"

#define DEFAULT_POS_ITERATIONS    2
#define DEFAULT_VEL_ITERATIONS    6
namespace PK {

//
PK_Box2DPhysicsManager::PK_Box2DPhysicsManager(PK_Scene &scene, const PK_String &sName) :
  PK_PhysicsManager(scene, sName)
{
    SetTypeName("PK_Box2DPhysicsManager");
    m_pWorld = new b2World(ConvertVector(m_vGravity));
    m_pContactListener = new PK_Box2DContactListener(*this);
    m_pRenderer = new PK_Box2DRenderer(*this);
    m_pWorld->SetContactListener(m_pContactListener);
    m_iPositionIterations = DEFAULT_POS_ITERATIONS;
    m_iVelocityIterations = DEFAULT_VEL_ITERATIONS;
    SetVisible(false);
}

//
PK_Box2DPhysicsManager::~PK_Box2DPhysicsManager()
{
  delete m_pWorld;
  delete m_pRenderer;
  delete m_pContactListener;
}


//
void PK_Box2DPhysicsManager::OnUpdate(const PK_GameTimer &timer)
{
    float32 fStep = (float32)timer.GetEllapsedTime() / 1000;
    m_pWorld->Step(fStep, m_iVelocityIterations, m_iPositionIterations);
}   

//
void PK_Box2DPhysicsManager::OnDraw()
{
    m_pRenderer->BeginRender();
    m_pWorld->DrawDebugData();
    m_pRenderer->EndRender();
}

//
void PK_Box2DPhysicsManager::SetVisible(bool bVisible)
{
  PK_PhysicsManager::SetVisible(bVisible);
  m_pWorld->SetDebugDraw(bVisible? m_pRenderer :  NULL);
}

//
void PK_Box2DPhysicsManager::OnBodyRemoved(PK_Body &body)
{
  PK_Box2DBody * pBody = (PK_Box2DBody *)&body;
  b2Body * b2body = pBody->GetBox2DBody();
  pBody->OnRemovedFromBox2DWorld(); 
  m_pWorld->DestroyBody(b2body);
}

// Cria um corpo apenas com uma parte (shape) na posicao e rotacao definidas
PK_Body * PK_Box2DPhysicsManager::CreateBody(const PK_String &sName, const PK_Vector2 &vPosition, PK_tBodyDefinition &bodyDefinition) 
{
    b2Body* pBody;
    b2BodyDef bodyDef;
    bodyDef.type = (bodyDefinition.bodyType == BodyType_Dynamic? b2_dynamicBody : (bodyDefinition.bodyType == BodyType_Static?  b2_staticBody : b2_kinematicBody));
    bodyDef.position.Set(EngineToB2dSystem(vPosition.x), EngineToB2dSystem(vPosition.y));
    pBody = m_pWorld->CreateBody(&bodyDef);
 
    for(PK_ListIterator(PK_t2DBodyPartDefinition) itor = bodyDefinition.bodyParts.Begin(); itor != bodyDefinition.bodyParts.End(); itor++)
    {
        PK_t2DBodyPartDefinition *pBodyPartDef = &(*itor);
   
        // Criar as shapes
        b2Shape *pShape;
        b2PolygonShape boxShape;
        b2CircleShape circleShape;
        switch(pBodyPartDef->shapeType)
        {
            case BodyPartShape_Box:
                boxShape.SetAsBox(EngineToB2dSystem(pBodyPartDef->shape.box.width) / 2, 
                                  EngineToB2dSystem(pBodyPartDef->shape.box.height) / 2, 
                                  EngineToB2dSystem(pBodyPartDef->vPivot), PK_MathHelper::DegreesToRadians(-pBodyPartDef->fRotation));
                pShape = &boxShape;
                break;

            case BodyPartShape_Circle:
                circleShape.m_p.Set(EngineToB2dSystem(pBodyPartDef->vPivot.x),
                                    EngineToB2dSystem(pBodyPartDef->vPivot.y));
                circleShape.m_radius = EngineToB2dSystem(pBodyPartDef->shape.circle.fRadius);
                pShape = &circleShape;
                break;

            default:
                throw PK_SystemException("Cannot create Physics Body because shape type '%d' is invalid.", 
                        __FILE__, __LINE__, pBodyPartDef->shapeType);
        }
    
        // Criar a fixture
        b2FixtureDef fixtureDef;
        fixtureDef.shape = pShape;
        fixtureDef.density = pBodyPartDef->fDensity;
        fixtureDef.friction = pBodyPartDef->fFriction;
        fixtureDef.restitution = pBodyPartDef->fRestitution;
        fixtureDef.filter.categoryBits = pBodyPartDef->usCollisionBit;
        fixtureDef.filter.maskBits = pBodyPartDef->usCollisionMask;
        fixtureDef.filter.groupIndex = pBodyPartDef->usCollisionGroup;

        // Criar uma fixture no body
        pBody->CreateFixture(&fixtureDef);

    }
    PK_Box2DBody * pkBody = new PK_Box2DBody(pBody, *this, sName);
    AddBody(*pkBody);
    return pkBody;
}

//
inline void PK_Box2DPhysicsManager::SetGravity(const PK_Vector2 &vGravity)
{
    PK_PhysicsManager::SetGravity(vGravity);
    m_pWorld->SetGravity(ConvertVector(vGravity));
}

// static 
PK_eBodyType PK_Box2DPhysicsManager::ConvertBodyType(b2BodyType type)
{
    switch(type)
    {
      case b2_staticBody:
        return BodyType_Static;
     
      case b2_kinematicBody:
        return BodyType_UserControlable;

      case b2_dynamicBody:
        return BodyType_Dynamic;
    }
    throw PK_SystemException("Connot convert b2BodyType '%d' to PK_eBodyType.", __FILE__, __LINE__, (int)type);
}

// static 
b2BodyType PK_Box2DPhysicsManager::ConvertBodyType(PK_eBodyType type)
{
    switch(type)
    {
      case BodyType_Static:
        return b2_staticBody;
     
      case BodyType_UserControlable:
        return b2_kinematicBody;

      case BodyType_Dynamic:
        return b2_dynamicBody;
            
      default:
        break;
    }
    throw PK_SystemException("Connot convert PK_eBodyType '%d' to b2BodyType.", __FILE__, __LINE__, (int)type);
}

// Ver bsSettings.h para explicacao
void PK_Box2DPhysicsManager::SetVelocityThreshold(float fVelocity)
{
    b2pk_Settings::m_b2_velocityThreshold = fVelocity;
}
 
} // namespace
