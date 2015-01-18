#if defined(POKE_ANDROID)
extern "C"
{
  #include <android/log.h>
}
#elif defined (POKE_WINDOWS) || defined(POKE_WINPHONE)
  #define WINDOWS_MEAN_AND_LEAN
  #include <windows.h>
#endif

#include "PK_Log.h"
#include "PK_MemoryBuffer.h"
#include "PK_Globals.h"

namespace PK
{
    
//
void PK_Log::WriteError(const char * szTag, const char * szFormat, ...)
{
	va_list args;
	va_start( args, szFormat );
    WriteVaArgs(szTag, szFormat, args, LogLevel_Error);
	va_end(args);
}
    
//
void PK_Log::WriteError(const char * szTag, const PK_String &sMessage)
{
    Write(szTag, sMessage.c_str(), LogLevel_Error);
}
    
//
void PK_Log::WriteWarning(const char * szTag, const char * szFormat, ...)
{
	va_list args;
	va_start( args, szFormat );
    WriteVaArgs(szTag, szFormat, args, LogLevel_Warning);
	va_end(args);
}
    
//
void PK_Log::WriteWarning(const char * szTag, const PK_String &sMessage)
{
    Write(szTag, sMessage.c_str(), LogLevel_Warning);
}  

//
void PK_Log::WriteInfo(const char * szTag, const char * szFormat, ...)
{
	va_list args;
	va_start( args, szFormat );
    WriteVaArgs(szTag, szFormat, args, LogLevel_Information);
	va_end(args);
}
    
//
void PK_Log::WriteInfo(const char * szTag, const PK_String &sMessage)
{
    Write(szTag, sMessage.c_str(), LogLevel_Information);
}


//
void PK_Log::WriteBuffer(const char * szTag, PK_MemoryBuffer &buffer)
{
   int iCols = 16 * 4;
   int BuffLen;
   char Buffer [512];
   char *pt, *pt1, *pt2;
   int  cont;

   BuffLen = buffer.GetLength();
   pt2 =(char*) buffer.GetData();

   memset (Buffer, ' ', sizeof (Buffer));
   for (cont = 1, pt = Buffer, pt1 = Buffer+3*iCols + 3; cont <= BuffLen; ++cont, ++pt1, ++pt2)
   {
      pt += sprintf (pt , "%02X ", (int) (unsigned char)(*pt2) );
      *pt = ' ';
      sprintf (pt1, "%c", ((*pt2 > 31 && *pt2 <127)?*pt2:'?'));
      *(pt1+1) = ' ';
      if (!(cont%iCols) || cont == (BuffLen))
      {
         Buffer [3*iCols + 1] = '|';
         Buffer [3*iCols + iCols + 7] = '\0';
         Write(szTag, Buffer, LogLevel_Information);
         memset (Buffer, ' ', sizeof (Buffer));
         pt1 = Buffer + 3*iCols + 2;
         pt = Buffer;
      }
   }
}

//
void PK_Log::Write(const char * szTag, const PK_String &sMessage, PK_eLogLevel level)
{
  Write(szTag, sMessage.c_str(), level);
}

//
void PK_Log::Write(const char * szTag, const char *szMessage, PK_eLogLevel level)
{
#if defined POKE_ANDROID
	switch(level)
	{
		case LogLevel_Information:
			__android_log_write(ANDROID_LOG_INFO, szTag, szMessage);
			break;
		case LogLevel_Warning:
			__android_log_write(ANDROID_LOG_WARN, szTag, szMessage);
			break;
		case LogLevel_Error:
			__android_log_write(ANDROID_LOG_ERROR, szTag, szMessage);
			break;
		default:
			__android_log_write(ANDROID_LOG_DEBUG, szTag, szMessage);
			break;
	}
#elif defined POKE_IOS
	printf("%s\n", szMessage);
#elif defined(POKE_WINDOWS) || defined(POKE_WINPHONE)
	OutputDebugString(szMessage);
	OutputDebugString("\n");
#endif

#ifdef POKE_DEBUG
    if (PK_Profiler::m_RemoteDebugger.IsRunning())
    {
        PK_Profiler::m_RemoteDebugger.AddLogMessage(szTag, level,(char*)szMessage);
    }
#endif
}
    
//
void PK_Log::WriteVaArgs(const char * szTag, const char *szFormat, va_list args, PK_eLogLevel level)
{
    PK_String msg;
    msg.FormatVaArgs(szFormat, args);
    Write(szTag, msg, level);
}
    
} // namespace
