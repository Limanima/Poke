#ifndef __PK_PK_ARGUMENTOUTOFRANGEEXCEPTION__
#define __PK_PK_ARGUMENTOUTOFRANGEEXCEPTION__

#include "PK_Exception.h"

namespace PK {

class PK_ArgumentOutOfRangeException : public PK_Exception
{
	public:
		PK_ArgumentOutOfRangeException(const PK_String &sArgument, const char * pszSourceFile, int iLineNumber);
        PK_ArgumentOutOfRangeException(const PK_String &sArgument, const PK_String &sMessage, const char * pszSourceFile, int iLineNumber);
};

}
#endif
