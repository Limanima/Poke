#include "PK_Globals.h"
#include "PK_GameApp.h"
#include "PK_InputManager.h"
#include "PK_SceneManager.h"
#include "PK_AdManager.h"
#include "PK_AudioManager.h"
#include "PK_LoadingIcon.h"
#include "PK_Component.h"
#include "PK_Player.h"
#include "PK_PokeSettings.h"
#include "PK_Log.h"
#include "PK_ClassFactory.h"
#include "PK_RandomGenerator.h"
#include "PK_Web.h"
#include "PK_SDLRenderManager.h"

#define MAX_ELLAPSED_TIME 50

namespace PK {
//
extern "C" void PK_GameApp_StaticFrameUpdate(void*)
{
//    PK_GameApp.FrameUpdate(); // fix pk_gameapp or objecto
}
    
//
PK_GameApp::PK_GameApp(const PK_String &sName) :
    PK_App(AppType_Game, sName)
{
	SetTypeName("PK_GameApp");
    m_pPlayer = NULL;
    m_pAudioManager = NULL;
    m_pInputManager = NULL;
    m_pAssetManager = NULL;
    m_pSceneManager = NULL; 
    m_pRenderManager = NULL;
    m_pAdManager = NULL;
	m_pEventManager = NULL;
}


//
void PK_GameApp::InternalInitialize(PK_Dictionary<PK_String, PK_String> arguments)
{
    #ifdef POKE_ANDROID
	PKa_InitializeAndroid();
    #endif
    LoadSettings();

    m_pPlayer = PK_ClassFactory::CreatePlayer();
    m_pPlayer->Grab();

    // Asset Manager
    PK_Log::WriteInfo(PK_LOG_TAG, "Creating asset manager...");
    m_pAssetManager = PK_ClassFactory::CreateAssetManager(PK_ASSET_MANAGER_NAME);
	AddComponent(*(PK_Component * )m_pAssetManager);
    
    // Event manager
    PK_Log::WriteInfo(PK_LOG_TAG, "Creating event manager...");
	m_pEventManager = &PK_EventManager::CreateInstance(PK_SDL_MANAGER_NAME);
    AddComponent(*(PK_Component * )m_pEventManager);

    // Input Manager
    PK_Log::WriteInfo(PK_LOG_TAG, "Creating input manager...");
	m_pInputManager = PK_ClassFactory::CreateInputManager(PK_INPUT_MANAGER_NAME);
	AddComponent(*(PK_Component * )m_pInputManager);

    // Render Manager
    PK_Log::WriteInfo(PK_LOG_TAG, "Creating render manager...");
	m_pRenderManager = PK_ClassFactory::CreateRenderManager(PK_RENDER_MANAGER_NAME);
	AddComponent(*(PK_Component * )m_pRenderManager);

    // Sound Manager
    PK_Log::WriteInfo(PK_LOG_TAG, "Creating sound manager...");
	m_pAudioManager = PK_ClassFactory::CreateAudioManager(PK_AUDIO_MANAGER_NAME);
	AddComponent(*(PK_Component * )m_pAudioManager);
      
    // Scene Manager
    PK_Log::WriteInfo(PK_LOG_TAG, "Creating scene manager...");
	m_pSceneManager = PK_ClassFactory::CreateSceneManager(PK_SCENE_MANAGER_NAME);
    AddComponent(*m_pSceneManager);

    // Advertising manager
    PK_Log::WriteInfo(PK_LOG_TAG, "Creating ad manager...");
    m_pAdManager = PK_ClassFactory::CreateAdManager(PK_AD_MANAGER_NAME);
    m_pAdManager->SetActive(m_Settings.GetWithAdvertising());
    AddComponent(*m_pAdManager);

    for(int i = 0; i < GetComponents().GetCount(); i++)
	{
        PK_Log::WriteInfo(PK_LOG_TAG, "Initialize component '%s'", GetComponents()[i]->GetName().c_str());
        GetComponents()[i]->OnLoad();
        GetComponents()[i]->OnInitialize();
    }

    // Inicializar o timer
    m_MainLoopTimer.SetWithSnooze(true);
    m_MainLoopTimer.OnTimer.Set(new PK_ObjectCallback<PK_GameApp>(*this, &PK_GameApp::OnLoopTimer));
    m_MainLoopTimer.SetEnabled(true);
    if (m_Settings.GetLockFPS() == true)
    {
      m_MainLoopTimer.SetAlarmTime((unsigned int)(1000/m_Settings.GetFPS()));
    }
    else
    {
      m_MainLoopTimer.SetAlarmTime(0);
    }

    PK_RandomGenerator::Initialize();

    // Test internet connection
    PK_Web::TestInternetConnectionAsync();

    PK_App::InternalInitialize(arguments);
}

//
void PK_GameApp::OnRun()
{
 	m_bRunning = true;
    OnStart();

    m_PokeGameData.IncrementGameUsages();
    m_PokeGameData.Save();

    if (m_Settings.GetWithOnlineServices())
    {
#ifdef POKE_IOS
        if (m_pPlayer->SupportsAuthentication())
        {
            PK_SDLRenderManager *pSDLManager = (PK_SDLRenderManager *) m_pRenderManager;
            SDL_iPhoneSetAnimationCallback(pSDLManager->GetWindow(), 1, PK_GameApp_StaticFrameUpdate, 0);
            m_pPlayer->Authenticate(false);
            return;
        }
#endif
    }

    while (m_bRunning)
    {
        FrameUpdate();
    }
}

// 
void PK_GameApp::InternalUnInitialize()
{
    PK_FREE(m_pPlayer);

    // Libertar os items da library que tenham scope global
    GetLibrary().RemoveItemsInScope(LibraryItemScope_Global);

    PK_App::InternalUnInitialize();
}
    
//
void PK_GameApp::LoadSettings()
{
    m_Settings.Load(PK_POKE_SETTINGS_FILE);    
    m_PokeGameData.Load();
}

//
void PK_GameApp::FrameUpdate()
{
    try
    {
        
        if (!m_bSuspended)
        {
            m_MainLoopTimer.Update();
        }
        else // Se o jogo esta suspenso (em background) temos que chamar o update do SDL. Isto para apanhar o evento de ENTER_FOREGROUND
        {
            m_pEventManager->OnUpdate(m_MainLoopTimer);
        }
    }
    catch(PK_Exception &ex)
    {
        PK_Log::WriteError(PK_LOG_TAG, "%s, File:%s, Line:%d", ex.GetMsg().c_str(), ex.GetFile().c_str(), ex.GetLine());
        throw ex;
    }
}
   
//
void PK_GameApp::OnLoopTimer(PK_Object &sender)
{
    if (m_MainLoopTimer.GetEllapsedTime() > MAX_ELLAPSED_TIME) // No minimo 20 fps
    {
        m_MainLoopTimer.SetEllapsedTime(MAX_ELLAPSED_TIME);
    }

    UpdateComponents(m_MainLoopTimer);
    DrawComponents(*m_pRenderManager);
}


//
void PK_PokeEngine::ExitGame()
{
	m_bRunning = false;
}
  
} // namespace
