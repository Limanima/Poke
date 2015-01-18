#include "PK_AndroidActivity.h"
#include "android/PK_JNIInterface.h"
#include "PK_Exceptions.h"
#include "PK_Consts.h"
#include "PK_Log.h"

namespace PK 
{

jclass  PK_AndroidActivity::m_javaClass = NULL;
jobject PK_AndroidActivity::m_javaObj = NULL;
jmethodID PK_AndroidActivity::m_getPackageName = NULL;
jmethodID PK_AndroidActivity::m_minimize = NULL; 
PK_String PK_AndroidActivity::m_sPackageName;

//static
// Tem que ser chamado da thread principal, isot porque o FindClass so funciona assim
void PK_AndroidActivity::Initialize()
{
	if(m_javaClass != NULL)
	{
		throw PK_SystemException("PK_AndroidActivity() already initialized.", __FILE__, __LINE__);
	}

	JNIEnv * pjniEnv = GetJNIENV();
	jclass cls = pjniEnv->FindClass("limanima/FatCatsAndMice/app/FatCatsAndMiceActivity");
	if (cls == NULL)
	{
		throw PK_JNIException(JNIException_ClassNotF, "limanima/FatCatsAndMice/app/FatCatsAndMiceActivity", __FILE__, __LINE__);
	}
	m_javaClass = static_cast<jclass>(pjniEnv->NewGlobalRef(cls));

	m_getPackageName = pjniEnv->GetMethodID(m_javaClass, "GetPackageName", "()Ljava/lang/String;");
	if (m_getPackageName == NULL)
	{
		throw PK_JNIException(JNIException_MethodNotF, "GetPackageName", __FILE__, __LINE__);
	}
    
    m_minimize = pjniEnv->GetMethodID(m_javaClass, "Minimize", "()V");
    if (m_minimize == NULL)
    {
        throw PK_JNIException(JNIException_MethodNotF, "Minimize", __FILE__, __LINE__);
    }

	jmethodID getInstanceMethod = pjniEnv->GetStaticMethodID(m_javaClass, "GetInstance", "()Llimanima/FatCatsAndMice/app/FatCatsAndMiceActivity;");
	if (getInstanceMethod == NULL)
	{
		throw PK_JNIException(JNIException_MethodNotF, "GetInstance", __FILE__, __LINE__);
	}

	m_javaObj = pjniEnv->CallStaticObjectMethod(m_javaClass, getInstanceMethod);
	if (m_javaObj == NULL)
	{
		throw PK_JNIException(JNIException_MethodError, "GetInstance", __FILE__, __LINE__);
	}

	m_sPackageName = GetPackageName();
}

//static
void PK_AndroidActivity::UnInitialize()
{

}

//static
PK_String PK_AndroidActivity::GetPackageName()
{
    if (m_javaObj == NULL)
	{
		throw PK_SystemException("PK_AndroidActivity not initialized. Call PK_AndroidActivity::Initialize().", __FILE__, __LINE__);
	}
	JNIEnv *pjniEnv = GetJNIENV();

	PK_Log::WriteInfo(PK_LOG_TAG, "Invoke Activity->GetPackageName()");
	jstring result = (jstring)pjniEnv->CallObjectMethod(m_javaObj, m_getPackageName);
	const char *nativeString = pjniEnv->GetStringUTFChars(result, 0);

	PK_String packageName = nativeString;
	pjniEnv->ReleaseStringUTFChars(result, nativeString);

	PK_Log::WriteInfo(PK_LOG_TAG, "Package name is '%s'.", packageName.c_str());
	return packageName;
}

//static
void PK_AndroidActivity::Minimize()
{
    if (m_javaObj == NULL)
    {
        throw PK_SystemException("PK_AndroidActivity not initialized. PK_AndroidActivity::Initialize().", __FILE__, __LINE__);
    }
    JNIEnv *pjniEnv = GetJNIENV();

    PK_Log::WriteInfo(PK_LOG_TAG, "Invoke Activity->Minimize()");
    pjniEnv->CallObjectMethod(m_javaObj, m_minimize);
}

} // namespace
