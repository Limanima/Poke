#include "PK_DXException.h"

namespace PK {

//
PK_DXException::PK_DXException(long hRes, const PK_String &sObject, const PK_String &sMethod, const char * pszSourceFile, int iLineNumber)
    : PK_Exception("Direct3D error.", pszSourceFile, iLineNumber)
{
}
    
} // namespace