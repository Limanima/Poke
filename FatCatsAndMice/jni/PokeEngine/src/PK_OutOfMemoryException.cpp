#include "PK_OutOfMemoryException.h"

namespace PK {

PK_OutOfMemoryException::PK_OutOfMemoryException(const std::string & sTypeName,const int iMemSizerequested, const char * pszSourceFile, int iLineNumber)
    : PK_Exception("Process run out of memory. Memory size requested %d bytes, type name %s.", pszSourceFile, iLineNumber, iMemSizerequested, sTypeName.c_str())
{
	m_iMemSizeRequested = iMemSizerequested;
}


} // namespace