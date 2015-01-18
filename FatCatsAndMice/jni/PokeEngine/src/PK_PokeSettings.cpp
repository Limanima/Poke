#include "PK_Globals.h"
#include "PK_PokeSettings.h"
#include "PK_Profiler.h" 
#include "PK_Environment.h"

namespace PK {
     
PK_PokeSettings::PK_PokeSettings() :
    PK_Settings(PK_POKE_SETTINGS_NAME, "pokeSettings")
{
    SetTypeName("PK_PokeSettings");
	m_uiFPS = 30;
	m_bLockFPS = true;
    m_bUpscale = false;
    m_bProfilerEnabled = false;
    m_bWithAdvertising = false;
    m_iOfflineAdStep = 5;
    m_bForceWindowSize = false;
    m_windowSize.Set(0, 0);
    m_bSplashEnabled = false;
    m_splashBackcolor = PK_COLOR_WHITE;    
}

//
void PK_PokeSettings::OnLoad()
{
    m_uiFPS = GetParameterValue_Int("fps");
	m_bLockFPS = GetParameterValue_Bool("lockFPS");
    m_gameResolution = GetParameterValue_Size("gameResolution");
    m_GameOrientation = (m_gameResolution.w > m_gameResolution.h? DeviceOrientation_Landscape : DeviceOrientation_Portait);
    m_bUpscale = GetParameterValue_Bool("doUpscale");
    m_bWithOnlineServices = GetParameterValue_Bool("withOnlineServices");
    m_bProfilerEnabled = GetParameterValue_Bool("profiler", "enabled");
    m_bForceWindowSize = GetParameterValue_Bool("forceWindowSize");
    m_windowSize = GetParameterValue_Size("windowSize");
    m_sAppId = GetParameterValue_String("appId");
    
    // Rate
    m_bRatingEnabled = GetParameterValue_Bool("rating", "enabled", false);
    m_iUsagesBeforeAskRating = GetParameterValue_Int("rating", "usagesBeforeAsking", 5);
  
    // Splash
    m_bSplashEnabled = GetParameterValue_Bool("splashScreen", "enabled", false);
    if (PK_Environment::GetPlatform() == Platform_iOS)
    {
        m_bSplashEnabled = false;
    }
    
    if (m_bSplashEnabled)
    {
        m_sSplashSprite = GetParameterValue_String("splashScreen", "sprite");
        m_splashBackcolor = GetParameterValue_Color("splashScreen", "backcolor", PK_COLOR_WHITE);
    }

    InitializeAdvertisingSettings();
}
 
//
void PK_PokeSettings::InitializeAdvertisingSettings()
{
    m_adTestDeviceUUIDs.Clear();
    PK_DataFileRecord *pAdvertisingRecord = GetRecord("advertising");
    if (pAdvertisingRecord == NULL)
    {
        return;
    }
    m_bWithAdvertising = GetParameterValue_Bool("advertising", "enabled");
    m_iOfflineAdStep = GetParameterValue_Int("advertising", "offlineAdStep");
    PK_DataFileRecord *pDeviceIdsRecord = pAdvertisingRecord->SelectRecord("testDevicesUUIDs");
    if (pDeviceIdsRecord != NULL)
    {
        // Advertising
        PK_List<PK_DataFileRecord *> idsRecs;
        pDeviceIdsRecord->SelectRecords("deviceUUID", idsRecs, false);
        for(PK_ListIterator(PK_DataFileRecord *) itor = idsRecs.Begin(); itor != idsRecs.End(); itor++)
        {
            PK_DataFileRecord *pRec = (*itor);
            m_adTestDeviceUUIDs.Add(pRec->GetFieldValue_String("value"));
        }
    }
}

  
}