#include "PK_ProfilerSettings.h"
#include "PK_Log.h"

namespace PK {

PK_ProfilerSettings::PK_ProfilerSettings() :
 PK_Settings(PK_PROFILER_SETTINGS_NAME, "pokeSettings/profiler")
{
    SetTypeName("PK_ProfilerSettings");
}

//
void PK_ProfilerSettings::OnLoad()
{
    m_bEnabled = GetParameterValue_Bool("enabled");
    m_bRemoteDebbugerEnabled = GetParameterValue_Bool("remoteDebugger", "enabled");
    m_iServerPort = GetParameterValue_Int("remoteDebugger", "serverPort");
    m_sServerName = GetParameterValue_String("remoteDebugger", "serverName");

    PK_Log::WriteInfo(PK_LOG_TAG, "Profiler Settings:");
    PK_Log::WriteInfo(PK_LOG_TAG, " enabled: %d", m_bEnabled);
    PK_Log::WriteInfo(PK_LOG_TAG, " remoteDebugger->enabled: %d", m_bRemoteDebbugerEnabled);
    if (m_bRemoteDebbugerEnabled)
    {
        PK_Log::WriteInfo(PK_LOG_TAG, " remoteDebugger->serverPort: %d", m_iServerPort);
        PK_Log::WriteInfo(PK_LOG_TAG, " remoteDebugger->serverName: %s", m_sServerName.c_str());
    }
}

}