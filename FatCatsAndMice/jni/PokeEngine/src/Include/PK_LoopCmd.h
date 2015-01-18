#ifndef _PK_LOOPCMD_H_
#define _PK_LOOPCMD_H_

#include "PK_ScriptCommand.h"
#include "PK_Scripting.h"

namespace PK {

struct PK_tLoopCmd : PK_tScriptCommand
{
    PK_tScriptValue labelName;
    PK_tLoopCmd() : PK_tScriptCommand(ScriptCommand_Loop) { }
};

class PK_CommandAttributes;

// Syntaxe do comando:
//  move from: 10,10; to: 20,20; speed: 5;
class PK_LoopCmd : public PK_ScriptCommand
{
private:
	PK_tLoopCmd m_Vars;

public:
	PK_LoopCmd(PK_Script &owner, PK_tLoopCmd &vars);
  	bool Execute(const PK_GameTimer &time);
    static PK_tLoopCmd * ParseAttributes(PK_CommandAttributes &attributes);
};

} // namespace

#endif