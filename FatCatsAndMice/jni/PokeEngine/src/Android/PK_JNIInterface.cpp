#include <jni.h>
#include "../include/PK_Log.h"
#include "../include/PK_Exceptions.h"
#include "../include/PK_AndroidAdBanner.h"
#include "../include/PK_Thread.h"
#include "../include/PK_AndroidWeb.h"
#include "../include/PK_AndroidMessageBox.h"
#include "../include/PK_AndroidAppStore.h"
#include "../include/PK_AndroidActivity.h"
#include "../include/PK_MessageBox.h"
#include "../include/PK_Globals.h"
#include "../include/PK_Player.h"

const jint PK_JNI_VERSION = JNI_VERSION_1_6;


JavaVM * gPK_pJavaVM = NULL;
jclass g_webClass = NULL;

//
extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	gPK_pJavaVM = vm;
	PK::PK_Log::WriteInfo(PK_LOG_TAG, "Poke Engine Library loaded.");
	return PK_JNI_VERSION;
}

//
extern "C" JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaAdBanner_AdRequestSuccess(JNIEnv * pEnv, jobject javaObj, jlong cObjAddress)
{
	PK::PK_Log::WriteInfo(PK_LOG_TAG, "Ad requested with success.");
	PK::PK_AndroidAdBanner *pAd =(PK::PK_AndroidAdBanner *)cObjAddress;
	pAd->InvokeOnRequestSuccess();
}

//
extern "C" JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaAdBanner_AdRequestError(JNIEnv * pEnv, jobject javaObj, jlong cObjAddress)
{
	PK::PK_Log::WriteInfo(PK_LOG_TAG, "Ad request error.");
	PK::PK_AndroidAdBanner *pAd =(PK::PK_AndroidAdBanner *)cObjAddress;
	pAd->InvokeOnRequestError();
}

//
extern "C" JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaMessageBox_Button1Clicked__(JNIEnv *, jclass)
{
	PK::PK_Log::WriteInfo(PK_LOG_TAG, "MessageBox button1 pressed.");
	PK::PK_MessageBox::InternalDialogClosed(PK::MsgBoxResult_Button1);
}

//
extern "C" JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaMessageBox_Button2Clicked__(JNIEnv *, jclass)
{
	PK::PK_Log::WriteInfo(PK_LOG_TAG, "MessageBox button2 pressed.");
	PK::PK_MessageBox::InternalDialogClosed(PK::MsgBoxResult_Button2);
}

//
extern "C" JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaMessageBox_Button3Clicked__(JNIEnv *, jclass)
{
	PK::PK_Log::WriteInfo(PK_LOG_TAG, "MessageBox button3 pressed.");
	PK::PK_MessageBox::InternalDialogClosed(PK::MsgBoxResult_Button3);
}

//
extern "C" JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaPlayer_GamerServicesLogin(JNIEnv *, jclass, jboolean success)
{
	PK::PokeEngine.GetPlayer().GamerServicesLogin(success != JNI_FALSE);
}

//
extern "C" JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaPlayer_GamerServicesLogout(JNIEnv *, jclass, jboolean)
{
	PK::PokeEngine.GetPlayer().GamerServicesLogout();
}



//PK_aWeb
void PKaLog_Write(PK::PK_eLogLevel level, JNIEnv * jEnv, jstring msg)
{
   const char *nativeString = jEnv->GetStringUTFChars( msg, 0);
   switch(level)
   {
   	   case PK::LogLevel_Information:
   		   PK::PK_Log::WriteInfo(PK_LOG_TAG, nativeString);
   		   break;
   	   case PK::LogLevel_Error:
   		   PK::PK_Log::WriteError(PK_LOG_TAG, nativeString);
   		   break;
   	   case PK::LogLevel_Warning:
   		   PK::PK_Log::WriteWarning(PK_LOG_TAG, nativeString);
   		   break;
   }
   jEnv->ReleaseStringUTFChars( msg, nativeString);
}

extern "C" JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaLog_WriteInfo(JNIEnv * jEnv, jclass, jstring msg)
{
	PKaLog_Write(PK::LogLevel_Information, jEnv, msg);
}

extern "C" JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaLog_WriteError(JNIEnv * jEnv, jclass, jstring msg)
{
	PKaLog_Write(PK::LogLevel_Error, jEnv, msg);
}

extern "C" JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaLog_WriteWarning(JNIEnv * jEnv, jclass, jstring msg)
{
	PKaLog_Write(PK::LogLevel_Warning, jEnv, msg);
}


namespace PK
{

//
JNIEnv * GetJNIENV()
{
	JNIEnv *pjniEnv;

	PK_Log::WriteInfo(PK_LOG_TAG, "Getting JNI Env for thread with id '%lld'.", PK_Thread::GetCurrentThreadId());
	if (gPK_pJavaVM == NULL)
	{
		throw PK_JNIException(PK::JNIException_Generic, "Cannot get JNIEnv because poke DLL was no loaded.", __FILE__, __LINE__);
	}
	int getEnvStat = gPK_pJavaVM->GetEnv((void **)&pjniEnv, PK_JNI_VERSION);
	if (getEnvStat == JNI_EDETACHED)
	{
		PK_Log::WriteInfo(PK_LOG_TAG, "Attaching JNI Env to thread with id '%lld'.", PK_Thread::GetCurrentThreadId());
		if (gPK_pJavaVM->AttachCurrentThread(&pjniEnv, NULL) != 0)
		{
			throw PK_JNIException(PK::JNIException_Generic, "Could not attach thread.", __FILE__, __LINE__);
		}

	}
	else if (getEnvStat == JNI_EVERSION)
	{
		throw PK_JNIException(PK::JNIException_Generic, "Invalid Java version.", __FILE__, __LINE__);
	}

	if (pjniEnv == NULL)
	{
		throw PK_JNIException(PK::JNIException_Generic, "Could not get JNIEnv.", __FILE__, __LINE__);
	}

	PK_Log::WriteInfo(PK_LOG_TAG, "JNIEnv obtained with success.", PK_Thread::GetCurrentThreadId());

	return pjniEnv;
}

//
void PKa_InitializeAndroid()
{
	PK_AndroidWeb::Initialize();
	PK_AndroidAdBanner::Initialize();
	PK_AndroidMessageBox::Initialize();
	PK_AndroidAppStore::Initialize();
	PK_AndroidActivity::Initialize();
}

//
void PKa_UnInitializeAndroid()
{
	PK_AndroidWeb::UnInitialize();
	PK_AndroidAdBanner::UnInitialize();
	PK_AndroidMessageBox::UnInitialize();
	PK_AndroidAppStore::UnInitialize();
	PK_AndroidActivity::UnInitialize();
}

//
void PKa_DettachCurrentThreadFromJVM()
{
	if (gPK_pJavaVM == NULL)
	{
		throw PK_JNIException(PK::JNIException_Generic, "Cannot dettach thread from JVM because JVM is not initialized.", __FILE__, __LINE__);
	}

	jint iRet = gPK_pJavaVM->DetachCurrentThread();
	if (iRet != JNI_OK)
	{
		throw PK_JNIException(PK::JNIException_Generic, "Error detaching thread from JVM.", __FILE__, __LINE__);
	}
}

} // namespace PK

