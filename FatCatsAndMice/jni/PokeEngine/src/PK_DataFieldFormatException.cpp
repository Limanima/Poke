#include "PK_DataFieldFormatException.h"
#include "PK_TypeConverters.h"

namespace PK {

PK_DataFieldFormatException::PK_DataFieldFormatException(PK_eDataFieldType fromFormat, PK_eDataFieldType toFormat, const char * pszSourceFile, int iLineNumber) :
	PK_Exception("Cannot convert DataFileField from type %s to type %s.", pszSourceFile, iLineNumber, 
			PK_TypeConverters::DataFieldTypeToStr(fromFormat).c_str(),
			PK_TypeConverters::DataFieldTypeToStr(toFormat).c_str())
{
}

} // namespace