#include "PK_Script.h"
#include "PK_tScriptValue.h"
#include "PK_Scripting.h"
#include "PK_tScriptVariable.h" 
#include "PK_TypeConverters.h"

namespace PK {
//
void PK_tScriptValue::SetValue_Bool(PK_tCommandAttribute * pAttrib)
{
    if (pAttrib == NULL)
    {
        SetToNull();
    }
    else
    {
        if (pAttrib->bIsVariable)
        {
            SetToVariable(pAttrib->sName);
        }
        else
        {
    	    SetValue(PK_TypeConverters::StrToBool(pAttrib->sValue));
        }
    }
}

//
void PK_tScriptValue::SetValue_Int(PK_tCommandAttribute * pAttrib)
{
    if (pAttrib == NULL)
    {
        SetToNull();
    }
    else
    {
        if (pAttrib->bIsVariable)
        {
            SetToVariable(pAttrib->sValue);
        }
        else
        {
    	    SetValue(PK_TypeConverters::StrToInt(pAttrib->sValue));
        }
    }
}
//
void PK_tScriptValue::SetValue_Str(PK_tCommandAttribute * pAttrib)
{
    if (pAttrib == NULL)
    {
        SetToNull();
    }
    else
    {
        if (pAttrib->bIsVariable)
        {
            SetToVariable(pAttrib->sName);
        }
        else
        {
    	    SetValue(pAttrib->sValue);
        }
    }
}

//
void PK_tScriptValue::SetValue_Float(PK_tCommandAttribute * pAttrib)
{
    if (pAttrib == NULL)
    {
        SetToNull();
    }
    else
    {
        if (pAttrib->bIsVariable)
        {
            SetToVariable(pAttrib->sValue);
        }
        else
        {
    	    SetValue(PK_TypeConverters::StrToFloat(pAttrib->sValue));
        }
    }
}

//
void PK_tScriptValue::SetValue_Vector2(PK_tCommandAttribute * pAttrib)
{
    if (pAttrib == NULL)
    {
        SetToNull();
    }
    else
    {
        if (pAttrib->bIsVariable)
        {
            SetToVariable(pAttrib->sValue);
        }
        else
        {
    	    SetValue(PK_TypeConverters::StrToVector2(pAttrib->sValue));
        }
    }
}

//
void PK_tScriptValue::SetValue_Color(PK_tCommandAttribute * pAttrib)
{
    if (pAttrib == NULL)
    {
        SetToNull();
    }
    else
    {
        if (pAttrib->bIsVariable)
        {
            SetToVariable(pAttrib->sValue);
        }
        else
        {
    	    SetValue(PK_TypeConverters::StrToColor(pAttrib->sValue));
        }
    }
}
//
bool PK_tScriptValue::IsNull(PK_Script &context)
{ 
    if (valType == ScriptValType_ScriptVar)
    {
        return context.GetVariable(sValue).value.IsNull();
    }
    return bIsNull; 
}

//
bool PK_tScriptValue::GetValue_Bool(PK_Script &context)
{
    if (valType == ScriptValType_ScriptVar)
    {
        return context.GetVariable(sValue).value.GetValue_Bool();
    }
    return val.b;
}

//
int PK_tScriptValue::GetValue_Int(PK_Script &context)
{
    if (valType == ScriptValType_ScriptVar)
    {
        return context.GetVariable(sValue).value.GetValue_Int();
    }
    return val.i;
}

//
float PK_tScriptValue::GetValue_Float(PK_Script &context)
{
    if (valType == ScriptValType_ScriptVar)
    {
        return context.GetVariable(sValue).value.GetValue_Float();
    }
    return val.f;
}


//
PK_String PK_tScriptValue::GetValue_Str(PK_Script &context)
{
    if (valType == ScriptValType_ScriptVar)
    {
        return context.GetVariable(sValue).value.GetValue_Str();
    }
    return sValue;
}

//
PK_Vector2 PK_tScriptValue::GetValue_Vector2(PK_Script &context)
{
    if (valType == ScriptValType_ScriptVar)
    {
        return context.GetVariable(sValue).value.GetValue_Vector2();
    }
    return PK_Vector2(val.v2.x, val.v2.y);
}

//
PK_Color PK_tScriptValue::GetValue_Color(PK_Script &context)
{
    if (valType == ScriptValType_ScriptVar)
    {
        return context.GetVariable(sValue).value.GetValue_Color();
    }
    return PK_Color(val.color.r, val.color.g, val.color.b, val.color.a);
}

} // namespace