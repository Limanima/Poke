#ifndef _FCAM_GAMESESSION_H
#define _FCAM_GAMESESSION_H

#include <PokeEngine.h>
#include "FC_Types.h"
class FC_Actor;

class FC_GameSession 
{
private:
    // Dados que sao gravados em disco
    int m_iGamesPlayed;
    bool m_bAutologin;
    int m_iHighScore;
    bool m_bAudioOn;
    int m_iTutorialSeenCount;

    int m_iScore;
    int m_iDeliveredAnimals;
    unsigned int m_uiEllapsedTime;
    bool m_bFridgeWasReleased;
    bool m_bElephantWasReleased;
    bool m_bAskedToLogin;
    PK::PK_String m_sFilename;
	int m_iNoDogsCounter;
	int m_iNoInanimateCounter;
	int m_iNoShirtCounter;
    float m_fDogsProbability;
    float m_fObjectsProbability;

public:
    FC_GameSession();
    void Save();
    void Load();
    void Reset();
    void IncrementDelivered();
    void AddScore(int iScore);
    void AddEllapsedTime(unsigned int uiEllapsed);
    const bool IsLevelValid(FC_eTimmingLevel level);
    bool ShouldShowTutorial();
    FC_Actor * RandomizeActor();
    void Trace();

    inline int GetDelivered() { return m_iDeliveredAnimals; }
    inline int GetScore() { return m_iScore; }
    inline int GetHighScore() { return m_iHighScore; }
    inline void SetHighScore(int iScore) { m_iHighScore = iScore; }
    inline unsigned int GetEllapsedTime() { return m_uiEllapsedTime; }
    inline void IncrementGamesPlayed() { m_iGamesPlayed++;}
    inline int GetGamesPlayedCount() { return m_iGamesPlayed;}
    inline void SetAutoLogin(bool bAutologin) { m_bAutologin = bAutologin; }
    inline bool ShouldAutoLogin() { return m_bAutologin; }
    inline void DontAskToLogin() { m_bAskedToLogin = true; }
    inline bool ShouldAskForLogin() { return !m_bAskedToLogin; } // So pergunta uma vez
    inline bool GetAudioOn() { return m_bAudioOn; }
    inline void SetAudioOn(bool bAudioOn) { m_bAudioOn = bAudioOn; }
    inline void IncrementTutorialSeen() { m_iTutorialSeenCount++; }
};

#endif
