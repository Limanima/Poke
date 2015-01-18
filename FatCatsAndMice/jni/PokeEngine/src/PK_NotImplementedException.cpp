#include "PK_NotImplementedException.h"

namespace PK {

PK_NotImplementedException::PK_NotImplementedException(const PK_String &sMethodName, const char * pszSourceFile, int iLineNumber) :
	PK_Exception("Method '%s' is not implemented.", pszSourceFile, iLineNumber, sMethodName.c_str())
{
}

} // namespace