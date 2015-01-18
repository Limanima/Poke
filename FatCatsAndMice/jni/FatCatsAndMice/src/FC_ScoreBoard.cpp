#include <PokeEngine.h>
#include "FC_ScoreBoard.h"     
#include "FC_Consts.h"
#include "FC_Stars.h"
#include "FC_Game.h"

//
FC_ScoreBoard::FC_ScoreBoard(const PK::PK_String &sName) :
    PK::PK_2DSceneControl(sName)
{  
    SetTypeName("FC_ScoreBoard");
    SetSize(500.0f, 150.0f);
    m_bHighscoreBeaten = false;
   // SetBackgroundColor(PK_Color(0.0f, 0.0f, 0.0f, 0.5f));

    m_pContainer = new PK::PK_Panel();
    m_pContainer->SetBackgroundImage(FCAM_SPRITE_SCOREBOARD);
    m_pContainer->SetBackgroundImageFitMode(PK::ImageSizeMode_RealSize);
	m_pContainer->SetBackgroundColor(PK_COLOR_GREEN);
    PK::PK_t2DBodyPartDefinition bodyPartDef;
    bodyPartDef.SetToBox(PK::PK_tSize(100.0f, 100.0f), PK_Vector2(0.0f, 0.0f));
    bodyPartDef.fDensity = 1.0f;
    bodyPartDef.fFriction = 1.0f;
    bodyPartDef.fRestitution = 0.3f;
    PK::PK_tBodyDefinition bodyDef;
    bodyDef.bodyParts.Add(bodyPartDef);
    bodyDef.bodyType = PK::BodyType_Dynamic;
    bodyDef.shapeMode = PK::ControlBodyShapeMode_UserDefined;
    m_pContainer->SetBodyDefinition(bodyDef);
    m_pContainer->SetWithPhysics(true);
    m_pContainer->OnBodyCollision.Set(new PK::PK_BodyCollisionCallback<FC_ScoreBoard>(*this, &FC_ScoreBoard::ScoreBoardCollided));

    AddControl(m_pContainer);

    // Score label
    m_pScoreLabel = new PK::PK_Label(sName + "_scoreLabel", FCAM_TEXT_SCORE);
    m_pScoreLabel->SetFont(FCAM_ASSET_FONT_DEFAULT);
    m_pScoreLabel->SetPosition(0.0f, 100.0f);
    m_pScoreLabel->SetColor(PK_Color(1.0f, 1.0f, 0.0f, 1.0f));
    m_pContainer->AddControl(m_pScoreLabel);
     
    // Score value
    m_pScoreValLabel = new PK::PK_Label(sName + "_scoreValLabel");
    m_pScoreValLabel->SetFont(FCAM_ASSET_FONT_DEFAULT);
    m_pScoreValLabel->SetPosition(0.0f, 20.0f);
    m_pScoreValLabel->SetColor(PK_Color(0.9f, 0.6f, 0.15f, 1.0f));
    m_pContainer->AddControl(m_pScoreValLabel);

    // new Highscore
    m_pHighScoreLbl = new PK::PK_Label(sName + "_newHighScoreLbl", FCAM_TEXT_NEW_HIGHSCORE);
    m_pHighScoreLbl->SetFont(FCAM_ASSET_FONT_DEFAULT);
    m_pHighScoreLbl->SetPosition(0.0f, -60.0f);
    m_pHighScoreLbl->SetColor(PK_COLOR_WHITE);
    m_pHighScoreLbl->SetScale(0.7f, 0.7f);
    m_pContainer->AddControl(m_pHighScoreLbl);
    
    // Highscore label
    m_pHiScoreLabel = new PK::PK_Label(sName + "_hiScoreLbl", FCAM_TEXT_HIGHSCORE);
    m_pHiScoreLabel->SetFont(FCAM_ASSET_FONT_DEFAULT);
    m_pHiScoreLabel->SetPosition(0.0f, -50.0f);
    m_pHiScoreLabel->SetColor(m_pScoreLabel->GetColor());
    m_pHiScoreLabel->SetScale(0.7f, 0.7f);
    m_pContainer->AddControl(m_pHiScoreLabel);
     
    // Highscore value
    m_pHiScoreValLabel = new PK::PK_Label(sName + "_hiScoreValLabel");
    m_pHiScoreValLabel->SetFont(FCAM_ASSET_FONT_DEFAULT);
    m_pHiScoreValLabel->SetPosition(0.0f, -110.0f);
    m_pHiScoreValLabel->SetColor(m_pScoreValLabel->GetColor());
    m_pHiScoreValLabel->SetScale(0.7f, 0.7f);
    m_pContainer->AddControl(m_pHiScoreValLabel);
    
    // Dummy floor
	m_pFloorPnl = new PK::PK_Panel(sName + "_dummyFloor");
    m_pFloorPnl->SetSize(768.0f, 20.0f);
    m_pFloorPnl->SetPosition(0.0f, 0.0f);
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

    // Stars
    m_pStars = new FC_Stars();
    m_pStars->SetVisible(false);
    m_pStars->SetEnabled(false);
   
    AddControl(m_pStars);
}

//
void FC_ScoreBoard::Show(int iScore, int iHighscore, bool bHighscoreBeaten)
{
    m_pContainer->SetRotation(0); // por causa de um bug que as vezes poe o scoreboard na vertical
    SetVisible(true);
    SetScore(iScore);
    SetHighScore(iHighscore);
    SetToFalling();
    m_pStars->SetVisible(false);
    m_pStars->SetEnabled(false);
    m_pHighScoreLbl->SetVisible(false);
    m_bHighscoreBeaten = bHighscoreBeaten;
    m_pHiScoreLabel->SetVisible(!m_bHighscoreBeaten);
    m_pHiScoreValLabel->SetVisible(!m_bHighscoreBeaten);
    m_ScoreSoundPlayed = false;
}

//
void FC_ScoreBoard::SetScore(int iScore)
{
    m_pScoreValLabel->SetText(iScore);
}

//
void FC_ScoreBoard::SetHighScore(int iHighscore)
{
    m_pHiScoreValLabel->SetText(iHighscore);
}

//
void FC_ScoreBoard::SetVisible(bool bVisible)
{
    PK_2DSceneControl::SetVisible(bVisible);
    m_pContainer->SetWithPhysics(bVisible, PK::BodyType_Dynamic);
    m_pFloorPnl->SetWithPhysics(bVisible, PK::BodyType_Static);
}

//
void FC_ScoreBoard::SetToFalling()
{
    m_pContainer->GetBody()->SetPosition(0.0f, 900.0f);
    m_pContainer->SetWithPhysics(true, PK::BodyType_Dynamic);
    m_pFloorPnl->SetWithPhysics(true, PK::BodyType_Static);
}

void FC_ScoreBoard::Dismiss()
{
    m_pFloorPnl->SetWithPhysics(false);
//    m_pContainer->ApplyForce(PK_Vector2(0.0f, -500.0f));
    FC_Game::GetInstance().PlaySound(FCAMP_SND_TITLE_EXIT_IDX);
}

//
void FC_ScoreBoard::ShowStars()
{
   m_pStars->SetVisible(true);
   m_pStars->SetEnabled(true);
   m_pHighScoreLbl->SetVisible(true);
   m_pStars->Show();
}

//
void FC_ScoreBoard::ScoreBoardCollided(PK::PK_Body &body)
{
    if (!m_ScoreSoundPlayed)
    {
        FC_Game::GetInstance().PlaySound(FCAMP_SND_TITLE_ENTRANCE_IDX);
        m_ScoreSoundPlayed = true;
    }
    if (!m_bHighscoreBeaten || m_pStars->IsVisible() == true)
    {
        return;
    }
    ShowStars();
}

