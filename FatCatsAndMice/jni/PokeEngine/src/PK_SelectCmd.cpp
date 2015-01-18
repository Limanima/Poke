#include "PK_SelectCmd.h"
#include "PK_CommandAttributes.h"
#include "PK_Scene.h"

namespace PK {

//
PK_SelectCmd::PK_SelectCmd(PK_Script &owner, PK_tSelectCmd &vars) :
	PK_ScriptCommand(owner, *(PK_tScriptCommand *)&vars)
{
	m_Vars = vars;
}

//
bool PK_SelectCmd::Execute(const PK_GameTimer &time)
{
    PK::PK_String sControlName = m_Vars.controlName.GetValue_Str(GetScript());
    PK_SceneControl * pControl = GetScript().GetScene()->FindControl(sControlName);
    if (pControl == NULL)
    {
        throw PK_SystemException("Error executing script command 'select'. Could not find control named '%s' in the scene '%s'.", 
            __FILE__, __LINE__, sControlName.c_str(),  GetScript().GetScene()->GetName().c_str());
    }
    GetScript().SetActiveControl(pControl);
    return true;
}


//
PK_tSelectCmd * PK_SelectCmd::ParseAttributes(PK_CommandAttributes &attributes)
{
   PK_tSelectCmd * pCmd = new PK_tSelectCmd();
   pCmd->controlName.SetValue_Str(attributes.GetAttribute("control"));

   return pCmd; 
}

} // namespace