#include <PokeEngine.h>
#include "FC_Actor.h"     
#include "FC_Consts.h"            
#include "FC_TypeConverters.h"   
#include "FC_GameplayScene.h" 

//  
FC_Actor::FC_Actor(FC_eActorType type) :
    PK::PK_Sprite(FC_TypeConverters::ActorTypeToStr(type))
{  
    m_ActorType = type;
    SetTag(ObjectType_Actor); 
    SetSize(120, 120);
 
    // Definicao do corpo fisico
    SetupPhysics();

    SetShadow(true, PK_Vector2(30.0f, -30.0f), FCAM_SHADOW_COLOR);

    m_State = ActorState_None;
    m_fAirResistance = 0;
    m_PlayerCommand = ActorCommand_None;

}


//
void FC_Actor::OnLoad()
{
    if (m_sBodySpriteAssetName.length() > 0)
    {
        SetSprite(PK::PokeEngine.GetAssetManager().LoadSprite(m_sBodySpriteAssetName, GetAssetContainerName()));
    }
}


//
void FC_Actor::Copy(PK::PK_SceneControl &copyFrom)
{
    FC_Actor *pActor = (FC_Actor *)&copyFrom;

    m_ActorType = pActor->m_ActorType;
    m_State = pActor->m_State;
    m_PlayerCommand = pActor->m_PlayerCommand;
    m_bCanBeControlled = pActor->m_bCanBeControlled ;
    m_fAirResistance = pActor->m_fAirResistance;
    m_sBodySpriteAssetName = pActor->m_sBodySpriteAssetName;
    PK::PK_Sprite::Copy(copyFrom);
}
 
//
void FC_Actor::OnUpdate(const PK::PK_GameTimer &time) 
{ 
  switch(m_State)
  {
    case ActorState_Falling:
        ProcessFalling(time);
        break;

    case ActorState_GoingLeft:
        ProcessGoingLeft(time);
        break;
         
    case ActorState_GoingRight:
        ProcessGoingRight(time);
        break;

    case ActorState_Killed:
        {
            PK::PK_tSize res = PK::PokeEngine.GetSettings().GetGameResolution();
            if (GetPosition().y < -(res.h / 2) - 150.0f) // +150 para sair totalmente do ecran
            {
                RemoveFromScene();
            }
        }
        break;    
    default:
      break;
  }
}

//
void FC_Actor::OnMessageReceived(PK::PK_tMessage1 &msg)
{
    if(msg.uiMsg == FCAM_MSG_GAMEOVER)
    {
        RemoveFromScene();
    }
}
//
void FC_Actor::ProcessFalling(const PK::PK_GameTimer &time)
{
    GetBody()->SetLinearDamping(m_fAirResistance);
    // se sair do ecran pela parte de baixo, em principio e porque e um cao,
    // basta retirar do jogo
    if (GetPosition().y < -(PK::PokeEngine.GetRenderManager().GetFrame().size.h / 2) - GetHeight() / 2)
    {
        RemoveFromScene();
    }
}

//
void FC_Actor::ProcessGoingLeft(const PK::PK_GameTimer &time)
{
    PK_Vector2 v = GetBody()->GetVelocity();
    float fGravity = -GetPhysicsManager()->GetGravity().y;
    ApplyForce(PK_Vector2(-FC_Game::GetInstance().GetSettings().GetSidewaySpeed(), -v.y * fGravity * GetBody()->GetMass()));
}

//
void FC_Actor::ProcessGoingRight(const PK::PK_GameTimer &time)
{
    PK_Vector2 v = GetBody()->GetVelocity();
    float fGravity = -GetPhysicsManager()->GetGravity().y;
    ApplyForce(PK_Vector2(FC_Game::GetInstance().GetSettings().GetSidewaySpeed(), -v.y * fGravity * GetBody()->GetMass()));

}

//
void FC_Actor::MoveLeft()
{
    if (m_State == ActorState_GoingLeft)
    {
        return;
    }
    m_State = ActorState_GoingLeft;
    GetBody()->SetLinearDamping(0.0f);
    FC_Game::GetInstance().PlaySound(FCAMP_SND_ACTOR_MOVE_IDX);
}

//
void FC_Actor::MoveRight()
{
    if (m_State == ActorState_GoingRight)
    {
        return;
    }
    m_State = ActorState_GoingRight;
    GetBody()->SetLinearDamping(0.0f);
    FC_Game::GetInstance().PlaySound(FCAMP_SND_ACTOR_MOVE_IDX);
}
 
//
void FC_Actor::Kill(bool bPlaySound)
{
    Kill(FCAM_JUMP_DIRECTION_RANDOM, bPlaySound);
}

// jumpDirection = -1 left, 1 right
void FC_Actor::Kill(int iJumpDirection, bool playSound)
{
 #ifdef DEBUG
    if (IsDead())
    {
        throw PK::PK_GameException("Cannot kill the same object twice!", __FILE__, __LINE__);
    }
#endif

    m_State = ActorState_Killed;

    if (OnKilled.HasCallback())
    {
        OnKilled->Execute(*this);
    }
       
    if (iJumpDirection == FCAM_JUMP_DIRECTION_RANDOM)
    {
        iJumpDirection = (PK::PK_RandomGenerator::GetRandNumber(2) == 0? FCAM_JUMP_DIRECTION_LEFT : FCAM_JUMP_DIRECTION_RIGHT);
    }
    // Removemos do box2d, ja nao e necessario
    if (HasBody())
    {
        DettachFromBody();
    }
    // Randomizamos para a parabola n ser sempre igual 
    float forceX = (float)(10 + PK::PK_RandomGenerator::GetRandNumber(25));
    float forceY = (float)(70 + PK::PK_RandomGenerator::GetRandNumber(50));
    // Puxamos um pouco pela gravidade para dar uma saida rapida
    PK::PK_MotionEffect *m = new PK::PK_MotionEffect(GetName() + "gravity", -20.0f, PK_Vector3(forceX * iJumpDirection, forceY, 0.0f));
    AddEffect(*m); 
    OnKill();
    if (playSound)
    {
        switch(GetActorType())
        {
            case ActorType_Cat:
                FC_Game::GetInstance().PlaySound(FCAMP_SND_CAT_DEATH_IDX);
                break;

            case ActorType_Mouse:
                FC_Game::GetInstance().PlaySound(FCAMP_SND_MOUSE_DEATH_IDX);
                break;
            default:
                break;
        }
    }
}
 
//
void FC_Actor::SetToFalling(float fAirResistance)
{
    m_State = ActorState_Falling;
    m_fAirResistance = fAirResistance;
} 
 
//
bool FC_Actor::CanBeControlled()
{
    // Se o actor ja estiver abaixo da parte de entrada inferior, ja nao pode ser controlado
    FC_GameplayScene *pScene = (FC_GameplayScene *)GetScene();
    if (GetPosition().y < pScene->GetTopDogHouseBound() || // se ja entrou na zona dos caes
        GetPosition().y > 512.0f) // se ainda n entrou no ecran
    {
        return false;
    }
 
    return (m_State == ActorState_Falling); 
}
  
//
void FC_Actor::SetupPhysics()
{   
    PK::PK_t2DBodyPartDefinition bodyPartDef;
    bodyPartDef.SetToCircle(50.0f);
    bodyPartDef.fDensity = 0.1f;
    bodyPartDef.fFriction = 0.0f;
    bodyPartDef.usCollisionBit = FC_Actor::GetActorCollisionBit(m_ActorType);
    bodyPartDef.usCollisionGroup = 2;
    PK::PK_tBodyDefinition bodyDef;
    bodyDef.bodyParts.Add(bodyPartDef);
    bodyDef.bodyType = PK::BodyType_Dynamic;
    bodyDef.shapeMode = PK::ControlBodyShapeMode_UserDefined;
    SetBodyDefinition(bodyDef);
    SetWithPhysics(true);
}

//
unsigned int FC_Actor::GetActorCollisionBit(FC_eActorType actorType)
{
    switch(actorType)
    {
        case ActorType_Cat:
            return FCAMP_COLLISIONBIT_CAT;
        case ActorType_Mouse:
            return FCAMP_COLLISIONBIT_MOUSE;
        case ActorType_Dog:
            return FCAMP_COLLISIONBIT_DOG;
        case ActorType_Object:
            return FCAMP_COLLISIONBIT_OBJECT;
        default:
            throw PK::PK_GameException("Invalid actor tupe '%d'", __FILE__, __LINE__, actorType);
    }
}
