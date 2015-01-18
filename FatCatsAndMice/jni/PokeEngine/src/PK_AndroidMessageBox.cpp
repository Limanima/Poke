#include "PK_AndroidMessageBox.h"
#include "android/PK_JNIInterface.h"
#include "PK_Exceptions.h"
#include "PK_Consts.h"
#include "PK_Log.h"

namespace PK 
{

jclass  PK_AndroidMessageBox::m_javaClass = NULL;
jmethodID PK_AndroidMessageBox::m_showMethod = NULL;

//static
// Tem que ser chamado da thread principal, isot porque o FindClass so funciona assim
void PK_AndroidMessageBox::Initialize()
{
	if(m_javaClass != NULL)
	{
		throw PK_SystemException("PK_AndroidMessageBox() already initialized.", __FILE__, __LINE__);
	}

	JNIEnv * pjniEnv = GetJNIENV();
	jclass cls = pjniEnv->FindClass("limanima/FatCatsAndMice/app/PKaMessageBox");
	if (cls == NULL)
	{
		throw PK_JNIException(JNIException_ClassNotF, "limanima/FatCatsAndMice/app/PKaMessageBox", __FILE__, __LINE__);
	}
	m_javaClass = static_cast<jclass>(pjniEnv->NewGlobalRef(cls));

	m_showMethod = pjniEnv->GetStaticMethodID(m_javaClass, "Show", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (m_showMethod == NULL)
	{
		throw PK_JNIException(JNIException_MethodNotF, "Show", __FILE__, __LINE__);
	}
}

//static
void PK_AndroidMessageBox::UnInitialize()
{

}

// static
void PK_AndroidMessageBox::Show(const PK_String sCaption, const PK_String sMessage,
		const PK_String sButton1Text, const PK_String sButton2Text, const PK_String sButton3Text)
{
	if (m_showMethod == NULL)
	{
		throw PK_SystemException("Class PK_eMsgBoxResult not intialized.", __FILE__, __LINE__);
	}

	JNIEnv * pjniEnv = GetJNIENV();

	jstring caption = pjniEnv->NewStringUTF(sCaption.c_str());
	jstring message = pjniEnv->NewStringUTF(sMessage.c_str());
	jstring button1 = pjniEnv->NewStringUTF(sButton1Text.c_str());
	jstring button2 = NULL;
	if (sButton2Text != "")
	{
		button2 = pjniEnv->NewStringUTF(sButton2Text.c_str());
	}

	jstring button3 = NULL;
	if (sButton3Text != "")
	{
		button3 = pjniEnv->NewStringUTF(sButton3Text.c_str());
	}

	pjniEnv->CallStaticVoidMethod(m_javaClass, m_showMethod, caption, message, button1, button2, button3);

	pjniEnv->DeleteLocalRef(caption);
	pjniEnv->DeleteLocalRef(message);
	pjniEnv->DeleteLocalRef(button1);
	if (button2 != NULL)
	{
		pjniEnv->DeleteLocalRef(button2);
	}
	if (button3 != NULL)
	{
		pjniEnv->DeleteLocalRef(button3);
	}
}

} // namespace
