#include "PK_AdManager.h"
#include "PK_ClassFactory.h"
#include "PK_AdBanner.h"
#include "PK_Sprite.h"
#include "PK_Scene.h"
#include "PK_TimerControl.h"
#include "PK_OfflineAdBanner.h"
#include "PK_Globals.h"

#define RETRY_TIME 60000
namespace PK {

//   
PK_AdManager::PK_AdManager(const PK_String &sName) :
  PK_Component(sName)
{
    m_pScene = new PK_Scene(sName + "_scene__");
    m_pScene->Grab();

    m_pAdBanner = NULL;
    m_pAdSprite = NULL;
    m_iOnLineAdsShown = 0;
    m_BannersVisible = false;
    
    m_pTimer = new PK_TimerControl(sName + "_retryTimer");
    m_pTimer->SetAlarmTime(RETRY_TIME);
    m_pTimer->SetEnabled(false);
    m_pTimer->SetWithSnooze(false);
    m_pTimer->OnTimer.Set(new PK::PK_ObjectCallback<PK_AdManager>(*this, &PK_AdManager::RetryTimer_Timer));
    m_pScene->AddControl(m_pTimer);
    
}

//
PK_AdManager::~PK_AdManager()
{
    if (m_pScene != NULL)
    {
        m_pScene->Release();
    }
    OnUnInitialize();
}

//
void PK_AdManager::OnInitialize()
{
    m_pScene->InternalInitialize();
}

//
void PK_AdManager::OnUnload()
{
    m_pScene->InternalUnload();
}

//
void PK_AdManager::OnUnInitialize()
{

    if (m_pAdBanner != NULL)
    {
        PK_FREE(m_pAdBanner);
    }

    if (m_OfflineAds.GetCount() > 0)
    {
        for(PK_ListIterator(PK_OfflineAdBanner *) itor = m_OfflineAds.Begin(); itor != m_OfflineAds.End(); itor++)
        {
            (*itor)->Release();
        }
        m_OfflineAds.Clear();
    }
}

//
void PK_AdManager::OnUpdate(const PK_GameTimer &timer)
{
    m_pScene->InternalUpdate(timer);

    if (m_pAdSprite == NULL && m_OfflineAds.GetCount() > 0)
    {
        m_currentOffLineAdItor = m_OfflineAds.Begin();
        SetOffLineBanner(*(*m_currentOffLineAdItor));
    }
}

//
void PK_AdManager::OnDraw()
{
    m_pScene->InternalDraw();
}


//
void PK_AdManager::SetBanner(const PK_String &sName, const PK_String &sAdId, PK_AdDock dockStyle)
{
    if (m_pAdBanner != NULL)
    {
        m_pAdBanner->Release();
    }
    m_pAdBanner = PK_ClassFactory::CreateAdBanner(sName, sAdId, dockStyle);
    m_pAdBanner->Grab();
    m_pAdBanner->OnRequestError.Set(new PK::PK_ObjectCallback<PK_AdManager>(*this, &PK_AdManager::AdBanner_RequestError));
    m_pAdBanner->OnRequestSuccess.Set(new PK::PK_ObjectCallback<PK_AdManager>(*this, &PK_AdManager::AdBanner_RequestSuccess));
}

//
void PK_AdManager::SetOffLineBanner(PK_OfflineAdBanner &sprite)
{
    if (m_pAdSprite != NULL)
    {
        m_pAdSprite->RemoveFromScene();
    }
    sprite.SetCurrentFrame(0);
    sprite.SetVisible(false);
    sprite.SetUpdateWhenHidden(false);
    m_pScene->AddControl(&sprite);
    sprite.Invalidate();
    m_pAdSprite = &sprite;
}

//
void PK_AdManager::ShowBanner()
{
    if (!IsActive())
    {
        return;
    }
	if (m_BannersVisible)
	{
		return;
	}
	// Mostramos logo o offline ad se existir, isto porque o online pode demorar algum tempo a aparecer
	if (m_pAdSprite != NULL)
    {
		m_pAdSprite->SetVisible(true);
    }
    if (m_pAdBanner != NULL)
    {
        m_pAdBanner->Show();
    }
    m_BannersVisible = true;
}

//
void PK_AdManager::HideBanner()
{
    if (m_pAdBanner != NULL)
    {
        m_pAdBanner->Hide();
    }
    if (m_pAdSprite != NULL)
    {
       m_pAdSprite->SetVisible(false);
    }
    m_pTimer->SetEnabled(false);
    m_BannersVisible = false;
}

//
void PK_AdManager::AdBanner_RequestError(PK::PK_Object &sender)
{
	// Os ads podem ter sido escondidos entretanto
	if (m_BannersVisible == false)
	{
		return;
	}

    if (m_pAdSprite != NULL)
    {
        m_pAdSprite->SetVisible(true);
        m_pAdSprite->Invalidate();
        m_pTimer->Reset();
        m_pTimer->SetEnabled(true);
    }
}
    
//
void PK_AdManager::AdBanner_RequestSuccess(PK::PK_Object &sender)
{
	// Os ads podem ter sido escondidos entretanto
	if (m_BannersVisible == false)
	{
		return;
	}

	if (m_pAdSprite != NULL)
    {
        m_iOnLineAdsShown++;
        if (m_iOnLineAdsShown > PokeEngine.GetSettings().GetOfflineAdStep())
        {
            IncrementOfflineAd();
            (*m_currentOffLineAdItor)->SetVisible(true);
            m_pAdBanner->Hide();
            m_iOnLineAdsShown = 0;
        }
        else
        {
            m_pAdSprite->SetVisible(false);
        }
    }
}
    
//
void PK_AdManager::RetryTimer_Timer(PK::PK_Object &sender)
{
    ShowBanner();
}

//
void PK_AdManager::AddOfflineAd(PK_OfflineAdBanner &ad)
{
    // Confirmar que nao esta ja adicionado
    for(PK_ListIterator(PK_OfflineAdBanner *) itor = m_OfflineAds.Begin(); itor != m_OfflineAds.End(); itor++)
    {
        if (&ad == (*itor))
        {
            throw PK_SystemException("Cannot add ad named '%s' to the Ad Manager because it's already added.", __FILE__, __LINE__, ad.GetName().c_str());
        }
    }
    m_OfflineAds.Add(&ad);
    ad.Grab();
    ad.OnLastFrame.Set(new PK::PK_ObjectCallback<PK_AdManager>(*this, &PK_AdManager::OfflineAd_LastFrame));
    ad.InternalInitialize();
    ad.InternalLoad();
}

//
void PK_AdManager::OfflineAd_LastFrame(PK::PK_Object &sender)
{
    ShowBanner();
}

//
void PK_AdManager::IncrementOfflineAd()
{
    // Se so tem um ad, n precisa de passar para o proximo
    if (m_OfflineAds.GetCount() == 1)
    {
        return;
    }

    m_currentOffLineAdItor++;
    if (m_currentOffLineAdItor == m_OfflineAds.End())
    {
        m_currentOffLineAdItor = m_OfflineAds.Begin();
    }
    SetOffLineBanner(*(*m_currentOffLineAdItor));
}


} // namespace
