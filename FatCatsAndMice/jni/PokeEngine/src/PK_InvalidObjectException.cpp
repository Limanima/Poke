#include "PK_InvalidObjectException.h"

namespace PK {

PK_InvalidObjectException::PK_InvalidObjectException(const PK_Object &object, const char * pszSourceFile, int iLineNumber) :
    PK_Exception("Invalid object. Cannot use local object instances. Use PK_Object::CreateInstance() to create a global object. Object type='%s', Object name='%s'", 
                     pszSourceFile, iLineNumber, object.GetTypeName().c_str(), object.GetName().c_str())
{
}

} // namespace