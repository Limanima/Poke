#ifndef _FCAM_Game_H
#define _FCAM_Game_H

#include <PokeEngine.h>
#include "FC_GameSettings.h"
#include "FC_GameSession.h"

class FC_GameplayScene;
class FC_MainMenuScene;
class FC_GlobalHUD;

class FC_Game : public PK::PK_Game
{
private:
    int m_iScore;
    PK::PK_Leaderboard *m_pLeaderboard;
    PK::PK_AdBanner    *m_pAdBanner;
    FC_GameSettings     m_Settings;
    FC_GameSession      m_GameSession;
	FC_GameplayScene   *m_pGameplayScene;
	FC_MainMenuScene   *m_pMainMenuScene;
	FC_GlobalHUD	   *m_pGlobalHUD;
    PK::PK_Array<PK::PK_SoundAsset *>  m_soundLibrary;
    PK::PK_MusicAsset      *m_pMenuMusic;

public:
    FC_Game();
    ~FC_Game();
    void OnStart();
    void OnExit();
    void OnEnterForeground();
    void OnGamerServicesLogin(bool bSuccess);
    void OnGamerServicesLogout();
    PK::PK_Scene * CreateScene(const PK::PK_String &name);
    void ShowGlobalHUD();
    void RefreshGlobalHUD();
    void PlaySound(int idx);
    void PlayMainMenuMusic();
    void FadeMusicOut();

    inline PK::PK_Leaderboard & GetLeaderboard() { return *m_pLeaderboard; }
    inline FC_GameSession & GetSession() { return m_GameSession; }
    inline FC_GameSettings & GetSettings() { return m_Settings; }
	inline FC_GameplayScene & GetGameplayScene() { return *m_pGameplayScene; }
 	inline FC_MainMenuScene & GetMainMenuScene() { return *m_pMainMenuScene; }
    

   static FC_Game & GetInstance() { return *((FC_Game*)&PK::PokeEngine.GetGame()); }
};

#endif
