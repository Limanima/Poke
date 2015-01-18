#ifndef _PK_POKEENGINE_H_
#define _PK_POKEENGINE_H_

#include "PK_Object.h"
#include "PK_Game.h"
#include "PK_Component.h"
#include "PK_DrawableComponent.h"
#include "PK_AssetManager.h"
#include "PK_SceneManager.h"
#include "PK_RenderManager.h"
#include "PK_PokeSettings.h"
#include "PK_Array.h"
#include "PK_Profiler.h"
#include "PK_Types.h"
#include "PK_GameTimer.h"
#include "PK_Library.h"    
#include "PK_PokeGameData.h"
#include "PK_EventManager.h"

namespace PK {
class PK_App;
class PK_InputManager;
class PK_SceneManager;
class PK_AdManager;
class PK_AudioManager;
class PK_LoadingIcon;
class PK_Component;
class PK_Player;

class PK_PokeEngine : public PK_Object
{
private:
    PK_Array<PK_Component *> m_Components;
    bool                 m_bRunning;
    PK_GameTimer         m_MainLoopTimer;
    unsigned int         m_uiGameId;
    bool                 m_bSuspended;
    PK_PokeSettings		*m_pSettings;
    PK_Library           m_Library;
    PK_Game             *m_pGame;
    PK_Player           *m_pPlayer;
    PK_Profiler         *m_pProfiler;
    PK_AudioManager     *m_pAudioManager;
    PK_InputManager     *m_pInputManager;
    PK_AssetManager     *m_pAssetManager;
    PK_SceneManager     *m_pSceneManager; 
    PK_RenderManager    *m_pRenderManager;
    PK_AdManager        *m_pAdManager;
	PK_EventManager     *m_pEventManager;
    PK_PokeGameData     *m_pPokeGameData;

public:
    PK_PokeEngine();
    void AddComponent(PK_Component & component);
    void Initialize(PK_Game &game);
    void UnInitialize();
    int Run(PK_App &app, int argc, char * argv[]);
    void Run(PK_Game &game);
    void FrameUpdate();
    void UpdateComponents(const PK_GameTimer &time);
    void DrawComponents();
    void ExitGame();
	void PostEvent(PK_tEvent &event);
    void RespondToEnterBackground();
    // Events
    void OnGameEnteredBackground();
    void OnGameEnteredForeground();
    void OnLowMemoryDetected();
    void OnOsIssuedEndGame();
    void OnCloseGame();
    void OnGamerServicesLogin(bool bSuccess);
    void OnGamerServicesLogout();

    void InternalAddComponent(PK_Component & component);

    PK_Component * GetComponent(const PK_String &sComponentName);
    void SetLoadingIcon(PK_LoadingIcon *pIcon);
    inline bool IsSuspended() { return m_bSuspended; }
    
    inline PK_Game & GetGame() { return *m_pGame; }
    inline PK_Library & GetLibrary() { return m_Library; }
    inline PK_SceneManager & GetSceneManager() { return (*m_pSceneManager); }
    inline PK_RenderManager & GetRenderManager() { return (*m_pRenderManager); }
    inline PK_PokeSettings & GetSettings() { return (*m_pSettings); }
    inline PK_AssetManager & GetAssetManager() { return (*m_pAssetManager); }
    inline PK_InputManager & GetInputManager() { return (*m_pInputManager); }
    inline PK_AudioManager & GetAudioManager() { return (*m_pAudioManager); }
    inline PK_EventManager & GetEventManager() { return (*m_pEventManager); }
    inline PK_AdManager & GetAdManager() { return (*m_pAdManager); }
    inline PK_Player & GetPlayer() { return (*m_pPlayer); }
    inline PK_Profiler & GetProfiler() { return (*m_pProfiler); }
    // FIXME - Este gamedata e exclusivo do engine, n devia ficar visivel por aqui
    inline PK_PokeGameData & GetGameData() { return (*m_pPokeGameData); }

private:
    void LoadSettings();
    void OnLoopTimer(PK_Object &sender);
};

}
#endif
