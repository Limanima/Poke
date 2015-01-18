#include <PokeEngine.h>
#include "FC_Consts.h"   
#include "FC_MainMenuScene.h"              
#include "FC_CatActor.h"   
#include "FC_GamePlayScene.h" 
#include "FC_ScoreBoard.h" 
                 
//  
FC_MainMenuScene::FC_MainMenuScene() :
    FC_BaseScene("fc_gameMainScene")
{
    SetTypeName("FC_MainMenuScene");

    SetWithPhysics(true);
    GetPhysicsManager()->SetGravity(PK_Vector2(0.0f, -25.0f));
  //  GetPhysicsManager()->SetVisible(true);
  
    // Titulo
    m_pTitle = new FC_Title(GetName() + "_gameTitle");
	AddControl(m_pTitle);
	 
    // Score board
    m_pScoreBoard = new FC_ScoreBoard(GetName() + "_scoreboard");
    AddControl(m_pScoreBoard);
     
    m_pTimer = new PK::PK_TimerControl(GetName() + "_timer", 1750, false, false);
    m_pTimer->OnTimer.Set(new PK::PK_ObjectCallback<FC_MainMenuScene>(*this, &FC_MainMenuScene::ShowTimer_Timer));
    AddControl(m_pTimer);

    m_pHideBoardsTimer = new PK::PK_TimerControl(GetName() + "_hideBoardsTimer", 500, false, false);
    m_pHideBoardsTimer->OnTimer.Set(new PK::PK_ObjectCallback<FC_MainMenuScene>(*this, &FC_MainMenuScene::HideBoardsTimer_Timer));
    AddControl(m_pHideBoardsTimer);
    
    m_pAskLoginTimer = new PK::PK_TimerControl(GetName() + "_askLoginTimer", 2500, false, false);
    m_pAskLoginTimer->OnTimer.Set(new PK::PK_ObjectCallback<FC_MainMenuScene>(*this, &FC_MainMenuScene::AskLoginTimer_Timer));
    AddControl(m_pAskLoginTimer);
    
    // Callback do sign da esquerda
    m_pLeftSign->OnSignClick.Set(new PK::PK_ObjectCallback<FC_MainMenuScene>(*this, &FC_MainMenuScene::BtnPlay_Click));
    // Callback do sign da direita
    m_pRightSign->OnSignClick.Set(new PK::PK_ObjectCallback<FC_MainMenuScene>(*this, &FC_MainMenuScene::BtnLeaderboards_Click));
	
 }
   
// 
void FC_MainMenuScene::OnInitialize()
{
} 
 
// 
void FC_MainMenuScene::OnOpen()
{ 
    GetGame().PlayMainMenuMusic();
    PK::PokeEngine.GetAdManager().ShowBanner();
    m_pAskLoginTimer->SetEnabled(false);

    switch(m_Type)
    { 
        case MainMenuType_Intro:
            m_pLeftSign->Show(SignType_Play, 500);
            m_pRightSign->Show(SignType_Leaderboards, 500);
            m_pTitle->Show();
            m_pScoreBoard->SetVisible(false);
            PK::PK_Rate::ShowWithCondition();
            break;

        case MainMenuType_GameOver:
            m_pLeftSign->Show(SignType_Play, 1500);
            m_pRightSign->Show(SignType_Leaderboards, 1500);
            m_pTitle->SetVisible(false);
            if (GetGame().GetLeaderboard().CanSubmitScore() && GetSession().GetScore() >  0)
            {
                GetGame().GetLeaderboard().SubmitScore(GetSession().GetScore());
            }
            // Ver se bateu o melhor score e gravar em caso disso
            bool bHighscoreBeaten = false;
            FC_GameSession savedSession;
            savedSession.Load();
            int iHighScore = savedSession.GetHighScore();
            if (iHighScore < GetGame().GetSession().GetScore())
            {
                iHighScore = GetSession().GetScore();
                GetSession().SetHighScore(iHighScore);
                bHighscoreBeaten = true;
            }
            bHighscoreBeaten = true;
            m_pScoreBoard->Show(GetSession().GetScore(), iHighScore, bHighscoreBeaten);
            m_pAskLoginTimer->SetEnabled(GetSession().ShouldAskForLogin() && GetSession().GetScore() > 0);
            GetSession().IncrementGamesPlayed();
            GetSession().Save();
            
#ifdef DEBUG
            GetSession().Trace();
#endif
            break;
    }

    GetGame().ShowGlobalHUD();
}
   
// 
void FC_MainMenuScene::OnUpdate(const PK::PK_GameTimer &time) 
{
    if (PK::PokeEngine.GetInputManager().QueryAction(PK::InputAction_Back))
    {
        GetGame().Exit();
    }
} 


//
void FC_MainMenuScene::BtnPlay_Click(PK::PK_Object &sender)
{
    if (!m_pScoreBoard->HasStarEffectEnded())
    {
        return;
    }
    m_pLeftSign->Hide();
    m_pRightSign->Hide();

    m_pHideBoardsTimer->Reset();
    m_pHideBoardsTimer->SetEnabled(true);

    m_pTimer->SetEnabled(true);
    
    GetGame().FadeMusicOut();
}

//
void FC_MainMenuScene::BtnLeaderboards_Click(PK::PK_Object &sender)
{
    GetGame().GetLeaderboard().Show();
}

//
void FC_MainMenuScene::ShowTimer_Timer(PK::PK_Object &sender)
{
    GetGame().GetGameplayScene().StartNewGame();
    PK::PokeEngine.GetAdManager().HideBanner();
    PK::PokeEngine.GetSceneManager().NavigateTo(FCAM_NAVIGATION_GAMEPLAY);
}

//
void FC_MainMenuScene::HideBoardsTimer_Timer(PK::PK_Object &sender)
{
    if (m_pTitle->IsVisible())
    {
        m_pTitle->Dismiss();
    }

    if (m_pScoreBoard->IsVisible())
    {
        m_pScoreBoard->Dismiss();
    }
}

//
void FC_MainMenuScene::AskLoginTimer_Timer(PK::PK_Object &sender)
{
    PK::PokeEngine.GetPlayer().AuthenticateWithQuery(PK::AuthenticateReason_LeaderboardsPost, false);
    GetSession().DontAskToLogin();
    GetSession().Save();
}




