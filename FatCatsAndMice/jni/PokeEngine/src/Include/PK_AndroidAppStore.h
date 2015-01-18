#ifndef _PK_ANDROIDAPPSTORE_H_
#define _PK_ANDROIDAPPSTORE_H_

#include <jni.h>
#include "PK_String.h"

namespace PK {

//
class PK_AndroidAppStore
{
private:
	static jclass  m_javaClass;
	static jmethodID m_OpenAppPageMethod;

public:
	static void OpenAppPage(const PK_String &sAppId);
	static void Initialize();
	static void UnInitialize();
};

} // namespace

#endif
