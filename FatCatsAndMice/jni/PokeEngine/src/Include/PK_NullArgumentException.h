#ifndef _PK_NULLARGUMENTEXCEPTION_
#define _PK_NULLARGUMENTEXCEPTION_

#include "PK_Exception.h"

namespace PK {

class PK_NullArgumentException : public PK_Exception
{
	public:
		PK_NullArgumentException(const PK_String &sArgument, const char * pszSourceFile, int iLineNumber);
};

}
#endif
