#include "PK_AndroidAdBanner.h"
#include "PK_Log.h"
#include "android/PK_JNIInterface.h"
#include "PK_Exceptions.h"
#include "PK_Consts.h"

namespace PK {

jclass  PK_AndroidAdBanner::m_adBannerClass = NULL;
jmethodID PK_AndroidAdBanner::m_showMethod = NULL;
jmethodID PK_AndroidAdBanner::m_hideMethod = NULL;
jmethodID PK_AndroidAdBanner::m_setAdIdMethod = NULL;
jmethodID PK_AndroidAdBanner::m_createInstanceMethod = NULL;

//
PK_AndroidAdBanner::PK_AndroidAdBanner(const PK_String &sName, const PK_String &sAdId, PK_AdDock dockStyle) :
    PK_AdBanner(sName, sAdId, dockStyle)
{
    SetTypeName("PK_AndroidAdBanner");
    m_javaAdBanner = NULL;
    CreateJavaObject();
}

//
PK_AndroidAdBanner::~PK_AndroidAdBanner()
{
	if (m_javaAdBanner != NULL)
	{
		JNIEnv *pjniEnv = GetJNIENV();
		pjniEnv->DeleteGlobalRef(m_javaAdBanner);
	}
}

//
void PK_AndroidAdBanner::Show()
{
	PK_Log::WriteInfo(PK_LOG_TAG, "Going to show ad named %s.", GetName().c_str());
	JNIEnv *pjniEnv = GetJNIENV();
	SetAdIdOnJava(GetAdId(), pjniEnv);
	pjniEnv->CallVoidMethod(m_javaAdBanner, m_showMethod);
}
  
//
void PK_AndroidAdBanner::Hide()
{
	JNIEnv *pjniEnv = GetJNIENV();
	pjniEnv->CallVoidMethod(m_javaAdBanner, m_hideMethod);
}


//
void PK_AndroidAdBanner::SetAdIdOnJava(const PK_String &sAdId, JNIEnv *pjniEnv)
{
	jstring adId = pjniEnv->NewStringUTF(sAdId.c_str());
	pjniEnv->CallVoidMethod(m_javaAdBanner, m_setAdIdMethod, adId);
	pjniEnv->DeleteLocalRef(adId);
}

//
void PK_AndroidAdBanner::CreateJavaObject()
{
	if (m_adBannerClass == NULL)
	{
		throw PK_SystemException("PK_AndroidAdBanner not initialized. Call PK_AndroidAdBanner::Initialize().", __FILE__, __LINE__);
	}

	JNIEnv *pjniEnv = GetJNIENV();
    jobject obj = pjniEnv->CallStaticObjectMethod(m_adBannerClass, m_createInstanceMethod, (long long)this);
	if (obj == NULL)
	{
		throw PK_JNIException(JNIException_MethodError, "CreateInstance", __FILE__, __LINE__);
	}
	m_javaAdBanner = static_cast<jobject>(pjniEnv->NewGlobalRef(obj));

}

// static
void PK_AndroidAdBanner::Initialize()
{
	JNIEnv *pjniEnv = GetJNIENV();
	jclass cls = pjniEnv->FindClass("limanima/FatCatsAndMice/app/PKaAdBanner");
    if (cls == NULL)
    {
		throw PK_JNIException(JNIException_ClassNotF, "limanima/FatCatsAndMice/app/PKaAdBanner", __FILE__, __LINE__);
    }
    m_adBannerClass = static_cast<jclass>(pjniEnv->NewGlobalRef(cls));

    m_createInstanceMethod = pjniEnv->GetStaticMethodID(m_adBannerClass, "CreateInstance", "(J)Llimanima/FatCatsAndMice/app/PKaAdBanner;");
    if (m_createInstanceMethod == NULL)
    {
		throw PK_JNIException(JNIException_MethodNotF, "CreateInstance", __FILE__, __LINE__);
    }

    m_showMethod = pjniEnv->GetMethodID(m_adBannerClass, "Show", "()V");
    if (m_showMethod == NULL)
    {
		throw PK_JNIException(JNIException_MethodNotF, "Show", __FILE__, __LINE__);
    }

    m_hideMethod = pjniEnv->GetMethodID(m_adBannerClass, "Hide", "()V");
    if (m_hideMethod == NULL)
    {
		throw PK_JNIException(JNIException_MethodNotF, "Hide",__FILE__, __LINE__);
    }

    m_setAdIdMethod = pjniEnv->GetMethodID(m_adBannerClass, "SetAdId", "(Ljava/lang/String;)V");
    if (m_setAdIdMethod == NULL)
    {
		throw PK_JNIException(JNIException_MethodNotF, "SetAdId", __FILE__, __LINE__);
    }
}

// static
void PK_AndroidAdBanner::UnInitialize()
{
	JNIEnv *pjniEnv = GetJNIENV();
	if (m_adBannerClass != NULL)
	{
		pjniEnv->DeleteGlobalRef(m_adBannerClass);
		m_adBannerClass = NULL;
	}
}

} // namespace
