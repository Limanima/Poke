#ifndef _PK_DATAFIELDFORMATEXCEPTION_
#define _PK_DATAFIELDFORMATEXCEPTION_

#include "PK_Exception.h"
#include "PK_Types.h"

namespace PK {

class PK_DataFieldFormatException : public PK_Exception
{
	public:
		PK_DataFieldFormatException(PK_eDataFieldType fromFormat, PK_eDataFieldType toFormat, const char * pszSourceFile, int iLineNumber);
};

}
#endif
