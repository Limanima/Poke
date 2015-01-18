#ifndef _PK_GAMEEXCEPTION_
#define _PK_GAMEEXCEPTION_

#include "PK_Exception.h"

namespace PK {

class PK_GameException : PK_Exception
{
public:
    PK_GameException() { } 
	PK_GameException(const char * pszFormat, const char * pszSourceFile, int iLineNumber, ...);
    PK_GameException(const PK_String &sMessage, const char * pszSourceFile, int iLineNumber);
};

}
#endif
