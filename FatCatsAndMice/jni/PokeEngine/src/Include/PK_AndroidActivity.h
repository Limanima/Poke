#ifndef _PK_ANDROIDACTIVITY_H_
#define _PK_ANDROIDACTIVITY_H_

#include <jni.h>
#include "PK_String.h"

namespace PK {
    
// Classe base para um asset: textura, sprite, font, etc
class PK_AndroidActivity
{
private:
	static jobject m_javaObj;
	static jclass  m_javaClass;
	static jmethodID m_getPackageName;
	static PK_String m_sPackageName;


public:
    static void Initialize();
    static void UnInitialize();
	static PK_String GetPackageName();
    static void Minimize();

	static inline PK_String GetPackageName() { return m_sPackageName; }
};

} // namespace

#endif
