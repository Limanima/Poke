#ifndef __PK_LOG_H__
#define __PK_LOG_H__

#include "PK_Consts.h"
#include "PK_Object.h"
#include "PK_String.h"

namespace PK {
class PK_MemoryBuffer;
    
enum PK_eLogLevel
{
    LogLevel_Information,
    LogLevel_Warning,
    LogLevel_Error
};
    
class PK_Log : public PK_Object
{
public:
	static void WriteError(const char * szTag, const char * szFormat, ...);
	static void WriteError(const char * szTag, const PK_String &sMessage);
    static void WriteWarning(const char * szTag, const char * szFormat, ...);
	static void WriteWarning(const char * szTag, const PK_String &sMessage);
	static void WriteInfo(const char * szTag, const char * szFormat, ...);
	static void WriteInfo(const char * szTag, const PK_String &sMessage);
	static void WriteBuffer(const char * szTag, PK_MemoryBuffer &buffer);
  
private:
	static void Write(const char * szTag, const PK_String &sMessage, PK_eLogLevel level);
	static void Write(const char * szTag, const char *szMessage, PK_eLogLevel level);
    static void WriteVaArgs(const char * szTag, const char *szFormat, va_list args, PK_eLogLevel level);
};

} // Namespace
#endif
