#include <PokeEngine.h>
#include "FC_Consts.h"   
#include "FC_GameplayScene.h"              
#include "FC_CatActor.h"   
#include "FC_MouseActor.h"   
#include "FC_DogActor.h"
#include "FC_InanimateActor.h"   
#include "FC_Game.h"
#include "FC_Title.h"
#include "FC_ScorePoint.h"
#include "FC_MainMenuScene.h"
#include "FC_Tutorial.h" 

FC_GameplayScene::FC_GameplayScene() :
    FC_BaseScene("fc_gameplayScene")
{
    SetTypeName("FC_GameplayScene");

    SetBackgroundImage(FCAM_SPRITESET_BACKGROUND);
    SetWithPhysics(true);
    GetPhysicsManager()->SetVelocityThreshold(3.0f); // Para evitar o tremor quando os objectos com muito bounce estão a colidir
 //   GetPhysicsManager()->SetVisible(true);
     
    // Player
    m_pPlayer = new FC_Player("fc_player");
    m_pPlayer->OnFlickedLeft.Set(new PK::PK_ObjectCallback<FC_GameplayScene>(*this, &FC_GameplayScene::Player_FlickedLeft));
    m_pPlayer->OnFlickedRight.Set(new PK::PK_ObjectCallback<FC_GameplayScene>(*this, &FC_GameplayScene::Player_FlickedRight));
    m_pPlayer->OnFlickEnded.Set(new PK::PK_ObjectCallback<FC_GameplayScene>(*this, &FC_GameplayScene::Player_FlickEnded));
    AddControl(m_pPlayer);
 
    // Lauch timer
    m_pLauchTimer = new PK::PK_TimerControl("fc_launchTimer");
    m_pLauchTimer->OnTimer.Set(new PK::PK_ObjectCallback<FC_GameplayScene>(*this, &FC_GameplayScene::LauchTimer_Timer));
    m_pLauchTimer->SetWithSnooze(false);
    AddControl(m_pLauchTimer);

    // Hud
    m_pHud = new FC_Hud("fc_hud");
    AddControl(m_pHud);

    // Actors Container
    m_pActorsContainer = new PK::PK_Panel("fc_actorsContainerPnl");
    AddControl(m_pActorsContainer);
    
    // Fogo
    m_pFire = new FC_Fire("fc_fire");
    m_pFire->SetPosition(0.0f, -400.0f);
    AddControl(m_pFire);
     
    // Saida da esquerda
    m_pLeftExit = new FC_ActorExit("fc_leftExit", Side_Left);
    m_pLeftExit->OnActorExited.Set(new PK::PK_ObjectCallback<FC_GameplayScene>(*this, &FC_GameplayScene::LeftExit_ActorExited));
    AddControl(m_pLeftExit); 
     
    // Saida da direita
    m_pRightExit = new FC_ActorExit("fc_rightExit", Side_Right); 
    m_pRightExit->OnActorExited.Set(new PK::PK_ObjectCallback<FC_GameplayScene>(*this, &FC_GameplayScene::RightExit_ActorExited));
    AddControl(m_pRightExit); 

    // Disable as signs
    m_pLeftSign->SetClickEnabled(false);
    m_pLeftSign->BringToFront();
    m_pRightSign->SetClickEnabled(false);
    m_pRightSign->BringToFront();
   
    // Tutorial
    m_pTutorial = new FC_Tutorial();
    m_pTutorial->OnClick.Set(new PK::PK_ObjectCallback<FC_GameplayScene>(*this, &FC_GameplayScene::Tutorial_Click));
    AddControl(m_pTutorial);

    m_State = GameplayState_StartingUp;
    m_bCanControlActor = false;
}

//
void FC_GameplayScene::OnLoad()
{
    // Adicionar items a library

    // Um para cada tipo de gato
    for(int i = 0; i < FCAM_TOTAL_CATS; i++)
    {
        FC_CatActor *pCat = new FC_CatActor(i + 1);
        PK::PK_String sId;
        sId.Format("CAT%d", i + 1);
        PK::PokeEngine.GetLibrary().AddItem(PK::LibraryItemScope_SceneGroup, *pCat, FCAM_LIB_ITEM_CAT_IDX + i, sId);
    }

    // Um para cada tipo de rato
    for(int i = 0; i < FCAM_TOTAL_MICE; i++)
    {
        FC_MouseActor *pMouse = new FC_MouseActor(i + 1);
        PK::PK_String sId;
        sId.Format("MOUSE%d", i + 1);
        PK::PokeEngine.GetLibrary().AddItem(PK::LibraryItemScope_SceneGroup, *pMouse, FCAM_LIB_ITEM_MOUSE_IDX + i, sId);
    }

    // Cao
    FC_DogActor *pDog = new FC_DogActor();
    PK::PokeEngine.GetLibrary().AddItem(PK::LibraryItemScope_SceneGroup, *pDog, FCAM_LIB_ITEM_DOG_IDX, "DOG");

	// Object inanimado
    FC_InanimateActor *pObj = new FC_InanimateActor();
    PK::PokeEngine.GetLibrary().AddItem(PK::LibraryItemScope_SceneGroup, *pObj, FCAM_LIB_ITEM_OBJECT_IDX, "OBJECT");
}

//
void FC_GameplayScene::OnInitialize()
{
}

//
void FC_GameplayScene::OnOpen()
{
	if (m_State == GameplayState_Running || m_State == GameplayState_Tutorial)
	{
        m_pLeftSign->Show(SignType_Mouse, 500);
		m_pRightSign->Show(SignType_Cat, 500);
	}
}

   
//
void FC_GameplayScene::StartNewGame()
{
	m_fReleaseTime = (float)GetGame().GetSettings().GetInitialReleaseTime();
    m_fReleaseDecreaseTime = GetGame().GetSettings().GetReleaseTimeDecrease();
    m_pLauchTimer->SetEnabled(true);
	m_pLauchTimer->SetAlarmTime((int)m_fReleaseTime);
	m_fAirResistance = GetGame().GetSettings().GetInitialAirResistance();
	m_fAirResistanceDecrease = GetGame().GetSettings().GetAirResistanceDecrease();
    m_fAirResistanceDecay = GetGame().GetSettings().GetAirResistanceDecay();
	m_State = GameplayState_NotStarted;
	m_pActorsContainer->RemoveAllControls();
	m_bCanControlActor = true;
	    
	GetSession().Reset();
      
	m_pPlayer->SetEnabled(true);
	m_pLeftExit->SetActorAccepted(ActorType_Mouse);
	m_pRightExit->SetActorAccepted(ActorType_Cat);

    if (GetSession().ShouldShowTutorial())
    {
        ShowTutorial();
    }
    else
    {
    	m_pHud->Show();
        m_State = GameplayState_Running;
    }
	PK::PK_Log::WriteInfo(FCAM_LOG_TAG, "GAME STARTED");
}

//
void FC_GameplayScene::ShowTutorial()
{
    m_pTutorial->Play();
    m_State = GameplayState_Tutorial;
    m_pLauchTimer->SetEnabled(false);
    GetSession().IncrementTutorialSeen();
    GetSession().Save();
}

//
void FC_GameplayScene::OnUpdate(const PK::PK_GameTimer &time) 
{ 
    switch(m_State)
    {
        case GameplayState_StartingUp: 
            m_pHud->SetVisible(false);
            GetGame().GetMainMenuScene().SetMenuType(MainMenuType_Intro);
            PK::PokeEngine.GetSceneManager().PopUp(FCAM_NAVIGATION_MAINMENU, true);
			m_State = GameplayState_NotStarted;
            break;


        case GameplayState_Gameover:
            if (m_pActorsContainer->GetControls().GetCount() == 0 && 
                !m_pLeftSign->IsVisible() &&  // Quando se perde, as signs sao escondidas, temos que esperar que desaparecam
                !m_pRightSign->IsVisible())   // 
            {
                 m_pHud->SetVisible(false);
		  		 BroadcastMessage(FCAM_MSG_GAMEOVER);
                 GetGame().GetMainMenuScene().SetMenuType(MainMenuType_GameOver);
                 PK::PokeEngine.GetSceneManager().PopUp(FCAM_NAVIGATION_MAINMENU, true);
            }
            break;
             
        case GameplayState_Running:
            GetSession().AddEllapsedTime(time.GetEllapsedTime());
            break;

        case GameplayState_Tutorial:
            break;

        case GameplayState_NotStarted:
            break;
               
        default:
            break;
    }
}    
   

// 
void FC_GameplayScene::LauchTimer_Timer(PK::PK_Object &sender)
{
    PK::PK_Log::WriteInfo(FCAM_LOG_TAG, "Game time: %d, score: %d", GetSession().GetEllapsedTime(), GetSession().GetScore());
    LaunchActor();
} 
  
//
void FC_GameplayScene::LaunchActor()
{
    FC_Actor *pActorToRelease = GetSession().RandomizeActor();

    pActorToRelease->SetPosition(PK::PK_RandomGenerator::GetRandNumber(400) - 170.0f, 512.0f + pActorToRelease->GetSize().h);
    pActorToRelease->OnKilled.Set(new PK::PK_ObjectCallback<FC_GameplayScene>(*this, &FC_GameplayScene::Actor_Died));
    m_pActorsContainer->AddControl(pActorToRelease);
    pActorToRelease->SetToFalling(m_fAirResistance);

    // Adicionamos a altura ao timer para que nao saiam actores uns por baixo dos outros
    m_pLauchTimer->SetAlarmTime((unsigned int) (m_fReleaseTime + pActorToRelease->GetSize().h));
    m_pLauchTimer->SetEnabled(true);


}

//
void FC_GameplayScene::Actor_Died(PK::PK_Object &sender)
{
    SetToGameOver();
}

//
void FC_GameplayScene::LeftExit_ActorExited(PK::PK_Object &sender)
{
  FC_Actor *pActor = m_pLeftExit->GetLastActorToExit();
 
  if (pActor->IsDog())
  {
      FC_DogActor *pDog = (FC_DogActor *)pActor;
       DogEnteredExit(*pDog, *((FC_ActorExit *) &sender));
  }
  else
  {
     ActorDeliveredWithSuccess(*pActor);
  } 
} 
              
//
void FC_GameplayScene::RightExit_ActorExited(PK::PK_Object &sender)
{
    FC_Actor *pActor = m_pRightExit->GetLastActorToExit();
    if (pActor->IsDog())
    {
        FC_DogActor *pDog = (FC_DogActor *)pActor;
        DogEnteredExit(*pDog, *((FC_ActorExit *) &sender));
    }
    else
    {
        ActorDeliveredWithSuccess(*pActor);
    }
}

//
void FC_GameplayScene::SetToGameOver()
{
    // SetToGameOver e chamado quando morre um actor, este metodo faz kill aos actores activos
    // Colocado isto para n ficar em loops
    if (m_State == GameplayState_Gameover)
    {
        return;
    }
    GetGame().PlaySound(FCAMP_SND_WRONG_ANIMAL_IDX);

    PK::PK_Log::WriteInfo(FCAM_LOG_TAG, "GAMEOVER");
    PK::PK_Log::WriteInfo(FCAM_LOG_TAG, "m_fAirResistance=%5.2f, m_fAirResistanceDecrease=%5.2f, m_fReleaseTime=%5.2f, m_fReleaseDecreaseTime=%5.2f", 
        m_fAirResistance, m_fAirResistanceDecrease, m_fReleaseTime, m_fReleaseDecreaseTime);

    m_State = GameplayState_Gameover;
    m_pLauchTimer->SetEnabled(false);
    m_pPlayer->SetEnabled(false);
    // Matar todos os actores que estiverem ainda a voar (para o jogador n pensar que ainda os pode controlar)
    for(PK_ListIterator(PK::PK_SceneControl *) itor = m_pActorsContainer->GetControls().Begin(); itor != m_pActorsContainer->GetControls().End(); itor++ )
    {
        FC_Actor *pActor = (FC_Actor *)(*itor);
        if (!pActor->IsDead())
        {
            pActor->Kill(false);
        }
    }
    m_pLeftSign->Hide();
    m_pRightSign->Hide();
}
  
//
void FC_GameplayScene::ActorDeliveredWithSuccess(FC_Actor &actor)
{
    m_fReleaseTime -= m_fReleaseDecreaseTime;
    m_fReleaseDecreaseTime *= (1.0f - GetGame().GetSettings().GetReleaseTimeDecreaseDecay());
    if (m_fReleaseTime < GetGame().GetSettings().GetMinReleaseTime())
    {
        m_fReleaseTime = (float)GetGame().GetSettings().GetMinReleaseTime();
    }

    m_fAirResistance -= m_fAirResistanceDecrease; 
    m_fAirResistanceDecrease *= (1.0f - m_fAirResistanceDecay);

    // O score depende de quando se enviou o gato/rato
    // Quanto mais acima maior o score
    float y = actor.GetPosition().y;
    int score = 3;
    if (y < GetGame().GetSettings().Get3PointsHeight())
    {
        score = 2;
    }
    if (y < GetGame().GetSettings().Get2PointsHeight())
    {
        score = 1;
    }
    GetGame().PlaySound(FCAMP_SOUND_1POINTS_IDX + (score - 1));

    FC_ScorePoint *pPoint = new FC_ScorePoint();
    pPoint->SetPosition(0.0f, 270.0f);
    pPoint->SetScore(score);
    AddControl(pPoint);
    GetSession().IncrementDelivered();
    GetSession().AddScore(score);
    m_pHud->Refresh();
  
    RemoveControl((PK::PK_SceneControl *)&actor);
}
       
// O actor controlavel e o que tiver entrado primeiro
FC_Actor * FC_GameplayScene::GetControllableActor()
{
    if (m_bCanControlActor == false ||
        m_pActorsContainer->GetControls().GetCount() == 0)
    {
        return NULL;
    }

    for(PK_ListIterator(PK::PK_SceneControl *) itor = m_pActorsContainer->GetControls().Begin(); itor != m_pActorsContainer->GetControls().End(); itor++ )
    {
        FC_Actor *pActor = (FC_Actor *)(*itor);
        if (pActor->CanBeControlled())
        {
            if (pActor->GetPosition().y > m_pFire->GetTop())
            {
                return pActor;
            }
        }
    }

    return NULL;
}   

//
void FC_GameplayScene::Player_FlickedLeft(PK::PK_Object &sender)
{

    FC_Actor *pCurrent = GetControllableActor();
    if (pCurrent != NULL)
    {
        pCurrent->MoveLeft();
        m_bCanControlActor = false;
    }
}

//
void FC_GameplayScene::Player_FlickedRight(PK::PK_Object &sender)
{

    FC_Actor *pCurrent = GetControllableActor();
    if (pCurrent != NULL)
    {
        pCurrent->MoveRight();
        m_bCanControlActor = false;
    }
}

//
void FC_GameplayScene::Player_FlickEnded(PK::PK_Object &sender)
{
    m_bCanControlActor = true;
}

//
void FC_GameplayScene::SpamDeadActor(FC_eActorType actorType, const PK_Vector2 &vPosition, int iJumpDirection, bool playSound)
{
    FC_Actor *pActor = NULL;
    int sndIdx = 0;
    switch(actorType)
    {
        case ActorType_Cat:
            pActor = &FC_CatActor::CreateRandomCat(GetSession());
            break;

        case ActorType_Mouse:
            pActor = &FC_MouseActor::CreateRandomMouse(GetSession());
            break;

        default:
#ifdef DEBUG
            throw PK::PK_GameException("Cannot spam dead actors of type %d.", __FILE__, __LINE__, (int)actorType);
#endif
            break;
    }
    
    if (pActor != NULL)
    {
        pActor->SetWithPhysics(false);
        pActor->SetPosition(vPosition);
        m_pActorsContainer->AddControl(pActor);
        pActor->Kill(iJumpDirection, playSound);
    }
}

//
void FC_GameplayScene::DogEnteredExit(FC_DogActor &dog, FC_ActorExit &exit)
{
    PK::PK_tSize res = PK::PokeEngine.GetSettings().GetGameResolution();

    int signal = (exit.GetSide() == Side_Left? -1 :1);
    FC_eActorType deadActorType = exit.GetActorType();
    for (int i = 0; i < 5; i++)
    {
        SpamDeadActor(deadActorType, PK_Vector2((res.w / 2) * signal, dog.GetPosition().y), -signal, (i==0));
    }

    m_pLauchTimer->SetEnabled(false);
    dog.RemoveFromScene();
    SetToGameOver();
}

//
float FC_GameplayScene::GetTopDogHouseBound()
{
    return (m_pFire->GetTop());
}

//
void FC_GameplayScene::EndTutorial()
{
    if (!m_pTutorial->CanEnd())
    {
        return;
    }
    m_State = GameplayState_Running;
    m_pHud->Show();
    LaunchActor();
    m_pTutorial->Stop();
    
}

//
void FC_GameplayScene::Tutorial_Click(PK::PK_Object &sender)
{
    EndTutorial();
}

//
void FC_GameplayScene::OnEnterForeground() 
{
	if (m_pLauchTimer != NULL)
	{
		m_pLauchTimer->Reset();
	}
}
