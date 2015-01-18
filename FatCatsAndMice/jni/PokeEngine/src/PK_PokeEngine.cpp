#include <assert.h>
#define DECLARE_POKE_VARS // Vai definir as variaveis globais em PK_Globals.h
#include "PK_Config.h"
#include "PK_Globals.h"
#include "PK_PokeEngine.h"
#include "PK_ClassFactory.h"
#include "PK_Settings.h"
#include "PK_Profiler.h" 
#include "PK_Exceptions.h"
#include "PK_Log.h"
#include "PK_InputManager.h"
#include "PK_SceneManager.h"
#include "PK_RenderManager.h"
#include "PK_AudioManager.h"
#include "PK_AdManager.h"
#include "PK_Thread.h"
#include "PK_Thread.h"
#include "PK_RandomGenerator.h"
#include "PK_Player.h"
#include "PK_SDLRenderManager.h"
#include "PK_MessageBox.h"
#include "PK_Library.h"
#include "PK_File.h"
#include "PK_Web.h"
#include "PK_ConsoleApp.h"
#include "PK_Console.h"
#include <SDL.h>

#ifdef POKE_ANDROID
    #include "android/PK_JNIInterface.h"
#endif

#ifdef POKE_SDL
    #include "PK_SDLManager.h"
#endif

#define MAX_ELLAPSED_TIME 50

namespace PK {
    
//
extern "C" void PK_PokeEngine_StaticFrameUpdate(void*)
{
    PokeEngine.FrameUpdate();
}
    
//-------------------------------------------------------
PK_PokeEngine::PK_PokeEngine()
{
    SetTypeName("PK_PokeEngine");
    SetName(PK_POKE_ENGINE_NAME);
    m_pGame = NULL;
    m_pRenderManager = NULL;
    m_pInputManager = NULL;
    m_pSceneManager = NULL;
    m_pAdManager = NULL;
    m_pAudioManager = NULL;
    m_pAssetManager = NULL;
	m_pEventManager = NULL;
    m_pProfiler = NULL;
    m_pPlayer = NULL;
    m_bRunning = false;
    m_Library.SetName(PK_LIBRARY_NAME);
}


// Adiciona um componente ao engine
void PK_PokeEngine::AddComponent(PK_Component & component)
{
    InternalAddComponent(component);
    component.OnLoad();
    component.OnInitialize();
}

//
void PK_PokeEngine::InternalAddComponent(PK_Component & component)
{
    if (m_Components.Contains(&component))
    {
        throw PK_SystemException("Cannot add component because it is already added to the system.", __FILE__, __LINE__);
    }
    component.Grab();
    m_Components.Add(&component);
}

// 
int PK_PokeEngine::Run(PK_App &app, int argc, char * argv[])
{
    PK::PK_Dictionary<PK::PK_String, PK::PK_String> arguments;
    for(int i = 0; i < argc; i++)
    {
        if (argv[i][0]=='-')
        {
            if (i < argc + 1)
            {
                PK_String name = PK::PK_String(argv[i]);
                name.Replace("-", "");
                if (name.length() == 0)
                {
                    continue;
                }
                arguments.Add(name, argv[i + 1]);
                i++;
            }
        }
    }

    try
    {
        app.InternalInitialize(arguments);
        app.InternalRun();
        app.InternalUnInitialize();
        return 0;
    }
    catch(PK_Exception &ex)
    { 
        PK_Log::WriteError(PK_LOG_TAG, "%s, File:%s, Line:%d", ex.GetMsg().c_str(), ex.GetFile().c_str(), ex.GetLine());
#ifdef POKE_DEBUG
        PK_MessageBox::Show("Poke exception:", ex.GetMsg());
        throw;
#endif
    }

    /*
    try
    {
        return app.Run(arguments);
    }
    catch(PK_Exception &ex)
    { 
        PK_Log::WriteError(PK_LOG_TAG, "%s, File:%s, Line:%d", ex.GetMsg().c_str(), ex.GetFile().c_str(), ex.GetLine());
#ifdef POKE_DEBUG
        PK_MessageBox::Show("Poke exception:", ex.GetMsg());
        throw;
#endif
    }*/
}

// Loop principal do engine
void PK_PokeEngine::Run(PK_Game &game)
{
    try
    {
        PK_Profiler::SetToReady();
        Grab();

        Initialize(game);

		m_bRunning = true;
        m_pGame->OnStart();

        m_pPokeGameData->IncrementGameUsages();
        m_pPokeGameData->Save();

        if (m_pSettings->GetWithOnlineServices())
        {
#ifdef POKE_IOS
            if (m_pPlayer->SupportsAuthentication())
            {
                PK_SDLRenderManager *pSDLManager = (PK_SDLRenderManager *) m_pRenderManager;
                SDL_iPhoneSetAnimationCallback(pSDLManager->GetWindow(), 1, PK_PokeEngine_StaticFrameUpdate, 0);
                m_pPlayer->Authenticate(false);
                return;
            }
#endif
        }

        while (m_bRunning)
        {
            FrameUpdate();
        }
        m_pGame->OnExit();
        UnInitialize();
        PK_Profiler::AssertObjectsDestroyed();
        exit(0);

    }
    catch(PK_Exception &ex)
    { 
        PK_Log::WriteError(PK_LOG_TAG, "%s, File:%s, Line:%d", ex.GetMsg().c_str(), ex.GetFile().c_str(), ex.GetLine());
#ifdef POKE_DEBUG
        PK_MessageBox::Show("Game Exception", ex.GetMsg());
        throw;
#endif
    }
}

//
void PK_PokeEngine::FrameUpdate()
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

    
// Inicializa os componentes
void PK_PokeEngine::Initialize(PK_Game &game)
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
	InternalAddComponent(*(PK_Component * )m_pAssetManager);
    
    // Event manager
    PK_Log::WriteInfo(PK_LOG_TAG, "Creating event manager...");
	m_pEventManager = &PK_EventManager::CreateInstance(PK_SDL_MANAGER_NAME);
    InternalAddComponent(*(PK_Component * )m_pEventManager);

    // Input Manager
    PK_Log::WriteInfo(PK_LOG_TAG, "Creating input manager...");
	m_pInputManager = PK_ClassFactory::CreateInputManager(PK_INPUT_MANAGER_NAME);
	InternalAddComponent(*(PK_Component * )m_pInputManager);

    // Render Manager
    PK_Log::WriteInfo(PK_LOG_TAG, "Creating render manager...");
	m_pRenderManager = PK_ClassFactory::CreateRenderManager(PK_RENDER_MANAGER_NAME);
	InternalAddComponent(*(PK_Component * )m_pRenderManager);

    // Sound Manager
    PK_Log::WriteInfo(PK_LOG_TAG, "Creating sound manager...");
	m_pAudioManager = PK_ClassFactory::CreateAudioManager(PK_AUDIO_MANAGER_NAME);
	InternalAddComponent(*(PK_Component * )m_pAudioManager);
      
    // Scene Manager
    PK_Log::WriteInfo(PK_LOG_TAG, "Creating scene manager...");
	m_pSceneManager = PK_ClassFactory::CreateSceneManager(PK_SCENE_MANAGER_NAME);
    InternalAddComponent(*m_pSceneManager);

    // Advertising manager
    PK_Log::WriteInfo(PK_LOG_TAG, "Creating ad manager...");
    m_pAdManager = PK_ClassFactory::CreateAdManager(PK_AD_MANAGER_NAME);
    m_pAdManager->SetActive(m_pSettings->GetWithAdvertising());
    InternalAddComponent(*m_pAdManager);
        
    // Profiler
    m_pProfiler = new PK_Profiler();
    m_pProfiler->SetActive(m_pSettings->GetProfilerEnabled());
    m_pProfiler->SetVisible(m_pSettings->GetProfilerEnabled());
    InternalAddComponent(*m_pProfiler);

    // Game
    m_pGame = &game;
    InternalAddComponent(*(PK_Component * )m_pGame);

    for(int i = 0; i < m_Components.GetCount(); i++)
	{
        PK_Log::WriteInfo(PK_LOG_TAG, "Initialize component '%s'", m_Components[i]->GetName().c_str());
        m_Components[i]->OnLoad();
        m_Components[i]->OnInitialize();
    }

    // Inicializar o timer
    m_MainLoopTimer.SetWithSnooze(true);
    m_MainLoopTimer.OnTimer.Set(new PK_ObjectCallback<PK_PokeEngine>(*this, &PK_PokeEngine::OnLoopTimer));
    m_MainLoopTimer.SetEnabled(true);
    if (m_pSettings->GetLockFPS() == true)
    {
      m_MainLoopTimer.SetAlarmTime((unsigned int)(1000/m_pSettings->GetFPS()));
    }
    else
    {
      m_MainLoopTimer.SetAlarmTime(0);
    }

    PK_RandomGenerator::Initialize();

    // Test internet connection
    PK_Web::TestInternetConnectionAsync();
}

// Liberta todos os recursos utilizados
void PK_PokeEngine::UnInitialize()
{
    for(int i = (int)m_Components.GetCount() - 1; i >= 0; i--)
	{
        m_Components[i]->OnUnInitialize();
        m_Components[i]->OnUnload();
        m_Components[i]->Release();
    }


    PK_FREE(m_pSettings)
    PK_FREE(m_pPokeGameData);
    PK_FREE(m_pPlayer);

    // Libertar os items da library que tenham scope global
    GetLibrary().RemoveItemsInScope(LibraryItemScope_Global);

}

// Executa o update em todos os componentes
void PK_PokeEngine::UpdateComponents(const PK_GameTimer &time)
{
     for(int i = 0; i < m_Components.GetCount(); i++)
	 {
         if (m_Components[i]->IsActive())
         {
            m_Components[i]->OnUpdate(time);
         }
     }
}

//
void PK_PokeEngine::DrawComponents()
{
    m_pRenderManager->BeginRender();
    for(int i = 0; i < m_Components.GetCount(); i++)
	{
         if (m_Components[i]->IsVisible())
         {
            m_Components[i]->OnDraw();
         }
    }
    m_pRenderManager->EndRender();
}

void PK_PokeEngine::ExitGame()
{
	if (m_pGame == NULL)
	{
		throw PK_SystemException("Cannot exit game because a PK_Game was not created.", __FILE__, __LINE__);
	}

	m_bRunning = false;
}
    
// Este evento pode n ocorrer na thread principal,
// mas e necesario suspender o loop de update/draw imediatamente
void PK_PokeEngine::RespondToEnterBackground()
{
    m_bSuspended = true;
    GetRenderManager().WaitForEnd();
    // Lanca evento que corre na thread principal do engine
    GetEventManager().PostEvent(PK_EVENT_APP_ENTERED_BACKGROUND);
}
    
//
void PK_PokeEngine::OnGameEnteredBackground()
{
	PK_Log::WriteInfo(PK_LOG_TAG, "Game entered background.");
    for(int i = 0; i < m_Components.GetCount(); i++)
    {
       m_Components[i]->InternalOnEnterBackground();
    }

}

//
void PK_PokeEngine::OnGameEnteredForeground()
{
	PK_Log::WriteInfo(PK_LOG_TAG, "Game entered foreground.");
    m_MainLoopTimer.Reset();
    for(int i = 0; i < m_Components.GetCount(); i++)
    {
       m_Components[i]->InternalOnEnterForeground();
    }

    m_bSuspended = false;
}

//
void PK_PokeEngine::OnLowMemoryDetected()
{
    m_pGame->OnLowMemory();
}
    
//
void PK_PokeEngine::OnOsIssuedEndGame()
{
    m_pGame->OnLowMemory();
    m_pGame->Exit();
}

//
void PK_PokeEngine::OnCloseGame()
{
    if (m_pGame->OnClose())
    {
        m_pGame->Exit();
    }
}

//
void PK_PokeEngine::OnGamerServicesLogin(bool bSuccess)
{

	m_pGame->OnGamerServicesLogin(bSuccess);
}

//
void PK_PokeEngine::OnGamerServicesLogout()
{
	m_pGame->OnGamerServicesLogout();
}

// Devolve um componente adicionado ao engine por nome
PK_Component * PK_PokeEngine::GetComponent(const PK_String &sComponentName)
{
    for(int i = 0; i < m_Components.GetCount(); i++)
    {
        if (m_Components[i]->GetName() == sComponentName)
        {
            return m_Components[i];
        }
    }
    return NULL;
}
    
//
void PK_PokeEngine::LoadSettings()
{
    m_pSettings = new PK_PokeSettings();
    m_pSettings->Grab();
    m_pSettings->Load(PK_POKE_SETTINGS_FILE);
    
    m_pPokeGameData = new PK_PokeGameData();
    m_pPokeGameData->Grab();
    m_pPokeGameData->Load();
}
    
// Passar pointer, isto porque NULL remove o icon
void PK_PokeEngine::SetLoadingIcon(PK_LoadingIcon *pIcon)
{
    m_pSceneManager->SetLoadingIcon(pIcon);
}

    
//
void PK_PokeEngine::OnLoopTimer(PK_Object &sender)
{
    if (m_MainLoopTimer.GetEllapsedTime() > MAX_ELLAPSED_TIME) // No minimo 20 fps
    {
        m_MainLoopTimer.SetEllapsedTime(MAX_ELLAPSED_TIME);
    }

    UpdateComponents(m_MainLoopTimer);
    DrawComponents();
}

//
void PK_PokeEngine::PostEvent(PK_tEvent &event)
{
	if (m_pEventManager == NULL)
	{
		throw PK_SystemException("Cannot post events because the event manager is not initialized.", __FILE__, __LINE__);
	}
	m_pEventManager->PostEvent(event);
}

} // namespace
