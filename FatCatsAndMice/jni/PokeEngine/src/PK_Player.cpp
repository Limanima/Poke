#include "PK_Player.h"
#include "PK_MessageBox.h"
#include "PK_Environment.h"
#include "PK_Web.h"
#include "PK_Log.h"
#include "PK_Globals.h"

// 
namespace PK {

//
PK_Player::PK_Player()
{
	SetTypeName("PK_Player");
    OnQueryLoginClosed.Set(new PK::PK_MessageBoxCallback<PK_Player>(*this, &PK_Player::LoginQuery_Closed));
    m_bShowLoginErrorDialog = false;
}

//
void PK_Player::Authenticate(bool showErrorDialog)
{
    m_bShowLoginErrorDialog = showErrorDialog;
    
}

//
void PK_Player::AuthenticateWithQuery(PK_eAuthenticateReason reason, bool bWithNoInternetDialog)
{
    if (!SupportsAuthentication())
    {
    	PK_Log::WriteInfo(PK_LOG_TAG, "Authentication not supported.");
        return;
    }

    if (IsAuthenticated())
    {
    	PK_Log::WriteInfo(PK_LOG_TAG, "Player is authenticated, don't need to ask.");
        return;
    }

    if (PK_Web::WithInternetConnection() == false)
    {
        if (bWithNoInternetDialog)
        {
            PK_String message;
            switch(reason)
            {
                case AuthenticateReason_LeaderboardsPost:
                case AuthenticateReason_LeaderboardsAccess:
                    message = PK_MESSAGE_NO_NET_LEADERBOARDS;
                    break;
            }
            PK_MessageBox::Show(PK_CAPTION_NO_NET, message);
    	}
    	PK_Log::WriteWarning(PK_LOG_TAG, "No internet connection. Cannot authenticate user.");
    	return;
    }

    PK_String message;
    switch (reason)
    {
        case AuthenticateReason_LeaderboardsPost:
            message = "To post scores to the leaderboards you have to login to " + PK_Environment::GetGameServicesName() + ". Login now?";
            break;
            
        case AuthenticateReason_LeaderboardsAccess:
            message = "To have access to leaderboards you have to login to " + PK_Environment::GetGameServicesName() + ". Login now?";
            break;
           
        default:
            break;
    }
    PK_MessageBox::Show("Login In", message,
                        "Yes",
                        "No",
                        "",
                        &OnQueryLoginClosed);

}
    
//
bool PK_Player::IsAuthenticated()
{
    return false;
}

//
bool PK_Player::SupportsAuthentication()
{
    return false;
}

//
void PK_Player::LoginQuery_Closed(PK_eMsgBoxResult res)
{
	switch(res)
	{
		case MsgBoxResult_Button1:
	    	PK_Log::WriteInfo(PK_LOG_TAG, "Player selected YES to login.");
	        Authenticate(true);
			break;
		case MsgBoxResult_Button2:
	    	PK_Log::WriteInfo(PK_LOG_TAG, "Player selected NO to login.");
			break;
        case MsgBoxResult_Button3:
        default:
            break;
	}
}

// Tem que submeter como eventos, isto porque estes callbacks podem ter sido chamadas via java/ObjectiveC e correr noutra thread
void PK_Player::GamerServicesLogin(bool bSuccess)
{
	if (bSuccess)
	{
		PK_Log::WriteInfo(PK_LOG_TAG, "Player signed in to the gamer services.");
	}
	else
	{
		PK_Log::WriteWarning(PK_LOG_TAG, "Error signing in to the gamer services.");
	}

	PK::PK_tEvent evt;
	evt.iEventCode = (bSuccess? PK_EVENT_GAME_SERVICES_LOGIN :PK_EVENT_GAME_SERVICES_LOGIN_ERROR);
	PK::PokeEngine.PostEvent(evt);
    
    if (!bSuccess && m_bShowLoginErrorDialog)
    {
        PK_MessageBox::Show("Login error", PK_String("Could not login to ") + PK_Environment::GetGameServicesName());
    }

}

// Tem que submeter como eventos, isto porque estes callbacks podem ter sido chamadas via java/ObjectiveC e correr noutra thread
void PK_Player::GamerServicesLogout()
{
	PK_Log::WriteInfo(PK_LOG_TAG, "Player signed out from the gamer services.");
	PK::PK_tEvent evt;
	evt.iEventCode = PK_EVENT_GAME_SERVICES_LOGOUT;
	PK::PokeEngine.PostEvent(evt);
}

} // namespace
