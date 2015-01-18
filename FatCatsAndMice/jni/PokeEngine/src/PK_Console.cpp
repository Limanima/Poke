#include "PK_Console.h"

namespace PK
{
    
//
void PK_Console::Write(const char * szFormat, ...)
{
	va_list args;
	va_start( args, szFormat );
    WriteVaArgs(szFormat, args);
	va_end(args);
}
    
//
void PK_Console::Write(const PK_String &sMessage)
{
    InternalWrite(sMessage.c_str());
}
    
//
void PK_Console::WriteLine(const char * szFormat, ...)
{
	va_list args;
	va_start( args, szFormat );
    WriteVaArgs(szFormat, args);
	va_end(args);
    printf("\n");
}
    
//
void PK_Console::WriteLine(const PK_String &sMessage)
{
    InternalWrite(sMessage.c_str());
    printf("\n");
}

//
void PK_Console::InternalWrite(const char *msg)
{
    printf("%s", msg);
}
          
//
void PK_Console::WriteVaArgs(const char *szFormat, va_list args)
{
    PK_String msg;
    msg.FormatVaArgs(szFormat, args);
    InternalWrite(msg.c_str());
}
    
} // namespace
