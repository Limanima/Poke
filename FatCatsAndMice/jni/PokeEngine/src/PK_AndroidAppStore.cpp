#include "PK_AndroidAppStore.h"
#include "android/PK_JNIInterface.h"
#include "PK_Exceptions.h"
#include "PK_Consts.h"
#include "PK_Log.h"

namespace PK 
{

jclass  PK_AndroidAppStore::m_javaClass = NULL;
jmethodID PK_AndroidAppStore::m_OpenAppPageMethod = NULL;

//static
// Tem que ser chamado da thread principal, isot porque o FindClass so funciona assim
void PK_AndroidAppStore::Initialize()
{
	if(m_javaClass != NULL)
	{
		throw PK_SystemException("PK_AndroidAppStore() already initialized.", __FILE__, __LINE__);
	}

	JNIEnv * pjniEnv = GetJNIENV();
	jclass cls = pjniEnv->FindClass("limanima/FatCatsAndMice/app/PKaAppStore");
	if (cls == NULL)
	{
		throw PK_JNIException(JNIException_ClassNotF, "limanima/FatCatsAndMice/app/PKaAppStore", __FILE__, __LINE__);
	}
	m_javaClass = static_cast<jclass>(pjniEnv->NewGlobalRef(cls));

	m_OpenAppPageMethod = pjniEnv->GetStaticMethodID(m_javaClass, "OpenAppPage", "(Ljava/lang/String;)V");
	if (m_OpenAppPageMethod == NULL)
	{
		throw PK_JNIException(JNIException_MethodNotF, "OpenAppPage", __FILE__, __LINE__);
	}
}

//static
void PK_AndroidAppStore::UnInitialize()
{

}

// static
void PK_AndroidAppStore::OpenAppPage(const PK_String &sAppId)
{
	if (m_javaClass == NULL)
	{
		throw PK_SystemException("PK_AndroidAppStore not initialized. Call PK_AndroidAppStore::OpenURL().", __FILE__, __LINE__);
	}
	JNIEnv *pjniEnv = GetJNIENV();

	jstring appId = pjniEnv->NewStringUTF(sAppId.c_str());

	PK_Log::WriteInfo(PK_LOG_TAG, "Opening app page with id '%s' in store.", sAppId.c_str());
	pjniEnv->CallStaticVoidMethod(m_javaClass, m_OpenAppPageMethod, appId);

	pjniEnv->DeleteLocalRef(appId);
}

} // namespace
