#include "PK_OfflineAdBanner.h"
#include "PK_Web.h"
#include "PK_AppStore.h"

namespace PK
{
    
//
PK_OfflineAdBanner::PK_OfflineAdBanner(const PK_String &sName) :
    PK_Sprite(sName)
{
	SetTypeName("PK_OfflineAdBanner");
    OnClick.Set(new PK::PK_ObjectCallback<PK_OfflineAdBanner>(*this, &PK_OfflineAdBanner::Ad_Click));
    m_ActionType = AdClickAction_None;
}

//
void PK_OfflineAdBanner::Ad_Click(PK::PK_Object &sender)
{
    if (m_sActionData == "")
    {
        return;
    }
    switch(m_ActionType)
    {
        case AdClickAction_OpenAppInStore:
            PK_AppStore::OpenAppPage(GetActionData());
            break;
            
        case AdClickAction_OpenUrl:
            PK_Web::OpenURL(GetActionData());
            break;
            
        default:
            break;
    }
}

} // namespace