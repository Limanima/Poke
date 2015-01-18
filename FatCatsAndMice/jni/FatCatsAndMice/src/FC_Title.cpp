#include <PokeEngine.h>
#include "FC_Title.h"     
#include "FC_Consts.h"
#include "FC_Game.h"

FC_Title::FC_Title(const PK::PK_String &sName) :
    PK::PK_Panel(sName)
{  
    //SetSpriteAssetName(FCAM_SPRITESET_TITLE);
    //SetShowEffect(new PK::PK_ColorEffect("btnColorFx", PK_COLOR_TRANSPARENT, PK_COLOR_WHITE, 1.0f, false, PK_COLOR_WHITE));
	//SetWithPhysics(true);
  
	// Letras
	m_pLetteringPnl = new PK::PK_Panel(sName + "_lettering");
	m_pLetteringPnl->SetBackgroundImage(FCAM_SPRITESET_TITLE);
    m_pLetteringPnl->SetBackgroundImageFitMode(PK::ImageSizeMode_SizeControlToImage);
    m_pLetteringPnl->SetPosition(0.0f, 900.0f);
    PK::PK_t2DBodyPartDefinition bodyPartDef;
    bodyPartDef.SetToBox(PK::PK_tSize(100.0f, 100.0f), PK_Vector2(0.0f, 0.0f));
    bodyPartDef.fDensity = 1.0f;
    bodyPartDef.fFriction = 1.0f;
    bodyPartDef.fRestitution = 0.3f;
    PK::PK_tBodyDefinition bodyDef;
    bodyDef.bodyParts.Add(bodyPartDef);
    bodyDef.bodyType = PK::BodyType_Dynamic;
    bodyDef.shapeMode = PK::ControlBodyShapeMode_UserDefined;
    m_pLetteringPnl->SetBodyDefinition(bodyDef);
    m_pLetteringPnl->SetWithPhysics(true);
    m_pLetteringPnl->OnBodyCollision.Set(new PK::PK_BodyCollisionCallback<FC_Title>(*this, &FC_Title::Collided));
 	AddControl(m_pLetteringPnl);

	// Dummy floor 
	m_pFloorPnl = new PK::PK_Panel(sName + "_dummyFloor");
    m_pFloorPnl->SetSize(768.0f, 20.0f);
    m_pFloorPnl->SetPosition(0.0f, 80.0f);
    bodyPartDef.SetToBox(PK::PK_tSize(768.0f, 20.0f), PK_Vector2(0.0f, 0.0f));
    bodyPartDef.fDensity = 1.0f;
    bodyPartDef.fFriction = 1.0f;
    bodyPartDef.fRestitution = 0.0f;
    bodyDef.bodyParts.Clear();
    bodyDef.bodyParts.Add(bodyPartDef);
    bodyDef.bodyType = PK::BodyType_Static;
    bodyDef.shapeMode = PK::ControlBodyShapeMode_UserDefined;
    m_pFloorPnl->SetBodyDefinition(bodyDef);
    m_pFloorPnl->SetWithPhysics(true, PK::BodyType_Static);
  	AddControl(m_pFloorPnl);
    
    m_ScoreSoundPlayed = false;
}
 
//
void FC_Title::OnInitialize()
{ 
    if (PK::PokeEngine.GetRenderManager().GetSafeFrame().size.w - m_pLetteringPnl->GetSize().w < 80.0f)
    {
        float w = PK::PokeEngine.GetRenderManager().GetSafeFrame().size.w - 80.0f;
        float scale = w * 1.0f / m_pLetteringPnl->GetSize().w; 
        SetScale(scale);
    }
}

void FC_Title::Dismiss()
{
    m_pFloorPnl->SetWithPhysics(false);
    FC_Game::GetInstance().PlaySound(FCAMP_SND_TITLE_EXIT_IDX);
}
   
//
void FC_Title::Show()
{
    SetVisible(true);
    m_ScoreSoundPlayed = false;
}

//
void FC_Title::Collided(PK::PK_Body &body)
{
    if (!m_ScoreSoundPlayed)
    {
        FC_Game::GetInstance().PlaySound(FCAMP_SND_TITLE_ENTRANCE_IDX);
        m_ScoreSoundPlayed = true;
    }
}
