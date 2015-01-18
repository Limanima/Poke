#include "PK_SetAttributeCmd.h"
#include "PK_CommandAttributes.h"
#include "PK_tScriptVariable.h"
#include "PK_tScriptValue.h"
#include "PK_2DSceneControl.h"
#include "PK_Exceptions.h"

namespace PK {

//
PK_SetAttributeCmd::PK_SetAttributeCmd(PK_Script &owner, PK_tSetAttributeCmd &commandAttribs) :
	PK_ScriptCommand(owner, *(PK_tScriptCommand *)&commandAttribs)
{
	m_attribs = commandAttribs;
}


//
bool PK_SetAttributeCmd::Execute(const PK_GameTimer &time)
{
    PK_2DSceneControl *p2dControl = Get2DControl();
    if (p2dControl == NULL)
    {
        // FIXME: este comando deve ser aplicavel a objectos 3D
        throw PK_SystemException("Cannot execute 'set' command because current object is not a 2D object.", __FILE__, __LINE__);
    }

    if (!m_attribs.position.IsNull(GetScript()))
	{
        p2dControl->SetPosition(m_attribs.position.GetValue_Vector2(GetScript()));
	}

    if (!m_attribs.rotation.IsNull(GetScript()))
	{
        p2dControl->SetRotation(m_attribs.rotation.GetValue_Float(GetScript()));
	}

    if (!m_attribs.visibility.IsNull(GetScript()))
	{
        p2dControl->SetVisible(m_attribs.visibility.GetValue_Bool(GetScript()));
	}

    if (!m_attribs.input.IsNull(GetScript()))
	{
        p2dControl->SetWithInput(m_attribs.input.GetValue_Bool(GetScript()));
	}
        
    if (!m_attribs.color.IsNull(GetScript()))
	{
        p2dControl->SetColor(m_attribs.color.GetValue_Color(GetScript()));
	}

    if (m_attribs.m_CustomAttributes.GetCount() > 0)
    {
        for(PK_ListIterator(PK_tCommandAttribute) itor = m_attribs.m_CustomAttributes.Begin(); itor != m_attribs.m_CustomAttributes.End(); itor++)
	    {
            PK_tCommandAttribute *pAttrib = &(*itor);
            PK_tScriptValue1 var;
            if (pAttrib->bIsVariable)
            {
                var = GetScript().GetVariable(pAttrib->sValue).value;
            }
            else
            {
                var.SetValue(pAttrib->sValue);
            }
            p2dControl->SetCustomAttribute(pAttrib->sName, var); 
        }
    }
    
    return true;
}

//
PK_tSetAttributeCmd * PK_SetAttributeCmd::ParseAttributes(PK_CommandAttributes &attributes)
{
    PK_tSetAttributeCmd * pCmd = new PK_tSetAttributeCmd();

	for(PK_ListIterator(PK_tCommandAttribute) itor = attributes.GetAttributes().Begin(); itor != attributes.GetAttributes().End(); itor++)
	{
		PK_tCommandAttribute *pAttrib = &(*itor);
		if (pAttrib->sName == "position")
		{
			pCmd->position.SetValue_Vector2(pAttrib);
		}
		else
		if (pAttrib->sName == "rotation")
		{
			pCmd->rotation.SetValue_Float(pAttrib);
		}
        else
		if (pAttrib->sName == "visible")
		{
            pCmd->visibility.SetValue_Bool(pAttrib);
		}
		else
        if (pAttrib->sName == "withInput")
		{
            pCmd->input.SetValue_Bool(pAttrib);
		}
        else
        if (pAttrib->sName == "color")
		{
			pCmd->color.SetValue_Color(pAttrib);
		}
		else
		{
			pCmd->m_CustomAttributes.Add(*pAttrib);
		}
	}

    return pCmd;
}


} // namespace