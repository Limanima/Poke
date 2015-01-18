#include "FC_GameSettings.h"
#include "FC_TypeConverters.h"

FC_GameSettings::FC_GameSettings() :
 PK_Settings("fc_GameSettings", "pokeSettings/gameSettings")
{
    SetTypeName("FC_GameSettings");
}

//
void FC_GameSettings::OnLoad()
{
    m_iInitialReleaseTime = GetParameterValue_Int("initialReleaseTime");
    m_fTimeDecrease = GetParameterValue_Float("releaseTimeDecrease");
    m_fTimeDecreaseDecay = GetParameterValue_Float("releaseTimeDecreaseDecay");
    m_iMinReleaseTime = GetParameterValue_Int("minReleaseTime");
    m_fInitialAirResistance = GetParameterValue_Float("initialAirResistance");
    m_fAirResistanceDecrease = GetParameterValue_Float("airResistanceDecrease");
    m_fAirResistanceDecay = GetParameterValue_Float("airResistanceDecay");
    m_fSidewaySpeed = GetParameterValue_Float("sidewaySpeed");
    m_iShirtProbability = GetParameterValue_Int("shirtProbability");
    m_i3PointsHeight = GetParameterValue_Int("threePointsHeight");
    m_i2PointsHeight = GetParameterValue_Int("twoPointsHeight");

    InitializeTimmings();
    // Validacoes
    if (m_iMinReleaseTime == 0)
    {
        throw PK::PK_GameException("Parameter 'minReleaseTime' cannot be 0.", __FILE__, __LINE__);
    }
}

//
void FC_GameSettings::InitializeTimmings()
{
    PK::PK_List<PK::PK_DataFileRecord *> list;
    SelectRecords("levelTimmings/level", list);
    m_LevelTimmings.SetSize(list.GetCount());
    int i = 0;
    for(PK_ListIterator(PK::PK_DataFileRecord *) itor = list.Begin(); itor != list.End(); itor++, i++)
    {
        FC_tTimmingEntry item;
        item._level = FC_TypeConverters::StrToTimmingLevel((*itor)->GetFieldValue_String("type"));
        item._iTimeInMsecs = (*itor)->GetFieldValue_Int("time");
        m_LevelTimmings[(int)item._level] = item;
    }
}

