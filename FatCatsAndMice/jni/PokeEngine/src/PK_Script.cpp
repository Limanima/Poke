#include "PK_Script.h" 
#include "PK_ScriptAsset.h"
#include "PK_Globals.h"
#include "PK_SetAttributeCmd.h"
#include "PK_MoveCmd.h"
#include "PK_PauseCmd.h"
#include "PK_RotateCmd.h"
#include "PK_LoopCmd.h"
#include "PK_LabelCmd.h"
#include "PK_PlaySoundCmd.h"
#include "PK_SelectCmd.h"
#include "PK_tScriptVariable.h"

namespace PK {

//
PK_Script::PK_Script(const PK_String &sName) :
	PK_SceneControl(sName)
{
	SetTypeName("PK_Script");
	m_pScriptAsset = NULL;
	m_bExecuting = false;
	m_iCurrentCommand = 0;
    m_pActiveControlAs2DSceneControl = NULL;
    m_pActiveControl = NULL;
    m_iExecutingAsyncCommands = 0;
}
     
//
PK_Script::~PK_Script()
{
	if (m_pScriptAsset != NULL)
	{
		m_pScriptAsset->Release();
	}

	for(int i = 0; i < m_Commands.GetCount(); i++)
	{
		delete m_Commands[i];
	}
}

//
void PK_Script::InternalLoad()
{
    PK_SceneControl::InternalLoad();
    if (m_sScriptAssetName != "")
    {
        PK_String sContainerName = GetAssetContainerName();
        SetScriptAsset(PokeEngine.GetAssetManager().LoadScript(m_sScriptAssetName, sContainerName));
    }
}

//
void PK_Script::InternalInitialize()
{
    SetActiveControl(GetParent());
	if (m_pScriptAsset != NULL)
	{
		PK_Array<PK_tScriptCommand *> *pCommands = &m_pScriptAsset->GetCommands();
		PK_ScriptCommand *pCmd;
		m_Commands.SetSize(pCommands->GetCount());
		for(int i = 0; i < pCommands->GetCount(); i++)
		{
            PK_tScriptCommand * pCmdData = (*pCommands)[i];
            switch(pCmdData->commandCode)
			{
				case ScriptCommand_SetAttribute:
					pCmd = new PK_SetAttributeCmd(*this, *(PK_tSetAttributeCmd *)pCmdData);
					break;
				case ScriptCommand_Move:
					pCmd = new PK_MoveCmd(*this, *(PK_tMoveCmd *)pCmdData);
					break;
				case ScriptCommand_Rotate:
                    pCmd = new PK_RotateCmd(*this, *(PK_tRotateCmd *)pCmdData);
					break;
				case ScriptCommand_Pause:
					pCmd = new PK_PauseCmd(*this, *(PK_tPauseCmd *)pCmdData);
					break;
                case ScriptCommand_Loop:
					pCmd = new PK_LoopCmd(*this, *(PK_tLoopCmd *)pCmdData);
					break;
                case ScriptCommand_Label:
					pCmd = new PK_LabelCmd(*this, *(PK_tLabelCmd *)pCmdData);
					break;
                case ScriptCommand_Select:
					pCmd = new PK_SelectCmd(*this, *(PK_tSelectCmd *)pCmdData);
					break;
                case ScriptCommand_PlaySound:
					pCmd = new PK_PlaySoundCmd(*this, *(PK_tPlaySoundCmd *)pCmdData);
					break;
				case ScriptCommand_UserDefined:
					break;
				default:
					throw PK_SystemException("Script named '%s' has an invalid command('%d').", __FILE__, __LINE__, 
								m_pScriptAsset->GetName().c_str(), pCmdData->commandCode);
			}
			m_Commands[i] = pCmd;
		}
	}

    PK_SceneControl::InternalInitialize();
    for(int i = 0;  i < m_Commands.GetCount(); i++)
    {
        m_Commands[i]->InternalInitialize();
    }
}

//
void PK_Script::InternalUpdate(const PK_GameTimer &time)
{
    //
	if (!m_bExecuting)
	{
        PK_SceneControl::InternalUpdate(time);
        return;
    }


    // Se n esta a executar nenhum comando, vai buscar para a lista de comandos do script
    if (m_ExecutingCommands.GetCount() == m_iExecutingAsyncCommands)
    {
        // Nao pode parar se estiver a executar comandos async
        if (m_iCurrentCommand >= m_Commands.GetCount() && m_iExecutingAsyncCommands == 0)
        {
            PK_SceneControl::InternalUpdate(time);
            m_bExecuting = false;
            return;
        }

        if (m_iCurrentCommand < m_Commands.GetCount())
        {
            PK_ScriptCommand *pCmd;
		    do
		    {
			    pCmd = m_Commands[m_iCurrentCommand];
			    m_ExecutingCommands.Add(pCmd);
			    m_iCurrentCommand++;
                if (pCmd->IsAsync())
                {
                    m_iExecutingAsyncCommands++;
                }
		    }
		    while(m_iCurrentCommand < m_Commands.GetCount() && pCmd->IsAsync());

		    if (m_ExecutingCommands.GetCount() == 0)
		    { 
			    m_bExecuting = false;
		    }
        }
	} 

	if (m_bExecuting)
	{
		for(PK_ListIterator(PK_ScriptCommand *) itor = m_ExecutingCommands.Begin(); itor != m_ExecutingCommands.End(); )
		{
			PK_ScriptCommand *pCmd = (*itor);
			if (pCmd->InternalExecute(time) == true)
			{
                if (m_ExecutingCommands.GetCount() == 0) // Algum comando pode ter forcado a limpeza da lista
                {
                    break;
                }
                if ((*itor)->IsAsync())
                {
                    m_iExecutingAsyncCommands--;
                }
                m_ExecutingCommands.Erase(itor++);
			}
            else
            {
                itor++;
            }
		}
	}
	
	PK_SceneControl::InternalUpdate(time);
}

//
void PK_Script::SetScriptAsset(PK_ScriptAsset &asset)
{
    if (m_pScriptAsset != NULL)
	{
		m_pScriptAsset->Release();
	}
    m_pScriptAsset = &asset;
    m_pScriptAsset->Grab();
}

//
void PK_Script::Break()
{
    m_bExecuting = false;
}

//
void PK_Script::Execute()
{
    if (GetParent() == NULL)
    {
		throw PK_SystemException("Cannot execute script name '%s' because it's not attached to a parent control.", __FILE__, __LINE__, GetName().c_str());
    }

	if (m_pScriptAsset == NULL)
	{
		throw PK_SystemException("Cannot execute script name '%s' because no script was loaded.", __FILE__, __LINE__, GetName().c_str());
	}
	if (m_bExecuting)
	{
        PK_Log::WriteWarning(PK_LOG_TAG, "Script named '%s' is already running.", GetName().c_str());
        return;
	}

	if (m_Commands.GetCount() > 0)
	{
		m_bExecuting = true;
		m_iCurrentCommand = 0;
        m_iExecutingAsyncCommands = 0;
		m_ExecutingCommands.Clear();
	}
}

//
void PK_Script::GotoBeginning()
{
    m_ExecutingCommands.Clear();
    m_iCurrentCommand = 0;
}

//
void PK_Script::GotoLabel(const PK::PK_String &sLabel)
{
    // 
    for(int i = 0; i < m_Commands.GetCount(); i++)
	{
        if (m_Commands[i]->GetCommandCode() == ScriptCommand_Label)
        {
            PK_LabelCmd *pLabel = (PK_LabelCmd *)m_Commands[i];
            if (pLabel->GetLabelName() == sLabel)
            {
                m_ExecutingCommands.Clear();
                m_iCurrentCommand = i;
                return;
            }
        }
    }

    throw PK_SystemException("Cannot loop to label '%s' because it does not exist in script named '%s'.", 
            __FILE__, __LINE__, sLabel.c_str(), GetName().c_str());
}

//
void PK_Script::SetVariable(const PK_String &sName, int iValue)
{
    PK_tScriptValue1 v(iValue);
    SetVariable(sName, v);
}

//
void PK_Script::SetVariable(const PK_String &sName, const PK_Vector2 &vValue)
{
    PK_tScriptValue1 v(vValue);
    SetVariable(sName, v);
}

//
void PK_Script::SetVariable(const PK_String &sName, PK_tScriptValue1 &value)
{
    PK_tScriptVariable *pVar = FindVariable(sName);
    if (pVar != NULL)
    {
        pVar->value = value;
    }
    else
    {
        PK_tScriptVariable newVar;
        newVar.sName = sName;
        newVar.value = value;
        m_GlobalVars.Add(newVar);
    }
}

//
PK_tScriptVariable PK_Script::GetVariable(const PK_String &sName)
{
    PK_tScriptVariable *pVar = FindVariable(sName);
    if (pVar != NULL)
    {
        return (*pVar);
    }
    PK_tScriptVariable var;
    var.sName = sName;
    return var;
}

//
void PK_Script::SetActiveControl(PK_SceneControl *pControl)
{
    m_pActiveControl = pControl;
    m_pActiveControlAs2DSceneControl = (pControl != NULL && pControl->Is2DControl()? (PK_2DSceneControl*) pControl: NULL);
}

//
PK_tScriptVariable * PK_Script::FindVariable(const PK_String &sName)
{
    for(PK_ListIterator(PK_tScriptVariable) itor = m_GlobalVars.Begin(); itor != m_GlobalVars.End(); itor++)
	{
        PK_tScriptVariable *pVar = &(*itor);
		if (pVar->sName == sName)
        {
            return pVar;
        }
    }
    return NULL;
}

} // namespace