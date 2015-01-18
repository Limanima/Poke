#include "PK_iOSPlayer.h"
#include "iOS/PKc_CInterface.h"
#include "PK_MessageBox.h"

// Basicamente um wrapper para o Objective-C
namespace PK {

PK_iOSPlayer::PK_iOSPlayer()
{
	SetTypeName("PK_iOSPlayer");
 }
    
//
void PK_iOSPlayer::Authenticate(bool showErrorDialog)
{
    PK_Player::Authenticate(showErrorDialog);
    PKc_PlayerAuthentication_AuthenticateUser();
}
    
//
bool PK_iOSPlayer::IsAuthenticated()
{
    return PKc_PlayerAuthentication_IsAuthenticated();
}
    
//
bool PK_iOSPlayer::SupportsAuthentication()
{
    return true;
}

} // namespace