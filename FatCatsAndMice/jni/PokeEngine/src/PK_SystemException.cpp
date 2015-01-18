#include <stdarg.h>
#include "PK_SystemException.h"

namespace PK {


PK_SystemException::PK_SystemException(const char * pszFormat, const char * pszSourceFile, int iLineNumber, ...) 
{
    va_list args;
	va_start( args, iLineNumber );
    PK_String msg;
    msg.FormatVaArgs(pszFormat, args);
    va_end( args ); 
	Init(msg, pszSourceFile, iLineNumber);
}

PK_SystemException::PK_SystemException(const PK_String &sMessage, const char * pszSourceFile, int iLineNumber) :
  PK_Exception(sMessage, pszSourceFile, iLineNumber)
{

}


} // namespace