#ifndef _PK_POKEGAMEDATA_H_
#define _PK_POKEGAMEDATA_H_

#include "PK_Settings.h"

namespace PK {    

//
class PK_PokeGameData : public PK_Settings
{
    // Rate data
    int m_iRateUsesUntilPrompt;
    bool m_bRateDontBother;
    
public:
	PK_PokeGameData();

public:
    void OnLoad();
    void OnSave();
    void IncrementGameUsages();

    inline int GetUsesWithoutPrompt() { return m_iRateUsesUntilPrompt; }
	inline bool GetRateDontBother() { return m_bRateDontBother; }

    inline void ResetRateUsesUntilPrompt() { m_iRateUsesUntilPrompt = 0; }
    inline void SetRateDontBother(bool bValue) { m_bRateDontBother = bValue; }
    
};

} // namespace

#endif