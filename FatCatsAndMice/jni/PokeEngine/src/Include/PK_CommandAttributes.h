#ifndef _PK_COMMANDATTRIBUTES_H_
#define _PK_COMMANDATTRIBUTES_H_

#include "PK_Scripting.h"
#include "PK_List.h"
#include "PK_Vector2.h"

namespace PK {


//
class PK_CommandAttributes
{
private:
    PK_List<PK_tCommandAttribute> m_Attribs;

public:
    PK_CommandAttributes() {}
    void ClearAttributes() { m_Attribs.Clear(); }
    void AddAttribute(PK_tCommandAttribute &attrib) { m_Attribs.Add(attrib); }
    PK_String GetAttributeValue(const PK_String &sName);
/*
    void GetAttributeValue_Str(const PK_String &sName, PK_tScriptVariable &intoVariable);
	void GetAttributeValue_Str(const PK_String &sName, PK_tScriptVariable &intoVariable, const PK_String & defaultVal);
    void GetAttributeValue_Vector2(const PK_String &sName, PK_tScriptVariable &intoVariable);
	void GetAttributeValue_Vector2(const PK_String &sName, PK_tScriptVariable &intoVariable, const PK_Vector2 & defaultVal);
	void GetAttributeValue_Float(const PK_String &sName, PK_tScriptVariable &intoVariable);
	void GetAttributeValue_Float(const PK_String &sName, PK_tScriptVariable &intoVariable, float defaultVal);
	void GetAttributeValue_Int(const PK_String &sName, PK_tScriptVariable &intoVariable);
	void GetAttributeValue_Int(const PK_String &sName, PK_tScriptVariable &intoVariable, int defaultVal);
	PK_String GetAttributeValue_Str(const PK_String &sName);
	PK_String GetAttributeValue_Str(const PK_String &sName, const PK_String & defaultVal);
    PK_Vector2 GetAttributeValue_Vector2(const PK_String &sName);
	PK_Vector2 GetAttributeValue_Vector2(const PK_String &sName, const PK_Vector2 & defaultVal);
	float GetAttributeValue_Float(const PK_String &sName);
	float GetAttributeValue_Float(const PK_String &sName, float defaultVal);
	int GetAttributeValue_Int(const PK_String &sName);
	int GetAttributeValue_Int(const PK_String &sName, int defaultVal);
*/
	bool ContainsAttribute(const PK_String &sName);
	inline PK_List<PK_tCommandAttribute> & GetAttributes() { return m_Attribs; }
    // Pode devolver null
	PK_tCommandAttribute * GetAttribute(const PK_String &sName, bool mandatory = true);

};

} // namespace

#endif