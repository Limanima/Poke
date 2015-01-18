#ifndef _PK_GAMEAPP_H_
#define _PK_GAMEAPP_H_

#include "PK_App.h"

namespace PK {

class PK_InputManager;
class PK_SceneManager;
class PK_AdManager;
class PK_AudioManager;
class PK_LoadingIcon;
class PK_Component;
class PK_Player;
class PK_PokeSettings;

class PK_GameApp : public PK_App
{
private:
    bool                 m_bRunning;
    PK_GameTimer         m_MainLoopTimer;
    unsigned int         m_uiGameId;
    bool                 m_bSuspended;
    PK_PokeSettings		 m_Settings;
    PK_PokeGameData      m_PokeGameData;
    PK_Library           m_Library;
    PK_Player           *m_pPlayer;
    PK_AudioManager     *m_pAudioManager;
    PK_InputManager     *m_pInputManager;
    PK_AssetManager     *m_pAssetManager;
    PK_SceneManager     *m_pSceneManager; 
    PK_RenderManager    *m_pRenderManager;
    PK_AdManager        *m_pAdManager;
	PK_EventManager     *m_pEventManager;

public:
	PK_GameApp(const PK_String &sName);
    void InternalInitialize(PK_Dictionary<PK_String, PK_String> arguments);
    void OnRun();
    void InternalUnInitialize();

private:
    void LoadSettings();
    void FrameUpdate();
    void OnLoopTimer(PK_Object &sender);

public:
    virtual void OnExit() {};
    virtual void OnStart() {}

    inline PK_Library & GetLibrary() { return m_Library; }
    inline PK_SceneManager & GetSceneManager() { return (*m_pSceneManager); }
    inline PK_RenderManager & GetRenderManager() { return (*m_pRenderManager); }
    inline PK_PokeSettings & GetSettings() { return m_Settings; }
    inline PK_AssetManager & GetAssetManager() { return (*m_pAssetManager); }
    inline PK_InputManager & GetInputManager() { return (*m_pInputManager); }
    inline PK_AudioManager & GetAudioManager() { return (*m_pAudioManager); }
    inline PK_EventManager & GetEventManager() { return (*m_pEventManager); }
    inline PK_AdManager & GetAdManager() { return (*m_pAdManager); }
    inline PK_Player & GetPlayer() { return (*m_pPlayer); }
};

}
#endif