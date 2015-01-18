#ifndef _PK_IOSADBANNER_H_
#define _PK_IOSADBANNER_H_

#include "PK_AdBanner.h"

namespace PK {

// Classe base para um asset: textura, sprite, font, etc
class PK_iOSAdBanner : public PK_AdBanner
{
private:
    void * m_pPKcBanner; // Obj-C object ptr

public:
	PK_iOSAdBanner(const PK_String &sName, const PK_String &sAdId, PK_AdDock dockStyle);
	 ~PK_iOSAdBanner();

    void Show();
    void Hide();
};

} // namespace

#endif