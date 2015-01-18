#ifndef _PK_INVALIDAPPARGUMENTSEXCEPTION_
#define _PK_INVALIDAPPARGUMENTSEXCEPTION_

#include "PK_Exception.h"

namespace PK {

class PK_InvalidAppArgumentsException : public PK_Exception
{
	public:
		PK_InvalidAppArgumentsException(const PK_String &msg, const char * pszSourceFile, int iLineNumber)
            : PK_Exception(msg, pszSourceFile, iLineNumber) {}
};

}
#endif
