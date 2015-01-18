#include "PK_OverflowException.h"

namespace PK {

//
PK_OverflowException::PK_OverflowException(const PK_String &sMessage, const char * pszSourceFile, int iLineNumber) :
	PK_Exception(sMessage, pszSourceFile, iLineNumber)
{

}

//
PK_OverflowException::PK_OverflowException(const char * pszFormat, const char * pszSourceFile, int iLineNumber, ...)
{
    va_list args;
	va_start( args, iLineNumber );
    PK_String msg;
    msg.FormatVaArgs(pszFormat, args);
    va_end( args ); 
	Init(msg, pszSourceFile, iLineNumber);
}


} // namespace