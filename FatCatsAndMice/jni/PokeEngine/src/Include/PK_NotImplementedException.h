#ifndef _PK_NOTIMPLEMENTEDEXCEPTION_
#define _PK_NOTIMPLEMENTEDEXCEPTION_

#include "PK_Exception.h"

namespace PK {

class PK_NotImplementedException : public PK_Exception
{
	public:
		PK_NotImplementedException(const PK_String &sMethodName, const char * pszSourceFile, int iLineNumber);
};

}
#endif
