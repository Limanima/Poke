#include "PK_AndroidLeaderboard.h"
#include "PK_Exceptions.h"
#include "android/PK_JNIInterface.h"
#include "PK_Log.h"
#include "PK_Globals.h"
#include "PK_Player.h"
#include "PK_Web.h"
#include "PK_MessageBox.h"

namespace PK {

//
PK_AndroidLeaderboard::PK_AndroidLeaderboard(const PK_String &sName, const PK_String &sId) :
    PK_Leaderboard(sName,  sId)
{
	SetTypeName("PK_AndroidLeaderboard");
	m_javaClass = NULL;
	m_javaObject = NULL;
	CreateJavaObject();
}

//
PK_AndroidLeaderboard::~PK_AndroidLeaderboard()
{
	JNIEnv *pjniEnv = GetJNIENV();
	if (m_javaClass != NULL)
	{
		pjniEnv->DeleteGlobalRef(m_javaClass);
	}
	if (m_javaObject != NULL)
	{
		pjniEnv->DeleteGlobalRef(m_javaObject);
	}
}

//
bool PK_AndroidLeaderboard::SubmitScore(int iScore)
{
	PK_Log::WriteInfo(PK_LOG_TAG, "Going to subit score to leaderboard '%s'. Score is '%d'.", GetId().c_str(), iScore);
	JNIEnv *pjniEnv = GetJNIENV();
	jboolean bRet = pjniEnv->CallBooleanMethod(m_javaObject, m_submitScoreMethod, iScore);
    return (bRet != JNI_FALSE);
}
    
//
bool PK_AndroidLeaderboard::Show()
{
	PK_Log::WriteInfo(PK_LOG_TAG, "Going to show leaderboard '%s'.", GetId().c_str());
    if (PK_Web::WithInternetConnection() == false)
    {
        PK_MessageBox::Show(PK_CAPTION_NO_NET, PK_MESSAGE_NO_NET_LEADERBOARDS);
        return false;
    }

    if (PK::PokeEngine.GetPlayer().IsAuthenticated() == false)
    {
     	PK::PK_Log::WriteInfo("FC", "Autenticar com query.");
        PK::PokeEngine.GetPlayer().AuthenticateWithQuery(PK::AuthenticateReason_LeaderboardsAccess);
        return false;
    }

    JNIEnv *pjniEnv = GetJNIENV();
	jboolean bRet = pjniEnv->CallBooleanMethod(m_javaObject, m_showMethod);
    return (bRet != JNI_FALSE);
}
    
//
bool PK_AndroidLeaderboard::CanSubmitScore()
{
	return PokeEngine.GetPlayer().IsAuthenticated();
}
    
//
bool PK_AndroidLeaderboard::CanShow()
{
	return PokeEngine.GetPlayer().IsAuthenticated();
}

//
bool PK_AndroidLeaderboard::IsSupported()
{
    return true;
}

//
void PK_AndroidLeaderboard::CreateJavaObject()
{
	JNIEnv *pjniEnv = GetJNIENV();
	jclass cls = pjniEnv->FindClass("limanima/FatCatsAndMice/app/PKaLeaderboard");
    if (cls == NULL)
    {
		throw PK_JNIException(JNIException_ClassNotF, "limanima/FatCatsAndMice/app/PKaLeaderboard", __FILE__, __LINE__);
    }
    m_javaClass = static_cast<jclass>(pjniEnv->NewGlobalRef(cls));

    jmethodID method = pjniEnv->GetStaticMethodID(m_javaClass, "CreateInstance", "(JLjava/lang/String;)Llimanima/FatCatsAndMice/app/PKaLeaderboard;");
    if (method == NULL)
    {
		throw PK_JNIException(JNIException_MethodNotF, "CreateInstance", __FILE__, __LINE__);
    }

    jstring leaderboardId = pjniEnv->NewStringUTF(GetId().c_str());
    jobject obj = pjniEnv->CallStaticObjectMethod(m_javaClass, method, (long long)this, leaderboardId);
    if (obj == NULL)
    {
		throw PK_JNIException(JNIException_MethodError, "CreateInstance", __FILE__, __LINE__);
    }
	pjniEnv->DeleteLocalRef(leaderboardId);
    m_javaObject = static_cast<jobject>(pjniEnv->NewGlobalRef(obj));

    m_showMethod = pjniEnv->GetMethodID(m_javaClass, "Show", "()Z");
    if (m_showMethod == NULL)
    {
		throw PK_JNIException(JNIException_MethodNotF, "Show", __FILE__, __LINE__);
    }

    m_submitScoreMethod = pjniEnv->GetMethodID(m_javaClass, "SubmitScore", "(I)Z");
    if (m_submitScoreMethod == NULL)
    {
		throw PK_JNIException(JNIException_MethodNotF, "SubmitScore",__FILE__, __LINE__);
    }

}

} // namespace
