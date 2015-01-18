#ifndef _PK_ADBANNER_H_
#define _PK_ADBANNER_H_

#include "PK_Object.h"
#include "PK_Types.h"
#include "PK_Callback.h"
#include "PK_ObjectCallback.h"

namespace PK {    

// Classe base para um asset: textura, sprite, font, etc
class PK_AdBanner : public PK_Object
{
protected:
    PK_String    m_sAdId;
    PK_AdDock    m_dockStyle;

public:
    PK_Callback<PK::PK_IObjectCallback> OnRequestError;
    PK_Callback<PK::PK_IObjectCallback> OnRequestSuccess;

public:
	PK_AdBanner(const PK_String &sName, const PK_String &sAdId, PK_AdDock dockStyle);

	virtual void Show();
    virtual void Hide() {}
    void InvokeOnRequestError();
    void InvokeOnRequestSuccess();
    inline PK_String GetAdId() const { return m_sAdId; }
    inline PK_AdDock GetDockStyle() const { return m_dockStyle; }

};

} // namespace

#endif
