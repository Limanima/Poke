#ifndef _PK_OUTOFMEMORYEXCEPTION_H_
#define _PK_OUTOFMEMORYEXCEPTION_H_

#include "PK_Exception.h"

namespace PK {

class PK_OutOfMemoryException : public PK_Exception
{
  private:
	int m_iMemSizeRequested;

  public:
	PK_OutOfMemoryException(const std::string &sTypeName, const int iMemSizerequested, const char * pszSourceFile, int iLineNumber);
};

}
#endif
