#ifndef _PK_DXEXCEPTION_H_
#define _PK_DXEXCEPTION_H_

#include "PK_Exception.h"

namespace PK {
    
class PK_DXException : public PK_Exception
{
    public:
        PK_DXException(long hRes, const PK_String &sObject, const PK_String &sMethod, const char * pszSourceFile, int iLineNumber);
};
    
} // namespace

#endif 
