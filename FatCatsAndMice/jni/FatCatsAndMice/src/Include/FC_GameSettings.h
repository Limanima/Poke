#ifndef _FC_GAMESETTINGS_H_
#define _FC_GAMESETTINGS_H_

#include <PokeEngine.h>
#include "FC_Types.h"
class FC_Session;
// 
class FC_GameSettings : public PK::PK_Settings
{
private:
    int   m_iInitialReleaseTime;
    int   m_iMinReleaseTime;
    float m_fInitialAirResistance;
    float m_fAirResistanceDecrease;
    float m_fAirResistanceDecay;
    float m_fSidewaySpeed;
    int   m_iShirtProbability;
    float m_fTimeDecrease;
    float m_fTimeDecreaseDecay;
    int m_i3PointsHeight;
    int m_i2PointsHeight;

    PK::PK_Array<FC_tTimmingEntry> m_LevelTimmings;

public:
	FC_GameSettings();
    void OnLoad();
    void InitializeTimmings();
   
	inline int GetInitialReleaseTime() { return m_iInitialReleaseTime; }
    inline float GetReleaseTimeDecrease() { return m_fTimeDecrease; }
    inline float GetReleaseTimeDecreaseDecay() { return m_fTimeDecreaseDecay; }
    inline int GetMinReleaseTime() { return m_iMinReleaseTime; }
	inline float GetInitialAirResistance() { return m_fInitialAirResistance; }
    inline float GetAirResistanceDecrease() { return m_fAirResistanceDecrease; }
    inline float GetAirResistanceDecay() { return m_fAirResistanceDecay; }
    inline float GetSidewaySpeed() { return m_fSidewaySpeed; }
    inline int GetShirtProbability() { return m_iShirtProbability; }
    inline FC_tTimmingEntry * GetLevelEntry(FC_eTimmingLevel level) { return &(m_LevelTimmings[(int)level]); }
    inline int Get3PointsHeight() { return m_i3PointsHeight; }
    inline int Get2PointsHeight() { return m_i2PointsHeight; }
};

#endif
