#include <PokeEngine.h>
#include "FC_Hud.h"     
#include "FC_Consts.h"

FC_Hud::FC_Hud(const PK::PK_String &sName) :
    PK::PK_Panel(sName) 
{  
    m_pGame = (FC_Game*)&PK::PokeEngine.GetGame();
    
    SetTypeName("FC_Hud");
    SetHeight(100.0f);
  //  SetBackgroundColor(0.5f, 0.3f, 0.1f, 1.0f);
    SetParentAlignment(PK::ParentAlignment_Top);
    SetPadding(0, 30, 0, 0);

    // Score
    m_pScoreLabel = new PK::PK_Label(sName + "_scoreLabel");
    m_pScoreLabel->SetFont(FCAM_ASSET_FONT_BIG);
    m_pScoreLabel->SetParentAlignment(PK::ParentAlignment_Center);
    m_pScoreLabel->SetPosition(0.0f, 0.0f);
    m_pScoreLabel->SetColor(PK_Color(PK_COLOR_RGBA_INT(50, 235, 200, 255)));
    AddControl(m_pScoreLabel);
}

//
void FC_Hud::SetScore(int iScore)
{
    m_pScoreLabel->SetText(iScore);
}

//
void FC_Hud::Refresh()
{
    SetScore(m_pGame->GetSession().GetScore());
}

//
void FC_Hud::Show()
{
    SetVisible(true);
	Refresh();
}
