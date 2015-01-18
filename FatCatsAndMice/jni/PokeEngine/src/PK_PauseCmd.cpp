#include "PK_PauseCmd.h"
#include "PK_CommandAttributes.h"

namespace PK {

//
PK_PauseCmd::PK_PauseCmd(PK_Script &owner, PK_tPauseCmd &vars) :
	PK_ScriptCommand(owner, *(PK_tScriptCommand *)&vars)
{
	m_Vars = vars;
}

//
void PK_PauseCmd::Prepare()
{
	m_uiEllapsed = 0;
}

//
bool PK_PauseCmd::Execute(const PK_GameTimer &time)
{
	m_uiEllapsed += time.GetEllapsedTime();
	return (m_uiEllapsed >= (unsigned int)m_Vars.duration.GetValue_Int(GetScript()));
}

//
PK_tPauseCmd * PK_PauseCmd::ParseAttributes(PK_CommandAttributes &attributes)
{
   PK_tPauseCmd * pCmd = new PK_tPauseCmd();
   pCmd->duration.SetValue_Int(attributes.GetAttribute("duration"));
   return pCmd;
}

} // namespace