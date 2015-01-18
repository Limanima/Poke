#include <PokeEngine.h>
#include "FC_ActorExit.h"     
#include "FC_Actor.h"     
       
// 
FC_ActorExit::FC_ActorExit(const PK::PK_String &sName, FC_eSide side) :
    PK::PK_2DSceneControl(sName)
{     
    SetTypeName("FC_ActorExit");
    int sign = (side == Side_Right? 1 : -1);
    m_Side = side;
    m_pLastActorToExit = NULL;
    SetSize(180.0f, (float)PK::PokeEngine.GetRenderManager().GetFrame().size.h);
    SetPosition(((PK::PokeEngine.GetRenderManager().GetFrame().size.w / 2) + 80.0f) * sign, 0.0f);
   // SetBackgroundColor(PK_COLOR_GREEN);
 
    // Limite do ecran - serve para matar logo o gato/rato quando bate 
    m_pPnlBound = new PK::PK_Panel("pnl_Bound");
    m_pPnlBound->SetSize(20.0f, (float)PK::PokeEngine.GetRenderManager().GetFrame().size.h);
    m_pPnlBound->SetPosition(-70.0f * sign, 0.0f);
   // m_pPnlBound->SetBackgroundColor(PK_COLOR_RED);
    PK::PK_t2DBodyPartDefinition bodyPartDef;
    bodyPartDef.SetToBox(m_pPnlBound->GetSize(), m_pPnlBound->GetPivot());
    bodyPartDef.usCollisionMask = 0x0;
    PK::PK_tBodyDefinition bodyDef;
    bodyDef.bodyParts.Add(bodyPartDef);
    bodyDef.bodyType = PK::BodyType_Static;
    m_pPnlBound->SetBodyDefinition(bodyDef);
    m_pPnlBound->SetWithPhysics(true, PK::BodyType_Static);
    m_pPnlBound->OnBodyCollision.Set(new PK::PK_BodyCollisionCallback<FC_ActorExit>(*this, &FC_ActorExit::Bound_Collision));
    AddControl(m_pPnlBound); 

    // Area de saida - fica mais para a esquerda/direita ja para fora do ecran
    // quando um gato/rato bate aqui, ganha o ponto
    m_pPnlExit = new PK::PK_Panel("pnl_Bound");
    m_pPnlExit->SetSize(20.0f, PK::PokeEngine.GetRenderManager().GetFrame().size.h);
    m_pPnlExit->SetPosition(70.0f * sign, 0.0f);
    //m_pPnlExit->SetBackgroundColor(PK_COLOR_YELLOW);
    m_pPnlExit->SetBodyDefinition(PK::BodyType_Static, PK::ControlBodyShapeMode_Autoadjust);
    m_pPnlExit->SetWithPhysics(true, PK::BodyType_Static);
    m_pPnlExit->OnBodyCollision.Set(new PK::PK_BodyCollisionCallback<FC_ActorExit>(*this, &FC_ActorExit::Exit_Collision));
    AddControl(m_pPnlExit);   
}

//
void FC_ActorExit::OnInitialize()
{
    m_pLastActorToExit = NULL;
}

//
void FC_ActorExit::SetActorAccepted(FC_eActorType actorAccepted)
{
    m_ActorAccepted = actorAccepted;
    m_pPnlBound->GetBody()->SetCollisionMask(~(FC_Actor::GetActorCollisionBit(actorAccepted) | FCAMP_COLLISIONBIT_DOG));
}

//
void FC_ActorExit::Bound_Collision(PK::PK_Body &body)
{
    PK_2DSceneControl *pControl = body.GetParentControl();
    switch(pControl->GetTag())
    {      
        case ObjectType_Actor:
            FC_Actor *pActor = (FC_Actor *)pControl;
            pActor->Kill(m_Side == Side_Left? FCAM_JUMP_DIRECTION_RIGHT : FCAM_JUMP_DIRECTION_LEFT, true);
            break;
    }
}

//
void FC_ActorExit::Exit_Collision(PK::PK_Body &body)
{
    PK_2DSceneControl *pControl = body.GetParentControl();
    switch(pControl->GetTag())
    {      
        case ObjectType_Actor:
            m_pLastActorToExit = (FC_Actor*)pControl;
            if (OnActorExited.HasCallback())
            {
                OnActorExited->Execute(*this);
            }
            break;
    }
}

