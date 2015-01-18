#include "PK_PokeGameData.h"
#include "PK_Consts.h"
#include "PK_Environment.h"
#include "PK_Path.h"

namespace PK {

PK_PokeGameData::PK_PokeGameData() :
    PK_Settings(PK_POKEGAMEDATA_NAME, "pokegameSettings")
{
    SetTypeName("PK_PokeGameData");
    m_bRateDontBother = false;
    m_iRateUsesUntilPrompt = 0;
    SetFilename(PK_Path::Combine(PK_Environment::GetGameStoragePath(), PK_POKE_GAME_DATA_FILE));
    SetLoadFailsIfNotExists(false);
}

//
void PK_PokeGameData::OnLoad()
{
    m_iRateUsesUntilPrompt = GetParameterValue_Int("rating", "usesUntilPrompt", 0);
    m_bRateDontBother = GetParameterValue_Bool("rating", "dontBother", false);
}
    
//
void PK_PokeGameData::OnSave()
{
    SetParameterValue_Int("rating", "usesUntilPrompt", m_iRateUsesUntilPrompt);
    SetParameterValue_Bool("rating", "dontBother", m_bRateDontBother);
}

//
void PK_PokeGameData::IncrementGameUsages()
{
    m_iRateUsesUntilPrompt++;
}
    
} // namespace
