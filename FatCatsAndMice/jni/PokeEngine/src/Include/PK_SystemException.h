#ifndef _POKEENGINEEXCEPTION_H_
#define _POKEENGINEEXCEPTION_H_

#include "PK_Exception.h"

namespace PK {

class PK_SystemException : public PK_Exception
{
  private:
	

  public:
    PK_SystemException() { } 
	PK_SystemException(const char * pszFormat, const char * pszSourceFile, int iLineNumber, ...);
	PK_SystemException(const PK_String &sMessage, const char * pszSourceFile, int iLineNumber);
};

}
#endif
