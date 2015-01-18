#ifndef _PK_ROTATECMD_H_
#define _PK_ROTATECMD_H_

#include "PK_ScriptCommand.h"
#include "PK_Vector3.h"
#include "PK_Scripting.h"

namespace PK {

// Roda um objecto da rotacao actual para os graus defenidos em "to"
// Syntaxe do comando
//  rotate to: 45; speed: 5; accel: 20; decel: 20; direction : cw | ccw;
//
//  "to" em graus
//  "speed", "accel", "decel" em graus por segundo

struct PK_tRotateCmd : PK_tScriptCommand
{
	PK_tScriptValue destDegrees;
	PK_tScriptValue speed;
	PK_tScriptValue direction;
    PK_tScriptValue acceleration;
    PK_tScriptValue deceleration;

    PK_tRotateCmd() : PK_tScriptCommand(ScriptCommand_Rotate) { }
};

class PK_GameTimer;
class PK_CommandAttributes;


class PK_RotateCmd : public PK_ScriptCommand
{
private:
	PK_tRotateCmd   m_Vars;
    float           m_fCurrentSpeed;
    bool            m_bBreaking;
    bool            m_bWrapped;
    
public:
	PK_RotateCmd(PK_Script &owner, PK_tRotateCmd &attribs);
    void Prepare();
	bool Execute(const PK_GameTimer &time);

    static PK_tRotateCmd * ParseAttributes(PK_CommandAttributes &attributes);
};

} // namespace

#endif