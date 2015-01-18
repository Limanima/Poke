#include "PK_AndroidPlayer.h"
#include "PK_Exceptions.h"
#include "android/PK_JNIInterface.h"
#include "PK_Log.h"
#include "PK_Web.h"
#include "PK_MessageBox.h"


// Basicamente um wrapper para o java
namespace PK {

PK_AndroidPlayer::PK_AndroidPlayer()
{
	SetTypeName("PK_AndroidPlayer");
	m_playerClass = NULL;
	m_javaPlayer = NULL;
	CreateJavaObject();
}

//
PK_AndroidPlayer::~PK_AndroidPlayer()
{
	JNIEnv *pjniEnv = GetJNIENV();
	if (m_playerClass != NULL)
	{
		pjniEnv->DeleteGlobalRef(m_playerClass);
	}
	if (m_javaPlayer != NULL)
	{
		pjniEnv->DeleteGlobalRef(m_javaPlayer);
	}
}

//
void PK_AndroidPlayer::Authenticate(bool showErrorDialog)
{
	if (PK_Web::WithInternetConnection() == false)
	{
		if (showErrorDialog)
		{
			PK_MessageBox::Show("Login error", "Cannot login to Google Play because there's no internet connection.");
		}
		return;
	}
	PK_Player::Authenticate(showErrorDialog);
	PK_Log::WriteInfo(PK_LOG_TAG, "Going to authenticate user in Google Play.");
	JNIEnv *pjniEnv = GetJNIENV();
	pjniEnv->CallVoidMethod(m_javaPlayer, m_doSignInMethod);
}

//
void PK_AndroidPlayer::SignOut()
{
	PK_Log::WriteInfo(PK_LOG_TAG, "Going to sign out from Google Play.");
	JNIEnv *pjniEnv = GetJNIENV();
	pjniEnv->CallVoidMethod(m_javaPlayer, m_doSignOutMethod);
	GamerServicesLogout();
}

//
bool PK_AndroidPlayer::IsAuthenticated()
{
	if (PK_Web::WithInternetConnection() == false) // A classe helper devolve true quando esta em estado de connecting.
	{
		return false;
	}
	PK_Log::WriteInfo(PK_LOG_TAG, "Check if user is authenticated on Google Play.");
	JNIEnv *pjniEnv = GetJNIENV();
	jboolean isAuthenticated = pjniEnv->CallBooleanMethod(m_javaPlayer, m_isSignedInMethod);
	PK_Log::WriteInfo(PK_LOG_TAG, "Player is authenticated: %s", (isAuthenticated != JNI_FALSE? "true": "false"));
    return (isAuthenticated != JNI_FALSE);
}
    
//
bool PK_AndroidPlayer::SupportsAuthentication()
{
    return true;
}

//
void PK_AndroidPlayer::CreateJavaObject()
{
	JNIEnv *pjniEnv = GetJNIENV();
	jclass cls = pjniEnv->FindClass("limanima/FatCatsAndMice/app/PKaPlayer");
    if (cls == NULL)
    {
		throw PK_JNIException(JNIException_ClassNotF, "limanima/FatCatsAndMice/app/PKaPlayer", __FILE__, __LINE__);
    }
    m_playerClass = static_cast<jclass>(pjniEnv->NewGlobalRef(cls));

    jmethodID method = pjniEnv->GetStaticMethodID(m_playerClass, "CreateInstance", "(J)Llimanima/FatCatsAndMice/app/PKaPlayer;");
    if (method == NULL)
    {
		throw PK_JNIException(JNIException_MethodNotF, "CreateInstance", __FILE__, __LINE__);
    }

    jobject obj = pjniEnv->CallStaticObjectMethod(m_playerClass, method, (long long)this);
    if (obj == NULL)
    {
		throw PK_JNIException(JNIException_MethodError, "CreateInstance", __FILE__, __LINE__);
    }
    m_javaPlayer = static_cast<jobject>(pjniEnv->NewGlobalRef(obj));

    m_isSignedInMethod = pjniEnv->GetMethodID(m_playerClass, "IsSignedIn", "()Z");
    if (m_isSignedInMethod == NULL)
    {
		throw PK_JNIException(JNIException_MethodNotF, "IsSignedIn", __FILE__, __LINE__);
    }

    m_doSignInMethod = pjniEnv->GetMethodID(m_playerClass, "DoSignIn", "()V");
    if (m_doSignInMethod == NULL)
    {
		throw PK_JNIException(JNIException_MethodNotF, "DoSignIn",__FILE__, __LINE__);
    }

    m_doSignOutMethod = pjniEnv->GetMethodID(m_playerClass, "DoSignOut", "()V");
    if (m_doSignOutMethod == NULL)
    {
        throw PK_JNIException(JNIException_MethodNotF, "DoSignOut",__FILE__, __LINE__);
    }
}

} // namespace
