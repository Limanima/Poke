#include "PK_AudioManagerSettings.h"
#include "PK_Profiler.h"

namespace PK {

PK_AudioManagerSettings::PK_AudioManagerSettings() :
 PK_Settings(PK_AUDIO_MANAGER_SETTINGS_NAME, "pokeSettings/audioManager")
{
    SetTypeName("PK_AudioManagerSettings");	
}

//
void PK_AudioManagerSettings::OnLoad()
{
    m_iAudioRate = GetParameterValue_Int("audioRate");
    m_usAudioFormat = GetParameterValue_Int("audioFormat");
    m_iAudioChannels = GetParameterValue_Int("audioChannels");
    m_iAudioBuffers = GetParameterValue_Int("audioBuffers");
}

}