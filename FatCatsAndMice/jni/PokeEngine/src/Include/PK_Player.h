#ifndef _PK_PLAYER_H_
#define _PK_PLAYER_H_

#include "PK_Object.h"
#include "PK_MessageBoxCallback.h"

namespace PK {
    
enum PK_eAuthenticateReason
{
    AuthenticateReason_LeaderboardsAccess,
    AuthenticateReason_LeaderboardsPost
};
    
// Classe base para um asset: textura, sprite, font, etc
class PK_Player : public PK_Object
{
private:
    bool m_bShowLoginErrorDialog;
    PK_Callback<PK::PK_IMessageBoxCallback> OnQueryLoginClosed;

public:
	PK_Player();
    virtual void Authenticate(bool showErrorDialog);
    virtual void AuthenticateWithQuery(PK_eAuthenticateReason reason, bool bWithNoInternetDialog = true);
    virtual void SignOut() { };
    virtual bool IsAuthenticated();
    virtual bool SupportsAuthentication();
    void LoginQuery_Closed(PK_eMsgBoxResult res);
    void GamerServicesLogin(bool bSuccess);
    void GamerServicesLogout();

};

} // namespace

#endif
