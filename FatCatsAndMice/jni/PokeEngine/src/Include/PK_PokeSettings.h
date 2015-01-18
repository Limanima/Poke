#ifndef _PK_POKESETTINGS_H_
#define _PK_POKESETTINGS_H_

#include "PK_Settings.h"
#include "PK_tSize.h"
#include "PK_Types.h"

namespace PK {
    
class PK_DataFileRecord;
  
class PK_PokeSettings : public PK_Settings
{
private:

	PK_tSize m_gameResolution;
	PK_List<PK_tNamedResolution> m_SupportedResolution;
    PK_eDeviceOrientation m_GameOrientation;
    unsigned int    m_uiFPS;
    bool            m_bLockFPS;
    bool            m_bUpscale;
    bool            m_bWithOnlineServices;
    bool            m_bProfilerEnabled;
    bool            m_bForceWindowSize;
    PK_tSize        m_windowSize;
    PK_String       m_sAppId;
    
    // Rate
    bool            m_bRatingEnabled;
    int             m_iUsagesBeforeAskRating;

    // Splash
    bool            m_bSplashEnabled;
    PK_String       m_sSplashSprite;
    PK_Color        m_splashBackcolor;
    

    // FIXME! criar settings para ad manager
    // Advertising
    PK_List<PK_String> m_adTestDeviceUUIDs;
    bool            m_bWithAdvertising;
    int             m_iOfflineAdStep;
    
public:
	PK_PokeSettings();
    void OnLoad();

private:
    void InitializeAdvertisingSettings();

public:
    PK_tNamedResolution GetSupportedResolutionByName(const PK_String &sName);
 
    inline PK_eDeviceOrientation GetGameOrientation() { return m_GameOrientation; }
    inline PK_tSize GetGameResolution() { return m_gameResolution; }
    inline unsigned int GetFPS() { return m_uiFPS; }
	inline bool GetLockFPS() { return m_bLockFPS; }
	inline bool GetUpscaleFlag() { return m_bUpscale; }
	inline bool GetWithOnlineServices() { return m_bWithOnlineServices; }
	inline bool GetProfilerEnabled() { return m_bProfilerEnabled; }
    inline bool GetWithAdvertising() { return m_bWithAdvertising; }
	inline int GetOfflineAdStep() { return m_iOfflineAdStep; }
	inline bool GetForceWindowSize() { return m_bForceWindowSize; }
    inline PK_tSize GetWindowSize() { return m_windowSize; }
    inline PK_String GetAppId() { return m_sAppId; }

    // Rate
    inline bool GetRatingEnabled() { return m_bRatingEnabled; }
    inline int GetUsagesBeforeAskRatingRate() { return m_iUsagesBeforeAskRating; }
 
    // Splash
    inline bool GetSplashEnabled() { return m_bSplashEnabled; }
    inline PK_String GetSplashSprite() { return m_sSplashSprite; }
    inline PK_Color GetSplashBackColor() { return m_splashBackcolor; }

    inline PK_List<PK_String> const &GetAdTestDeviceUUIDs() const { return m_adTestDeviceUUIDs; }
};

}
#endif
