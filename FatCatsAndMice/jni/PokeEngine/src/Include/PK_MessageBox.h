#ifndef _PK_MESSAGEBOX_H_
#define _PK_MESSAGEBOX_H_

#include "PK_Callback.h"
#include "PK_MessageBoxCallback.h"
#include "PK_String.h"

namespace PK {


struct PK_tMsgBoxEvent
{
    PK_Callback<PK_IMessageBoxCallback> *pCallback;
    PK_eMsgBoxResult result;
};

//
class PK_MessageBox 
{
    static bool m_bDialogOpen;
    
public:
    static void Show(const PK_String &sCaption, const PK_String &sText);
    static void Show(const PK_String &sCaption, const PK_String &sText,
                                    const PK_String &sButton1Text,
                                    const PK_String &sButton2Text,
                                    const PK_String &sButton3Text,
                                    PK_Callback<PK_IMessageBoxCallback> *pCallback);
    
    inline static bool IsDialogOpen() { return m_bDialogOpen;}
    static void InternalDialogClosed(PK_eMsgBoxResult result);
};

} // namespace

#endif
