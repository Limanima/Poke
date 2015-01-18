#ifndef _PK_SCRIPTING_H_
#define _PK_SCRIPTING_H_

#include "PK_String.h"
    
namespace PK {
     
enum PK_eScriptCommand
{
	ScriptCommand_SetAttribute,
	ScriptCommand_Move,
	ScriptCommand_Rotate,
    ScriptCommand_Pause,
    ScriptCommand_Loop,
    ScriptCommand_Label,
    ScriptCommand_Select,
    ScriptCommand_PlaySound,
	ScriptCommand_UserDefined
};

enum PK_eScriptValueType
{
    ScriptValType_Unk,
    ScriptValType_Bool,
    ScriptValType_Int,
    ScriptValType_Float,
    ScriptValType_Str,
    ScriptValType_Vector2,
    ScriptValType_ScriptVar,
    ScriptValType_Color
};

struct PK_tScriptValueVector
{
    float x, y;
};

struct PK_tScriptValueColor
{
    float r, g, b, a;
};
struct PK_tCommandAttribute
{
    PK_String sName;
    PK_String sValue;
    bool bIsVariable;
};

struct PK_tScriptCommand
{
    PK_eScriptCommand commandCode;
	bool bAsync;
    PK_tScriptCommand() { }
    PK_tScriptCommand (PK_eScriptCommand code) { commandCode = code; }
};


} // namespace


#endif