#include "PK_AdBannerControl.h"
#include "PK_AdBanner.h"

namespace PK {

//
PK_AdBannerControl::PK_AdBannerControl(const PK_String &sName, const PK_String &sAdId) :
   PK_2DSceneControl(sName)
{
	SetTypeName("PK_AdBannerControl");
    m_pBanner = new PK_AdBanner(sName + "_banner", sAdId, AdDock_Top);
    m_pBanner->Grab();
}

//
PK_AdBannerControl::~PK_AdBannerControl()
{
    m_pBanner->Release();
}


} // namespace