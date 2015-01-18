#ifndef _PK_RATE_H_
#define _PK_RATE_H_

#include "PK_MessageBox.h"

namespace PK {    

// Classe base para um asset: textura, sprite, font, etc
class PK_Rate
{
	static PK_Callback<PK::PK_IMessageBoxCallback> OnQueryRateClosed;

public:
    static void Show();
    static void ShowWithCondition();
    static bool IsSupported();

private:
    static void QueryRate_Closed(PK_eMsgBoxResult res);
    static void OnDontAskPressed();
    static void OnLaterPressed();
    static void OnRateNowPressed();

};

} // namespace

#endif
