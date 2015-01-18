#include "PK_AndroidWeb.h"
#include "android/PK_JNIInterface.h"
#include "PK_Exceptions.h"
#include "PK_Consts.h"
#include "PK_Log.h"

namespace PK 
{

jclass  PK_AndroidWeb::m_javaClass = NULL;
jmethodID PK_AndroidWeb::m_withInternetConnectionMethod = NULL;
jmethodID PK_AndroidWeb::m_openURLMethod = NULL;

//static
// Tem que ser chamado da thread principal, isot porque o FindClass so funciona assim
void PK_AndroidWeb::Initialize()
{
	if(m_javaClass != NULL)
	{
		throw PK_SystemException("PK_AndroidWeb() already initialized.", __FILE__, __LINE__);
	}

	JNIEnv * pjniEnv = GetJNIENV();
	jclass cls = pjniEnv->FindClass("limanima/FatCatsAndMice/app/PKaWeb");
	if (cls == NULL)
	{
		throw PK_JNIException(JNIException_ClassNotF, "limanima/FatCatsAndMice/app/PKaWeb", __FILE__, __LINE__);
	}
	m_javaClass = static_cast<jclass>(pjniEnv->NewGlobalRef(cls));

	m_withInternetConnectionMethod = pjniEnv->GetStaticMethodID(m_javaClass, "WithInternetConnection", "()Z");
	if (m_withInternetConnectionMethod == NULL)
	{
		throw PK_JNIException(JNIException_MethodNotF, "WithInternetConnection", __FILE__, __LINE__);
	}

	m_openURLMethod = pjniEnv->GetStaticMethodID(m_javaClass, "OpenURL", "(Ljava/lang/String;)V");
	if (m_openURLMethod == NULL)
	{
		throw PK_JNIException(JNIException_MethodNotF, "OpenURL", __FILE__, __LINE__);
	}
}

//static
void PK_AndroidWeb::UnInitialize()
{

}

// static
// Nao e bem uma thread, mas e chamado da thread que testa as comms
// mas no fundo e a thread para o android
bool PK_AndroidWeb::TestInternetConnectionThread()
{
	if (m_javaClass == NULL)
	{
		throw PK_SystemException("PK_AndroidWeb not initialized. Call PK_AndroidWeb::Initialize().", __FILE__, __LINE__);

	}
	JNIEnv *pjniEnv = GetJNIENV();

    jboolean bRet = pjniEnv->CallStaticBooleanMethod(m_javaClass, m_withInternetConnectionMethod);

    PKa_DettachCurrentThreadFromJVM();

	return (bRet != JNI_FALSE);
}

// static
void PK_AndroidWeb::OpenURL(const PK_String &sURL)
{
	if (m_javaClass == NULL)
	{
		throw PK_SystemException("PK_AndroidWeb not initialized. Call PK_AndroidWeb::OpenURL().", __FILE__, __LINE__);
	}
	JNIEnv *pjniEnv = GetJNIENV();

	jstring url = pjniEnv->NewStringUTF(sURL.c_str());

	PK_Log::WriteInfo(PK_LOG_TAG, "Opening url '%s' thru JNI.", sURL.c_str());
	pjniEnv->CallStaticVoidMethod(m_javaClass, m_openURLMethod, url);

	pjniEnv->DeleteLocalRef(url);
}

} // namespace
