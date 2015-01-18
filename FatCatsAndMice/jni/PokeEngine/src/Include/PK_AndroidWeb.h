#ifndef _PK_ANDROIDWEB_H_
#define _PK_ANDROIDWEB_H_

#include <jni.h>
#include "PK_String.h"

namespace PK {

//
class PK_AndroidWeb
{
private:
	static jclass  m_javaClass;
	static jmethodID m_withInternetConnectionMethod;
	static jmethodID m_openURLMethod;

public:
    static void Initialize();
    static void UnInitialize();
	static bool TestInternetConnectionThread();
	static void OpenURL(const PK_String &sURL);
};

} // namespace

#endif
