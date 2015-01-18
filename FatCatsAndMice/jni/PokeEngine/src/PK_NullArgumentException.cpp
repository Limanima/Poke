#include "PK_NullArgumentException.h"

namespace PK {

PK_NullArgumentException::PK_NullArgumentException(const PK_String &sArgument, const char * pszSourceFile, int iLineNumber) :
	PK_Exception("Argument cannot be null '%s'.", pszSourceFile, iLineNumber, sArgument.c_str())
{
}

} // namespace