#ifndef _PK_SCRIPTEXCEPTION_
#define _PK_SCRIPTEXCEPTION_

#include "PK_Exception.h"

namespace PK {

class PK_ScriptException : public PK_Exception
{
	public:
		PK_ScriptException(const PK_String &message, const char * pszSourceFile, int iLineNumber) :
		  PK_Exception(message, pszSourceFile, iLineNumber, sArgument.c_str())
		  {
		  }
};

}
#endif
