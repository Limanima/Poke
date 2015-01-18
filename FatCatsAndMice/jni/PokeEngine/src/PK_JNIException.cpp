#include "PK_JNIException.h"

namespace PK {


//
PK_JNIException::PK_JNIException(PK_eJNIException type, const char * pszSourceFile, int iLineNumber) :
  PK_Exception(FormatMessage(type, ""), pszSourceFile, iLineNumber)
{
}

//
PK_JNIException::PK_JNIException(PK_eJNIException type, const PK_String &sMsg, const char * pszSourceFile, int iLineNumber) :
  PK_Exception(FormatMessage(type, sMsg), pszSourceFile, iLineNumber)
{
}


//
PK_String PK_JNIException::FormatMessage(PK_eJNIException type, const PK_String &sMsg)
{
	PK_String sMessage;
	switch(type)
	{
		case JNIException_ClassNotF:
			sMessage = "Java class '" + sMsg + "' not found.";
			break;

		case JNIException_MethodNotF:
			sMessage = "Java method '" + sMsg + "()' not found.";
			break;

		case JNIException_MethodError:
			sMessage = "Java method '" + sMsg + "()' error.";
			break;

		default:
			break;
	}

	return PK_String("JNI Exception: " + sMessage);
}

} // namespace
