#ifndef _PK_GLESEXCEPTION_H_
#define _PK_GLESEXCEPTION_H_


#include "PK_Exception.h"

namespace PK {
    
    class PK_GLESException : public PK_Exception
    {

    public:
        PK_GLESException(const char * pszSourceFile, int iLineNumber);
    };
    
} // namespace

#endif 
