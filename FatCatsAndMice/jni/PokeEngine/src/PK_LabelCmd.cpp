#include "PK_LabelCmd.h"
#include "PK_CommandAttributes.h"

namespace PK {

//
PK_LabelCmd::PK_LabelCmd(PK_Script &owner, PK_tLabelCmd &vars) :
	PK_ScriptCommand(owner, *(PK_tScriptCommand *)&vars)
{
	m_Vars = vars;
}


//
bool PK_LabelCmd::Execute(const PK_GameTimer &time)
{
    return true;
}

//
PK_String PK_LabelCmd::GetLabelName()
{
    return m_Vars.labelName.GetValue_Str(GetScript());  
}

//
PK_tLabelCmd * PK_LabelCmd::ParseAttributes(PK_CommandAttributes &attributes)
{
   PK_tLabelCmd * pCmd = new PK_tLabelCmd();
   pCmd->labelName.SetValue_Str(attributes.GetAttribute("name"));

   return pCmd; 
}

} // namespace