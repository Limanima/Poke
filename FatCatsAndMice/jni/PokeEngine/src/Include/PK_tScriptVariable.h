#ifndef _PK_SCRIPTVARIABLE_H_
#define _PK_SCRIPTVARIABLE_H_


namespace PK {

struct PK_tScriptValue1
{
private:
    union
    {
        int         i;
        float       f;
        bool       b;
        PK_tScriptValueVector  v2;
		char        *str;
        PK_tScriptValueColor   color;
    } val;

    bool bIsNull;
    PK_String sValue;
    PK_eScriptValueType valType;
public:
    PK_tScriptValue1()
    {
        SetToNull();
    }
    PK_tScriptValue1(int iValue)
    {
        SetValue(iValue);
    }
    
    PK_tScriptValue1(PK_Vector2 vValue)
    {
        SetValue(vValue);
    }

    inline bool IsNull() { return bIsNull; }
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
    void SetValue(const PK_Color &color)
	{
		valType = ScriptValType_Color;
		val.color.r = color.r;
        val.color.g = color.g;
        val.color.b = color.b;
        val.color.a = color.a;
		bIsNull = false;
	}
    inline bool GetValue_Bool() 
    {
        return val.b;
    }
    inline int GetValue_Int() 
    {
        return val.i;
    }
    inline float GetValue_Float() 
    {
        return val.f;
    }
    inline PK_String & GetValue_Str() 
    {
        return sValue;
    }
    inline PK_Vector2 GetValue_Vector2() 
    {
        return PK_Vector2(val.v2.x, val.v2.y);
    }
    inline PK_Color GetValue_Color() 
    {
        return PK_Color(val.color.r, val.color.g, val.color.b, val.color.a);
    }
};

class PK_tScriptValue;
struct PK_tScriptVariable
{
	PK_tScriptValue1 value;
	PK_String sName;
};

} // namespace

#endif