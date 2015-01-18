#include "PK_Rate.h"
#include "PK_Web.h"
#include "PK_Globals.h"
#include "PK_Game.h"
#include "PK_Environment.h"

#ifdef POKE_IOS
  #include "iOS/PKc_CInterface.h"
#endif
#ifdef POKE_WINDOWS
  #define WINDOWS_MEAN_AND_LEAN
  #include <Windows.h>
#endif

namespace PK {

PK_Callback<PK::PK_IMessageBoxCallback> PK_Rate::OnQueryRateClosed;


// static
void PK_Rate::Show()
{
	PK_String sApId;

	OnQueryRateClosed.Set(new PK::PK_MessageBoxCallback<PK_Rate>(&PK_Rate::QueryRate_Closed));
    PK_MessageBox::Show("Please Rate",
    					"Please, rate the game. It will only take a second.\nDo you want to rate?",
                        "Yes",
                        "Later",
                        "Don't Ask",
                        &OnQueryRateClosed);

}
    
//static
void PK_Rate::ShowWithCondition()
{
   
    if (IsSupported() == false)
    {
        return;
    }
    if(PokeEngine.GetSettings().GetRatingEnabled() == false)
    {
        return;
    }
    if (PokeEngine.GetGameData().GetRateDontBother() == true)
    {
        return;
    }
    if(PokeEngine.GetGameData().GetUsesWithoutPrompt() <= PokeEngine.GetSettings().GetUsagesBeforeAskRatingRate())
    {
        return;
    }
    if (PK_Web::WithInternetConnection() == false)
    {
        PK_Web::TestInternetConnectionAsync();
        return;
    }
     
    Show();
}

//
void PK_Rate::QueryRate_Closed(PK_eMsgBoxResult res)
{
	switch(res)
	{
		case MsgBoxResult_Button1:
			OnRateNowPressed();
			break;
		case MsgBoxResult_Button2:
			OnLaterPressed();
			break;
		case MsgBoxResult_Button3:
			OnDontAskPressed();
			break;
        default:
            break;
	}
}

// static
void PK_Rate::OnDontAskPressed()
{
	PK_Log::WriteInfo(PK_LOG_TAG, "'Dont Ask' Pressed");
    PokeEngine.GetGameData().SetRateDontBother(true);
    PokeEngine.GetGameData().Save();
}
    
// static
void PK_Rate::OnLaterPressed()
{
	PK_Log::WriteInfo(PK_LOG_TAG, "'Later' Pressed");
    PokeEngine.GetGameData().ResetRateUsesUntilPrompt();
    PokeEngine.GetGameData().Save();
}

// static
void PK_Rate::OnRateNowPressed()
{
   PK_Log::WriteInfo(PK_LOG_TAG, "'Yes' Pressed");
   PokeEngine.GetGame().OpenInAppStore();
}

// static 
bool PK_Rate::IsSupported()
{
    return (PK_Environment::IsAndroid() || PK_Environment::IsiOS());
}

}

// namespace
