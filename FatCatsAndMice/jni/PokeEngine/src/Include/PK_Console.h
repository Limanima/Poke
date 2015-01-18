#ifndef __PK_CONSOLE_H__
#define __PK_CONSOLE_H__

#include "PK_String.h"

namespace PK {

class PK_Console
{
public:
	static void Write(const char * szFormat, ...);
	static void Write(const PK_String &sMessage);
	static void WriteLine(const char * szFormat, ...);
	static void WriteLine(const PK_String &sMessage);
  
private:
    static void InternalWrite(const char *msg);
    static void WriteVaArgs(const char *szFormat, va_list args);
};

} // Namespace
#endif
