#ifndef _PK_SelectCmd_H_
#define _PK_SelectCmd_H_

#include "PK_ScriptCommand.h"
#include "PK_Scripting.h"

namespace PK {

struct PK_tSelectCmd : PK_tScriptCommand
{
    PK_tScriptValue controlName;
    PK_tSelectCmd() : PK_tScriptCommand(ScriptCommand_Select) { }
};

class PK_CommandAttributes;

// Syntaxe do comando:
//  label name:NOME;
class PK_SelectCmd : public PK_ScriptCommand
{
private:
	PK_tSelectCmd m_Vars;

public:
	PK_SelectCmd(PK_Script &owner, PK_tSelectCmd &vars);
  	bool Execute(const PK_GameTimer &time);
    static PK_tSelectCmd * ParseAttributes(PK_CommandAttributes &attributes);
};

} // namespace

#endif