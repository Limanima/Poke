#include "PK_iOSAdBanner.h"
#include "iOS/PKc_CInterface.h"
#include "PK_Log.h"

namespace PK {
    
//
PK_iOSAdBanner::PK_iOSAdBanner(const PK_String &sName, const PK_String &sAdId, PK_AdDock dockStyle) :
    PK_AdBanner(sName, sAdId, dockStyle)
{
    SetTypeName("PK_iOSAdBanner");
    m_pPKcBanner = NULL;
}
  
//
PK_iOSAdBanner::~PK_iOSAdBanner()
{
        
}
  
//
void PK_iOSAdBanner::Show()
{
    if (m_pPKcBanner == NULL)
    {
        try
        {
            m_pPKcBanner = PKc_AdBanner_Create(*this);
        }
        catch (PK_Exception &ex)
        {
            PK_Log::WriteError("Exception in PK_iOSAdBanner::Show()(). Error was %s", ex.GetMsg().c_str());
        }
    }
    if(m_pPKcBanner != NULL)
    {
        PKc_AdBanner_Show(m_pPKcBanner);
    }
}
  
//
void PK_iOSAdBanner::Hide()
{
    if(m_pPKcBanner != NULL)
    {
        PKc_AdBanner_Hide(m_pPKcBanner);
    }
}

} // namespace