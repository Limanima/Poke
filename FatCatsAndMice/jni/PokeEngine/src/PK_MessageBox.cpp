#include "PK_MessageBox.h"
#include "PK_MessageBoxCallback.h"
#include "PK_MessageBox.h"
#include "PK_Log.h"
#include "PK_EventManager.h"
#include "PK_Globals.h"

#ifdef POKE_IOS
	#include "iOS/PKc_CInterface.h"
#elif POKE_ANDROID
	#include "PK_AndroidMessageBox.h"
#elif POKE_WINDOWS
	#include <Windows.h>
#endif

namespace PK
{

bool PK_MessageBox::m_bDialogOpen = false;
PK_Callback<PK_IMessageBoxCallback> *g_pCallback = NULL;

//
void PK_MessageBox::Show(const PK_String &sCaption, const PK_String &sText)
{
	PK_MessageBox::Show(sCaption, sText, "OK", "", "", NULL);
}

//
void PK_MessageBox::Show(const PK_String &sCaption, const PK_String &sText,
                         const PK_String &sButton1Text,
                         const PK_String &sButton2Text,
                         const PK_String &sButton3Text,
                         PK_Callback<PK_IMessageBoxCallback> *pCallback)
{
	#ifdef POKE_WINPHONE
	return;
	#endif
    if (m_bDialogOpen)
    {
        return;
    }
    m_bDialogOpen = true;
    g_pCallback = pCallback;
    PK_Log::WriteInfo(PK_LOG_TAG, "Showing MessageBox '%s', '%s', '%s', '%s', '%s'",
    		sCaption.c_str(), sText.c_str(), sButton1Text.c_str(), sButton2Text.c_str(), sButton3Text.c_str());
#ifdef POKE_IOS
    PKc_ShowMessageBox(sCaption, sText, sButton1Text, sButton2Text, sButton3Text);
#elif POKE_ANDROID
    PK_AndroidMessageBox::Show(sCaption, sText, sButton1Text, sButton2Text, sButton3Text);
#elif POKE_WINDOWS
    MessageBox(NULL, sText.c_str(), sCaption.c_str(), 0);
    // FIXME, isto esta marteladado, devia ver qual o botoa
    InternalDialogClosed(MsgBoxResult_Button1);
#endif
}

    
// static
void PK_MessageBox::InternalDialogClosed(PK_eMsgBoxResult result)
{
    if (g_pCallback != NULL && g_pCallback->HasCallback())
    {
        // Envia um evento para correr na main thread
        PK_tEvent closeEvent;
        PK_tMsgBoxEvent *pMsgBoxEventData = new PK_tMsgBoxEvent();
        pMsgBoxEventData->pCallback = g_pCallback;
        pMsgBoxEventData->result = result;
        closeEvent.iEventCode = PK_EVENT_MESSAGEBOX_CLOSED;
        closeEvent.pEventData = pMsgBoxEventData;
        PokeEngine.GetEventManager().PostEvent(closeEvent);
     //   (*g_pCallback)->Execute(result);
    }
    m_bDialogOpen = false;
}

} // namespace
