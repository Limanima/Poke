#include "PK_FileNotFoundException.h"

namespace PK {

PK_FileNotFoundException::PK_FileNotFoundException(const PK_String &sFilename, const char * pszSourceFile, int iLineNumber) :
	PK_Exception("File not found %s", pszSourceFile, iLineNumber, sFilename.c_str())
{
}

} // namespace