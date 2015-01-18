#include <PokeEngine.h>
#include "FC_Game.h"
#include "FC_MainMenuScene.h"
#include "FC_GameplayScene.h"
#include "FC_Consts.h"
#include "FC_GlobalHUD.h"
 
   
// Entry point do jogo. Chamado do main()
extern "C" void GameMain()
{   
    FC_Game *pMyGame = new FC_Game();
    PK::PokeEngine.Run(*pMyGame);
}    

FC_Game::FC_Game() :
    PK_Game("Fat Cats & Mice")
{
    m_pAdBanner = NULL;
    m_pLeaderboard = NULL;
    m_pGlobalHUD = NULL;
 
} 

//
FC_Game::~FC_Game()            
{ 
    if(m_pAdBanner != NULL)
    {
        m_pAdBanner->Release();
    } 
    
    if (m_pLeaderboard != NULL)
    {
        m_pLeaderboard->Release();
    }
}     
    
void FC_Game::OnStart()
{ 
	PK::PK_Log::WriteInfo(FCAM_LOG_TAG, "OnStart()");
    // Global HUB
	m_pGlobalHUD = new FC_GlobalHUD();
	PK::PokeEngine.AddComponent(*m_pGlobalHUD);

    m_Settings.Load(PK_POKE_SETTINGS_FILE);
    PK::PokeEngine.GetRenderManager().SetClearColor(PK_COLOR_BLACK);

    m_pLeaderboard = PK::PK_Leaderboard::CreateInstance(FCAM_LEADERBOARDS_NAME, FCAM_LEADERBOARDS_ID_GAME_CENTER, FCAM_LEADERBOARDS_ID_GOOGLE_PLAY);
    m_pLeaderboard->Grab();
    
    // Publicidade
    PK::PokeEngine.GetAdManager().SetBanner(FCAM_ADBANNER_NAME, FCAM_ADBANNER_ID, PK::AdDock_Top);
    
    
    if (PK::PK_Environment::IsiOS())
    {
        // Snails paid
        PK::PK_OfflineAdBanner *pAdSprite = new PK::PK_OfflineAdBanner("_fc_snailsPaidAd");
        pAdSprite->SetSpriteAssetName(FCAM_SPRITE_SNAILS_PAID_AD);
        pAdSprite->SetParentAlignment(PK::ParentAlignment_Top);
        pAdSprite->SetActionData(FCAM_SNAILS_APP_ID);
        pAdSprite->SetActionType(PK::AdClickAction_OpenAppInStore);
        PK::PokeEngine.GetAdManager().AddOfflineAd(*pAdSprite);
        
        // Snails free
        pAdSprite = new PK::PK_OfflineAdBanner("_fc_snailsFreeAd");
        pAdSprite->SetSpriteAssetName(FCAM_SPRITE_SNAILS_FREE_AD);
        pAdSprite->SetParentAlignment(PK::ParentAlignment_Top);
        pAdSprite->SetActionData(FCAM_SNAILS_FREE_APP_ID);
        pAdSprite->SetActionType(PK::AdClickAction_OpenAppInStore);
        PK::PokeEngine.GetAdManager().AddOfflineAd(*pAdSprite);
    }
    else
    {
        // Limanima.com
        PK::PK_OfflineAdBanner *pAdSprite = new PK::PK_OfflineAdBanner("_fc_limanimaAd");
        pAdSprite->SetSpriteAssetName(FCAM_SPRITE_LIMANIMA_AD);
        pAdSprite->SetParentAlignment(PK::ParentAlignment_Top);
        pAdSprite->SetActionData(FCAM_LIMANIMA_URL);
        pAdSprite->SetActionType(PK::AdClickAction_OpenUrl);
        PK::PokeEngine.GetAdManager().AddOfflineAd(*pAdSprite);
    }

    //
    GetSession().Load();
    if (GetSession().ShouldAutoLogin())
    {
        PK::PokeEngine.GetPlayer().Authenticate(false);
    }
    PK::PokeEngine.GetAudioManager().SetMuted(GetSession().GetAudioOn());
    m_pGlobalHUD->Refresh();
    m_pGlobalHUD->SetVisible(false);

    // Load de sound effects
    m_soundLibrary.SetSize(11);
    m_soundLibrary[FCAMP_SOUND_1POINTS_IDX] = PK::PokeEngine.GetAssetManager().LoadSoundEffect(FCAMP_SND_1POINTS, PK_ASSET_CONTAINER_NAME);
    m_soundLibrary[FCAMP_SOUND_2POINTS_IDX] = PK::PokeEngine.GetAssetManager().LoadSoundEffect(FCAMP_SND_2POINTS, PK_ASSET_CONTAINER_NAME);
    m_soundLibrary[FCAMP_SOUND_3POINTS_IDX] = PK::PokeEngine.GetAssetManager().LoadSoundEffect(FCAMP_SND_3POINTS, PK_ASSET_CONTAINER_NAME);
    m_soundLibrary[FCAMP_SND_TITLE_ENTRANCE_IDX] = PK::PokeEngine.GetAssetManager().LoadSoundEffect(FCAMP_SND_TITLE_ENTRANCE, PK_ASSET_CONTAINER_NAME);
    m_soundLibrary[FCAMP_SND_WRONG_ANIMAL_IDX] = PK::PokeEngine.GetAssetManager().LoadSoundEffect(FCAMP_SND_WRONG_ANIMAL, PK_ASSET_CONTAINER_NAME);
    m_soundLibrary[FCAMP_SND_CAT_DEATH_IDX] = PK::PokeEngine.GetAssetManager().LoadSoundEffect(FCAMP_SND_CAT_DEATH, PK_ASSET_CONTAINER_NAME);
    m_soundLibrary[FCAMP_SND_MOUSE_DEATH_IDX] = PK::PokeEngine.GetAssetManager().LoadSoundEffect(FCAMP_SND_MOUSE_DEATH, PK_ASSET_CONTAINER_NAME);
    m_soundLibrary[FCAMP_SND_TITLE_EXIT_IDX] = PK::PokeEngine.GetAssetManager().LoadSoundEffect(FCAMP_SND_TITLE_EXIT, PK_ASSET_CONTAINER_NAME);
    m_soundLibrary[FCAMP_SND_BOARD_SHOW_IDX] = PK::PokeEngine.GetAssetManager().LoadSoundEffect(FCAMP_SND_BOARD_SHOW, PK_ASSET_CONTAINER_NAME);
    m_soundLibrary[FCAMP_SND_BOARD_HIDE_IDX] = PK::PokeEngine.GetAssetManager().LoadSoundEffect(FCAMP_SND_BOARD_HIDE, PK_ASSET_CONTAINER_NAME);
    m_soundLibrary[FCAMP_SND_ACTOR_MOVE_IDX] = PK::PokeEngine.GetAssetManager().LoadSoundEffect(FCAMP_SND_ACTOR_MOVE, PK_ASSET_CONTAINER_NAME);

    m_pMenuMusic = PK::PokeEngine.GetAssetManager().LoadMusic(FCAMP_MUSIC_MENU, PK_ASSET_CONTAINER_NAME);
}

//
void FC_Game::OnExit()
{
}  

//
void FC_Game::OnEnterForeground()
{
    m_pGameplayScene->OnEnterForeground();
}

//
void FC_Game::OnGamerServicesLogin(bool bSuccess)
{
    GetSession().SetAutoLogin(bSuccess);
    GetSession().Save();
	if (m_pGlobalHUD != NULL)
	{
		m_pGlobalHUD->OnPlayerLoginStatusChanged();
	}
}

//
void FC_Game::OnGamerServicesLogout()
{
    GetSession().SetAutoLogin(false);
    GetSession().Save();
	if (m_pGlobalHUD != NULL)
	{
		m_pGlobalHUD->OnPlayerLoginStatusChanged();
	}
}

//
PK::PK_Scene * FC_Game::CreateScene(const PK::PK_String &name)
{
    if (name == "mainMenu")
    {
        m_pMainMenuScene = new FC_MainMenuScene();
        return m_pMainMenuScene;
    }
    if (name == "gameplay")
    {
		m_pGameplayScene = new FC_GameplayScene();
        return m_pGameplayScene;
    }

    return NULL;
}
  
// 
void FC_Game::ShowGlobalHUD()
{
    m_pGlobalHUD->SetVisible(true);
} 
 
//
void FC_Game::RefreshGlobalHUD()
{
    m_pGlobalHUD->Refresh();
}

//
void FC_Game::PlaySound(int idx)
{
#ifdef POKE_DEBUG
    if (idx < 0 || idx >= (int)m_soundLibrary.GetSize())
    {
        PK::PK_Log::WriteWarning(FCAM_LOG_TAG, "Sound index to be played is outside of the bounds of the sound library.");
        return;
    }
#endif
    PK::PokeEngine.GetAudioManager().PlaySoundEffect(*m_soundLibrary[idx]);
}

//
void FC_Game::PlayMainMenuMusic()
{
    PK::PokeEngine.GetAudioManager().PlayMusic(*m_pMenuMusic, true);
}

//
void FC_Game::FadeMusicOut()
{
    PK::PokeEngine.GetAudioManager().FadeOutMusic(1.0f);
}