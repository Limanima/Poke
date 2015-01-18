#ifndef _PK_ANDROIDMESSAGEBOX_H_
#define _PK_ANDROIDMESSAGEBOX_H_

#include <jni.h>
#include "PK_Types.h"
#include "PK_String.h"

namespace PK {

//
class PK_AndroidMessageBox
{
private:
	static jclass  m_javaClass;
	static jmethodID m_showMethod;


public:
    static void Initialize();
    static void UnInitialize();
	static void Show(const PK_String sCaption, const PK_String sMessage, const PK_String sButton1Text, const PK_String sButton2Text, const PK_String sButton3Text);
};

} // namespace

#endif
