#ifndef _PK_SCRIPTCOMMAND_H_
#define _PK_SCRIPTCOMMAND_H_

#include "PK_String.h"
#include "PK_Scripting.h"
#include "PK_Script.h"
#include "PK_ScriptAsset.h"
#include "PK_tScriptValue.h"

namespace PK {

class PK_2DSceneControl;
class PK_GameTimer;

//
class PK_ScriptCommand
{
private:
    PK_Script	*m_pScript;
	PK_tScriptCommand m_BaseAttribs;
    bool         m_bExecuting;
    PK_2DSceneControl *m_pControlAs2DSceneControl;
    PK_SceneControl   *m_pControl;

public:
	PK_ScriptCommand(PK_Script &owner, PK_tScriptCommand &vars);
    virtual ~PK_ScriptCommand() {}
	 // E executado quando o script corre o Initialize
    virtual void InternalInitialize() {}
    // E executado quando o comando vai iniciar a execucao
    virtual void Prepare() {}
	// Comandos devem devolver true se acabaram a execucao ou false caso contrario
	virtual bool InternalExecute(const PK_GameTimer &time);
    virtual bool Execute(const PK_GameTimer &time) = 0;
	inline bool IsAsync() { return m_BaseAttribs.bAsync; }
    inline PK_Script & GetScript() { return *m_pScript; }
    inline PK_eScriptCommand GetCommandCode() { return m_BaseAttribs.commandCode; }
    inline PK_2DSceneControl * Get2DControl() { return m_pControlAs2DSceneControl; }
    inline PK_SceneControl * GetControl() { return m_pControl; }
};

} // namespace

#endif