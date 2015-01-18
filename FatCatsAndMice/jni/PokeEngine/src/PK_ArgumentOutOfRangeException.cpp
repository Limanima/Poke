#include "PK_ArgumentOutOfRangeException.h"

namespace PK {

PK_ArgumentOutOfRangeException::PK_ArgumentOutOfRangeException(const PK_String &sArgument, const char * pszSourceFile, int iLineNumber) :
	PK_Exception("Argument '%s' is out of range.", pszSourceFile, iLineNumber, sArgument.c_str())
{
}

PK_ArgumentOutOfRangeException::PK_ArgumentOutOfRangeException(const PK_String &sArgument, const PK_String &sMessage, const char * pszSourceFile, int iLineNumber) :
	PK_Exception("Argument '%s' is out of range. %s.", pszSourceFile, iLineNumber, sArgument.c_str(), sArgument.c_str())
{
}

} // namespace