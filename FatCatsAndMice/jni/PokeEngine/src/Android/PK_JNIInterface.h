#ifndef __PKC_CINTERFACE_H__
#define __PKC_CINTERFACE_H__

#include "PK_String.h"
#include <jni.h>

#ifdef __cplusplus

extern "C"
{
#endif
// PKaAdBanner
JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaAdBanner_AdRequestSuccess(JNIEnv *, jobject);
JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaAdBanner_AdRequestError(JNIEnv *, jobject);
// PKaMessageBox
JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaMessageBox_Button1Clicked(JNIEnv *, jclass);
JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaMessageBox_Button2Clicked(JNIEnv *, jclass);
JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaMessageBox_Button3Clicked(JNIEnv *, jclass);
//PK_aPlayer
JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaPlayer_GamerServicesLogin(JNIEnv *, jclass, jboolean);
JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaPlayer_GamerServicesLogout(JNIEnv *, jclass, jboolean);
//PK_aLog
JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaLog_WriteInfo(JNIEnv *, jclass, jstring);
JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaLog_WriteError(JNIEnv *, jclass, jstring);
JNIEXPORT void JNICALL Java_limanima_FatCatsAndMice_app_PKaLog_WriteWarning(JNIEnv *, jclass, jstring);

#ifdef __cplusplus
}

#endif
namespace PK
{
 JNIEnv * GetJNIENV();
 void PKa_InitializeAndroid();
 void PKa_UnInitializeAndroid();
 void PKa_DettachCurrentThreadFromJVM();
}
#endif
