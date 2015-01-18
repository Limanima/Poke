#ifndef _PK_IOSPLAYER_H_
#define _PK_IOSPLAYER_H_

#include "PK_Player.h"

namespace PK {
    
// Classe base para um asset: textura, sprite, font, etc
class PK_iOSPlayer : public PK_Player
{
private:
    bool m_bMustLoginThrowGameCenter; // Ha uma limitacao no Game Center. Se o pop up de login for mostrado
                                      // na app e o user carregar em cancel, as proximas chamadas de authenticate
                                      // nao fazem nada e o user tem que fazer login pelo Came Center
    
protected:

public:
	PK_iOSPlayer();
    void Authenticate(bool showErrorDialog);
    bool IsAuthenticated();
    bool SupportsAuthentication();
    
    inline void SetMustLoginThrowGameCenter() { m_bMustLoginThrowGameCenter = true; }
};

} // namespace

#endif