#ifndef _PK_PLAYSOUNDCMD_H_
#define _PK_PLAYSOUNDCMD_H_

#include "PK_ScriptCommand.h"
#include "PK_Scripting.h"

namespace PK {

struct PK_tPlaySoundCmd : PK_tScriptCommand
{
    PK_tScriptValue resName;
    PK_tPlaySoundCmd() : PK_tScriptCommand(ScriptCommand_PlaySound) { }
};

class PK_CommandAttributes;

// Syntaxe do comando:
//  play_sound asset:NOME;
class PK_PlaySoundCmd : public PK_ScriptCommand
{
private:
	PK_tPlaySoundCmd m_Vars;

public:
	PK_PlaySoundCmd(PK_Script &owner, PK_tPlaySoundCmd &vars);
  	bool Execute(const PK_GameTimer &time);
    static PK_tPlaySoundCmd * ParseAttributes(PK_CommandAttributes &attributes);
};

} // namespace

#endif