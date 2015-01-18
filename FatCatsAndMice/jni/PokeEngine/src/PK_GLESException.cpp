
#include "PK_GLESException.h"

namespace PK {
    
PK_GLESException::PK_GLESException(const char * pszSourceFile, int iLineNumber)
    : PK_Exception("OpenGL ES error.", pszSourceFile, iLineNumber)
    {
    }
    
    
} // namespace