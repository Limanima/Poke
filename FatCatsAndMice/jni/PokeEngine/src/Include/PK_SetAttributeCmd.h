#ifndef _PK_SETPOSITIONCMD_H_
#define _PK_SETPOSITIONCMD_H_

#include "PK_ScriptCommand.h"
#include "PK_ScriptAsset.h"
#include "PK_Vector3.h"
#include "PK_Script.h"

namespace PK {


struct PK_tSetAttributeCmd : PK_tScriptCommand
{
    PK_tScriptValue position;
    PK_tScriptValue rotation;
    PK_tScriptValue visibility;
    PK_tScriptValue input;
    PK_tScriptValue color;
    PK_List<PK_tCommandAttribute> m_CustomAttributes;
    PK_tSetAttributeCmd() : PK_tScriptCommand(ScriptCommand_SetAttribute) { }

};

class PK_CommandAttributes;

// Syntaxe do comando:
//  Set [position:x, y, z]; [rotation:angle]
class PK_SetAttributeCmd : public PK_ScriptCommand
{
private:
	PK_tSetAttributeCmd m_attribs;
	
public:
	PK_SetAttributeCmd(PK_Script &owner, PK_tSetAttributeCmd &commandAttribs);
	bool Execute(const PK_GameTimer &time);
    static PK_tSetAttributeCmd * ParseAttributes(PK_CommandAttributes &attributes);
};

} // namespace

#endif