#include "PK_GameException.h"

namespace PK {

//
PK_GameException::PK_GameException(const char * pszFormat, const char * pszSourceFile, int iLineNumber, ...)
{
    va_list args;
	va_start( args, iLineNumber );
    PK_String msg;
    msg.FormatVaArgs(pszFormat, args);
    va_end( args ); 
	Init(msg, pszSourceFile, iLineNumber);
}

//
PK_GameException::PK_GameException(const PK_String &sMessage, const char * pszSourceFile, int iLineNumber) :
	PK_Exception(sMessage, pszSourceFile, iLineNumber)
{
}

} // namespace