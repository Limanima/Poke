#include "PK_ScriptCommand.h"
#include "PK_Script.h"

namespace PK {

//
PK_ScriptCommand::PK_ScriptCommand(PK_Script &owner, PK_tScriptCommand &attribs)
{
	m_pScript = &owner;

	m_BaseAttribs = attribs;
    m_bExecuting = false;
}

//
bool PK_ScriptCommand::InternalExecute(const PK_GameTimer &time)
{
    if (!m_bExecuting)
    {
        m_pControlAs2DSceneControl = m_pScript->GetActive2DControl();
        m_pControl = m_pScript->GetActiveControl();
        Prepare();
        m_bExecuting = true;
    }
    bool bEnded = Execute(time);
    m_bExecuting = !bEnded;
    return bEnded;
}


} // namespace