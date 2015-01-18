#ifndef _PK_ANDROIDPLAYER_H_
#define _PK_ANDROIDPLAYER_H_

#include "PK_Player.h"
#include <jni.h>

namespace PK {
    
// Classe base para um asset: textura, sprite, font, etc
class PK_AndroidPlayer : public PK_Player
{
private:
	jobject m_javaPlayer;
	jclass  m_playerClass;
	jmethodID m_isSignedInMethod;
	jmethodID m_doSignInMethod;
	jmethodID m_doSignOutMethod;

public:
	PK_AndroidPlayer();
	~PK_AndroidPlayer();
    void Authenticate(bool showErrorDialog);
    void SignOut();
    bool IsAuthenticated();
    bool SupportsAuthentication();

private:
    void CreateJavaObject();
};

} // namespace

#endif
