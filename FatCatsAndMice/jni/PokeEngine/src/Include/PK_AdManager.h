#ifndef _PK_ADMANAGER_H_
#define _PK_ADMANAGER_H_

#include "PK_Component.h"
#include "PK_Types.h"

namespace PK {

class PK_AdBanner;
class PK_Scene;
class PK_Sprite;
class PK_TimerControl;
class PK_OfflineAdBanner;

class PK_AdManager : public PK_Component
{
protected:

private:
    PK_Scene            *m_pScene;
    PK_AdBanner         *m_pAdBanner;
    PK_OfflineAdBanner  *m_pAdSprite;
    PK_TimerControl     *m_pTimer; // Usado para fazer retries
    PK_List<PK_OfflineAdBanner *> m_OfflineAds;
    PK_ListIterator(PK_OfflineAdBanner *)  m_currentOffLineAdItor;
    int m_iOfflineAdsCounter;
    int m_iOnLineAdsShown;
    bool                 m_BannersVisible;

public:
    PK_AdManager(const PK_String &sName);
    ~PK_AdManager();
    
    void OnInitialize();
    void OnUnload();
    void OnUnInitialize();
    void OnUpdate(const PK_GameTimer &timer);
    void OnDraw();
    void SetBanner(const PK_String &sName, const PK_String &sAdId, PK_AdDock dockStyle);
    void ShowBanner();
    void HideBanner();
    void AdBanner_RequestError(PK::PK_Object &sender);
    void AdBanner_RequestSuccess(PK::PK_Object &sender);
    void RetryTimer_Timer(PK::PK_Object &sender);
    void AddOfflineAd(PK_OfflineAdBanner &aAd);
    void OfflineAd_LastFrame(PK::PK_Object &sender);


private:
    void SetOffLineBanner(PK_OfflineAdBanner &sprite);
    void IncrementOfflineAd();
};

}

#endif
