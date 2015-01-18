#include "PK_CommandAttributes.h"
#include "PK_TypeConverters.h"

#define ASSERT_ATTRIB_EXISTS(pAttrib, attribName) \
if (pAttrib == NULL) \
{ \
	throw PK_SystemException("Scripting error. Attribute '%s' not found.", __FILE__, __LINE__, attribName.c_str()); \
}

namespace PK {

//
PK_String PK_CommandAttributes::GetAttributeValue(const PK_String &sName)
{
	PK_tCommandAttribute * pAttrib = GetAttribute(sName);
    return pAttrib->sValue;
}

	/*
//
void PK_CommandAttributes::GetAttributeValue_Str(const PK_String &sName, PK_tScriptVariable &intoVariable)
{
	intoVariable.SetValue_Str(GetAttributeValue_Str(sName));
}

//
void PK_CommandAttributes::GetAttributeValue_Str(const PK_String &sName, PK_tScriptVariable &intoVariable, const PK_String & defaultVal)
{
	intoVariable.SetValue_Str(GetAttributeValue_Str, defaultVal);
}   
//
void PK_CommandAttributes::GetAttributeValue_Vector2(const PK_String &sName, PK_tScriptVariable &intoVariable)
{
	intoVariable.SetValue_Vector2(GetAttributeValue_Vector2);
}

//
void PK_CommandAttributes::GetAttributeValue_Vector2(const PK_String &sName, PK_tScriptVariable &intoVariable, const PK_Vector2 & defaultVal)
{
	intoVariable.SetValue_Vector2(GetAttributeValue_Vector2, defaultVal);
}

//
void PK_CommandAttributes::GetAttributeValue_Float(const PK_String &sName, PK_tScriptVariable &intoVariable)
{
	intoVariable.SetValue_Float(GetAttributeValue_Float);
}

//
void PK_CommandAttributes::GetAttributeValue_Float(const PK_String &sName, PK_tScriptVariable &intoVariable, float defaultVal)
{
	intoVariable.SetValue_Float(GetAttributeValue_Float, defaultVal);
}

//
void PK_CommandAttributes::GetAttributeValue_Int(const PK_String &sName, PK_tScriptVariable &intoVariable)
{
	intoVariable.SetValue_Int(GetAttributeValue_Float);
}

//
void PK_CommandAttributes::GetAttributeValue_Int(const PK_String &sName, PK_tScriptVariable &intoVariable, int defaultVal)
{
	intoVariable.SetValue_Int(GetAttributeValue_Int, defaultVal);
}

//
PK_String PK_CommandAttributes::GetAttributeValue_Str(const PK_String &sName)
{
	PK_tCommandAttribute *pParam = GetAttribute(sName);
	ASSERT_ATTRIB_EXISTS(pParam, sName)
	return pParam->sValue;
}

//
PK_String PK_CommandAttributes::GetAttributeValue_Str(const PK_String &sName, const PK_String & defaultVal)
{
	PK_tCommandAttribute *pParam = GetAttribute(sName, false);
	if (pParam == NULL)
	{
		return defaultVal;
	}

	return pParam->sValue;
}   
//
PK_Vector2 PK_CommandAttributes::GetAttributeValue_Vector2(const PK_String &sName)
{
	PK_tCommandAttribute *pParam = GetAttribute(sName);
	ASSERT_ATTRIB_EXISTS(pParam, sName)
	return pParam->GetValue_Vector2();
}

//
PK_Vector2 PK_CommandAttributes::GetAttributeValue_Vector2(const PK_String &sName, const PK_Vector2 & defaultVal)
{
	PK_tCommandAttribute *pParam = GetAttribute(sName, false);
	if (pParam == NULL)
	{
		return defaultVal;
	}

	return pParam->GetValue_Vector2();
}

//
float PK_CommandAttributes::GetAttributeValue_Float(const PK_String &sName)
{
	PK_tCommandAttribute *pParam = GetAttribute(sName);
	ASSERT_ATTRIB_EXISTS(pParam, sName)
	return pParam->GetValue_Float();
}

//
float PK_CommandAttributes::GetAttributeValue_Float(const PK_String &sName, float defaultVal)
{
	PK_tCommandAttribute *pParam = GetAttribute(sName);
	if (pParam == NULL)
	{
		return defaultVal;
	}
	return pParam->GetValue_Float();
}

//
int PK_CommandAttributes::GetAttributeValue_Int(const PK_String &sName)
{
	PK_tCommandAttribute *pParam = GetAttribute(sName);
	ASSERT_ATTRIB_EXISTS(pParam, sName)
	return pParam->GetValue_Int();
}

//
int PK_CommandAttributes::GetAttributeValue_Int(const PK_String &sName, int defaultVal)
{
	PK_tCommandAttribute *pParam = GetAttribute(sName);
	if (pParam == NULL)
	{
		return defaultVal;
	}
	return pParam->GetValue_Int();
}
*/
//
bool PK_CommandAttributes::ContainsAttribute(const PK_String &sName)
{
	return (GetAttribute(sName, false) != NULL);
}

//
PK_tCommandAttribute * PK_CommandAttributes::GetAttribute(const PK_String &sName, bool mandatory)
{
	if (sName == "")
	{
		throw PK_SystemException("Command parameter name cannot be empty.", __FILE__, __LINE__);
	}
    
    for(PK_ListIterator(PK_tCommandAttribute) itor = m_Attribs.Begin(); itor != m_Attribs.End(); itor++)
	{
		if ((*itor).sName == sName)
		{
			return &(*itor);
		}
	}

	if (mandatory)
	{
		throw PK_SystemException("Command parameter '%s' is mandatory.", __FILE__, __LINE__, sName.c_str());
	}

	return NULL;
}


} // namespace