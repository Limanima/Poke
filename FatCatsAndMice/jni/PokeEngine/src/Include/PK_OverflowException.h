#ifndef __PK_OVERFLOWEXCEPTION__
#define __PK_OVERFLOWEXCEPTION__

#include "PK_Exception.h"

namespace PK {

class PK_OverflowException : public PK_Exception
{
public:
    PK_OverflowException(const PK_String &sMessage, const char * pszSourceFile, int iLineNumber);
    PK_OverflowException(const char * pszFormat, const char * pszSourceFile, int iLineNumber, ...);
};

}
#endif
