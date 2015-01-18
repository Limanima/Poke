#ifndef _PK_LABELCMD_H_
#define _PK_LABELCMD_H_

#include "PK_ScriptCommand.h"
#include "PK_Scripting.h"

namespace PK {

struct PK_tLabelCmd : PK_tScriptCommand
{
    PK_tScriptValue labelName;
    PK_tLabelCmd() : PK_tScriptCommand(ScriptCommand_Label) { }
};

class PK_CommandAttributes;

// Syntaxe do comando:
//  label name:NOME;
class PK_LabelCmd : public PK_ScriptCommand
{
private:
	PK_tLabelCmd m_Vars;

public:
	PK_LabelCmd(PK_Script &owner, PK_tLabelCmd &vars);
  	bool Execute(const PK_GameTimer &time);
    PK_String GetLabelName();
    static PK_tLabelCmd * ParseAttributes(PK_CommandAttributes &attributes);
};

} // namespace

#endif