#include "PK_AdBanner.h"
#include "PK_Exceptions.h"

namespace PK {

PK_AdBanner::PK_AdBanner(const PK_String &sName, const PK_String &sAdId, PK_AdDock dockStyle) :
    PK_Object(sName)
{
	SetTypeName("PK_AdBanner");
	if (sAdId == "")
	{
		throw PK_NullArgumentException("sAdId", __FILE__, __LINE__);
	}
	m_sAdId = sAdId;
    m_dockStyle = dockStyle;
}

//
void PK_AdBanner::Show()
{
    InvokeOnRequestError();
}

//
void PK_AdBanner::InvokeOnRequestError()
{
    if (OnRequestError.HasCallback())
    {
        OnRequestError->Execute(*this);
    }
}
    
//
void PK_AdBanner::InvokeOnRequestSuccess()
{
    if (OnRequestSuccess.HasCallback())
    {
        OnRequestSuccess->Execute(*this);
    }
}
} // namespace
