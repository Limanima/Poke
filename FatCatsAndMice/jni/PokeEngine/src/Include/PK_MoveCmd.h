#ifndef _PK_MOVECMD_H_
#define _PK_MOVECMD_H_

#include "PK_ScriptCommand.h"
#include "PK_Vector3.h"
#include "PK_Scripting.h"

namespace PK {

struct PK_tMoveCmd : PK_tScriptCommand
{
	PK_tScriptValue destination; // "move to" command
    PK_tScriptValue by;          // "move by" command
    PK_tScriptValue speed;
    PK_tScriptValue acceleration;
    PK_tScriptValue deceleration;
 
    PK_tMoveCmd() : PK_tScriptCommand(ScriptCommand_Move) { }
};

class PK_GameTimer;
class PK_CommandAttributes;

// Syntaxe do comando:
//  move from: 10,10; to: 20,20; speed: 5;
class PK_MoveCmd : public PK_ScriptCommand
{
private:
	PK_tMoveCmd m_Vars;
    float       m_fCurrentSpeed;
    bool        m_bBreaking;

public:
	PK_MoveCmd(PK_Script &owner, PK_tMoveCmd &vars);
    void Prepare();
  	bool Execute(const PK_GameTimer &time);
    static PK_tMoveCmd * ParseAttributes(PK_CommandAttributes &attributes);
};

} // namespace

#endif