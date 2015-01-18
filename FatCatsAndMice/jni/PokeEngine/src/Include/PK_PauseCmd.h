#ifndef _PK_PAUSECMD_H_
#define _PK_PAUSECMD_H_

#include "PK_ScriptCommand.h"

namespace PK {

struct PK_tPauseCmd : PK_tScriptCommand
{
   PK_tScriptValue duration; // em msecs
   PK_tPauseCmd() : PK_tScriptCommand(ScriptCommand_Pause) { }
};

class PK_CommandAttributes;

// Syntaxe do comando:
//  pause duration:mSecs;
class PK_PauseCmd : public PK_ScriptCommand
{
private:
	PK_tPauseCmd m_Vars;
	unsigned int m_uiEllapsed;
	
public:
	PK_PauseCmd(PK_Script &owner, PK_tPauseCmd &vars);
	void Prepare();
	bool Execute(const PK_GameTimer &time);
    static PK_tPauseCmd * ParseAttributes(PK_CommandAttributes &attributes);
};

} // namespace

#endif