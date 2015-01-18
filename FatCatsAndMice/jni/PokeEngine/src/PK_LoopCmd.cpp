#include "PK_LoopCmd.h"
#include "PK_CommandAttributes.h"

namespace PK {

//
PK_LoopCmd::PK_LoopCmd(PK_Script &owner, PK_tLoopCmd &vars) :
	PK_ScriptCommand(owner, *(PK_tScriptCommand *)&vars)
{
	m_Vars = vars;
}


//
bool PK_LoopCmd::Execute(const PK_GameTimer &time)
{
    PK::PK_String sName = m_Vars.labelName.GetValue_Str(GetScript());
    if (sName == "")
    {
        GetScript().GotoBeginning();
    }
    else
    {
        GetScript().GotoLabel(sName);
    }

    return true;
}

//
PK_tLoopCmd * PK_LoopCmd::ParseAttributes(PK_CommandAttributes &attributes)
{
   PK_tLoopCmd * pCmd = new PK_tLoopCmd();
   pCmd->labelName.SetValue_Str(attributes.GetAttribute("label", false));

   return pCmd; 
}

} // namespace