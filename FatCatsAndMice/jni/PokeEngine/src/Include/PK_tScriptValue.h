#ifndef _PK_SCRIPTVALUE_H_
#define _PK_SCRIPTVALUE_H_

#include "PK_Scripting.h"
#include "PK_Color.h"

namespace PK {


class PK_Script;
class PK_tScriptValue
{
    union
    {
        int         i;
        float       f;
        bool        b;
        PK_tScriptValueVector  v2;
		char        *str;
        PK_tScriptValueColor   color;
    } val;

private:
    bool bIsNull;
    PK_String sValue;
    PK_eScriptValueType valType;

public:
	PK_tScriptValue()
	{
		SetToNull();
	}
    PK_tScriptValue(int iVal)
	{
		SetValue(iVal);
	}
    bool GetValue_Bool(PK_Script &context);
    int GetValue_Int(PK_Script &context);
    PK_String GetValue_Str(PK_Script &context);
    PK_Vector2 GetValue_Vector2(PK_Script &context);
    float GetValue_Float(PK_Script &context); 
    PK_Color GetValue_Color(PK_Script &context);
    bool IsNull(PK_Script &context);
    inline bool IsNull() { return bIsNull; }
    inline void SetToVariable(const PK_String &sName)
    {
        bIsNull = false;
		valType = ScriptValType_ScriptVar;
        sValue = sName;
    }
    
	inline void SetToNull() 
	{ 
		bIsNull = true;
		valType = ScriptValType_Unk;
	}
    void SetValue(bool bVal)
	{
		valType = ScriptValType_Bool;
		val.b = bVal;
		bIsNull = false;
	}
	void SetValue(int iVal)
	{
		valType = ScriptValType_Int;
		val.i = iVal;
		bIsNull = false;
	}
	void SetValue(float fVal)
	{
		valType = ScriptValType_Float;
		val.f = fVal;
		bIsNull = false;
	}
	void SetValue(const PK_String &sVal)
	{
		valType = ScriptValType_Str;
		sValue = sVal;
		val.str = (char*)sVal.c_str();
		bIsNull = false;
	}
	void SetValue(const PK_Vector2 &vValue)
	{
		valType = ScriptValType_Vector2;
		val.v2.x = vValue.x;
		val.v2.y = vValue.y;
		bIsNull = false;
	}
    void SetValue(PK_Color bVal)
	{
		valType = ScriptValType_Color;
        val.color.r = bVal.r;
        val.color.g = bVal.g;
        val.color.b = bVal.b;
        val.color.a = bVal.a;
		bIsNull = false;
	}
    void SetValue_Bool(PK_tCommandAttribute * pAttrib);
	void SetValue_Int(PK_tCommandAttribute * pAttrib);
	void SetValue_Str(PK_tCommandAttribute * pAttrib);
	void SetValue_Float(PK_tCommandAttribute * pAttrib);
	void SetValue_Vector2(PK_tCommandAttribute * pAttrib);
	void SetValue_Color(PK_tCommandAttribute * pAttrib);
};

} // namespace

#endif