#ifndef _PK_JNIEXCEPTION_H_
#define _PK_JNIEXCEPTION_H_

#include "PK_Exception.h"

namespace PK {

enum PK_eJNIException
{
	JNIException_ClassNotF,
	JNIException_MethodNotF,
	JNIException_MethodError,
	JNIException_Generic
};

class PK_JNIException : public PK_Exception
{

  public:
	PK_JNIException(PK_eJNIException type, const char * pszSourceFile, int iLineNumber);
	PK_JNIException(PK_eJNIException type, const PK_String &sMsg, const char * pszSourceFile, int iLineNumber);

	static PK_String FormatMessage(PK_eJNIException type, const PK_String &sMsg);
};

}
#endif

