#ifndef _PK_FILENOTFOUNDEXCEPTION_
#define _PK_FILENOTFOUNDEXCEPTION_

#include "PK_String.h"
#include "PK_Exception.h"

namespace PK {

class PK_FileNotFoundException : PK_Exception
{
public:
	PK_FileNotFoundException(const PK_String &szFilename, const char * pszSourceFile, int iLineNumber);
};

}
#endif
