#ifndef _PK_ANDROIDADBANNER_H_
#define _PK_ANDROIDADBANNER_H_

#include "PK_AdBanner.h"
#include <jni.h>

namespace PK {

//
class PK_AndroidAdBanner : public PK_AdBanner
{
private:
	static jclass  m_adBannerClass;
	static jmethodID m_showMethod;
	static jmethodID m_hideMethod;
	static jmethodID m_setAdIdMethod;
	static jmethodID m_createInstanceMethod;
	jobject m_javaAdBanner;

public:
	PK_AndroidAdBanner(const PK_String &sName, const PK_String &sAdId, PK_AdDock dockStyle);
	~PK_AndroidAdBanner();
    void Show();
    void Hide();

    static void Initialize();
    static void UnInitialize();

private:
    void SetAdIdOnJava(const PK_String &sAdId, JNIEnv *pjniEnv);
    void CreateJavaObject();
};

} // namespace

#endif
