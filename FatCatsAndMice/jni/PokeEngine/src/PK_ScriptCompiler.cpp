#include "PK_ScriptCompiler.h"
#include "PK_MemoryBuffer.h"
#include "PK_MemoryBufferReader.h"
#include "PK_ScriptAsset.h"
#include "PK_CommandAttributes.h"
#include "PK_SetAttributeCmd.h"
#include "PK_PauseCmd.h"
#include "PK_RotateCmd.h"
#include "PK_MoveCmd.h"
#include "PK_LoopCmd.h"
#include "PK_LabelCmd.h"
#include "PK_PlaySoundCmd.h"
#include "PK_SelectCmd.h"

#define COMMAND_DELIMITER ' ' 
#define PARAM_DELIMITER ';' 
#define PROPERTY_TERMINATOR ':' 
#define COMMENT_CHAR '#' 
#define VARIABLE_INDICATOR '%'

namespace PK {

//
void PK_ScriptCompiler::Compile(const PK_String &sScript, PK_ScriptAsset &intoAsset)
{ 
    PK_MemoryBuffer buffer(sScript);
    PK_MemoryBufferReader reader(buffer);

	PK_CommandAttributes attributes;
	PK_List<PK_tScriptCommand *> commandList;
    PK_tScriptCommand *pCmd;
    
    while(!reader.IsAtEOB())
    {
        PK_String line = reader.ReadLine();
        line = line.Trim(line);
        if (line == "" || line[0] == COMMENT_CHAR)
        {
            continue;
        }
        
		PK_eScriptCommand command = ExtractCommand(line, attributes);
		switch(command)
		{
			case ScriptCommand_SetAttribute:
                pCmd = PK_SetAttributeCmd::ParseAttributes(attributes);
				break;
			case ScriptCommand_Move:
                pCmd = PK_MoveCmd::ParseAttributes(attributes);
				break;  
            case ScriptCommand_Rotate:
                pCmd = PK_RotateCmd::ParseAttributes(attributes);
				break;
            case ScriptCommand_Pause:
                pCmd = PK_PauseCmd::ParseAttributes(attributes);
				break;
            case ScriptCommand_Loop:
                pCmd = PK_LoopCmd::ParseAttributes(attributes);
				break;
            case ScriptCommand_Label:
                pCmd = PK_LabelCmd::ParseAttributes(attributes);
				break;
            case ScriptCommand_Select:
                pCmd = PK_SelectCmd::ParseAttributes(attributes);
				break;
            case ScriptCommand_PlaySound:
                pCmd = PK_PlaySoundCmd::ParseAttributes(attributes);
				break;
			case ScriptCommand_UserDefined:
				throw PK_SystemException("User defined commands are not supported. Command line is %s.", 
                    __FILE__, __LINE__, line.c_str());
		} 
		InitializeCommonAttribs(*pCmd, attributes);
		commandList.Add(pCmd);
    }
   
    intoAsset.GetCommands().SetSize(commandList.GetCount());
	int i = 0;
	for(PK_ListIterator(PK_tScriptCommand *) itor = commandList.Begin(); itor != commandList.End(); itor++)
	{
		intoAsset.GetCommands()[i++] = (*itor);
	}
}

//
PK_eScriptCommand PK_ScriptCompiler::ExtractCommand(const PK_String & commandText, PK_CommandAttributes &retCommandAttribs)
{
	unsigned long iPos = commandText.find(COMMAND_DELIMITER);
	
	if (iPos == PK_String::npos)
	{
		if (commandText.length() == 0)
		{
			throw PK_SystemException("PK Script compilation error. Commands cannot be empty.", __FILE__, __LINE__);
		}
        iPos = commandText.length();
	}

	// Command
	PK_eScriptCommand command = ScriptCommand_UserDefined;
	PK_String cmd = commandText.substr(0, iPos);
	if (cmd == "set")
	{
		command = ScriptCommand_SetAttribute;
	}
    else
	if (cmd == "move")
	{
		command = ScriptCommand_Move;
	}	
    else
	if (cmd == "rotate")
	{
		command = ScriptCommand_Rotate;
	}
    else
    if (cmd == "pause")
	{
		command = ScriptCommand_Pause;
	}
    else
    if (cmd == "loop")
	{
		command = ScriptCommand_Loop;
	}
    else
    if (cmd == "label")
	{
		command = ScriptCommand_Label;
	}
    else
    if (cmd == "select")
	{
		command = ScriptCommand_Select;
	}
    else
    if (cmd == "play_sound")
	{
		command = ScriptCommand_PlaySound;
	}
	// Properties
	PK_String sParams = commandText.substr(iPos);
	PK_Array<PK_String> pars;
	sParams.Split(PARAM_DELIMITER, pars);
    retCommandAttribs.ClearAttributes();
	for(int i = 0; i < pars.GetCount(); i++)
	{
		pars[i] = pars[i].Trim(pars[i]);
		if (pars[i]== "")
		{
            if (i + 1 == pars.GetCount())
            {
                break;
            }
			throw PK_SystemException("Script parse error. Property names are mandatory in commands.", __FILE__, __LINE__);
		}
		PK_tCommandAttribute param;
		iPos = pars[i].find(PROPERTY_TERMINATOR);
		if (iPos == PK_String::npos)
		{
			param.sName = pars[i];
			param.sValue = "";
		}
		else
		{
			param.sName = pars[i].substr(0, iPos);
            param.sName = param.sName.Trim(param.sName);
			param.sValue = pars[i].substr(iPos + 1);
            param.sValue = param.sValue.Trim(param.sValue);
		}

        param.bIsVariable = (param.sValue.length() >=3 && param.sValue[0] == VARIABLE_INDICATOR && param.sValue[param.sValue.length() - 1] == VARIABLE_INDICATOR);
        if (param.bIsVariable)
        {
            param.sValue = param.sValue.substr(1, param.sValue.length() - 2);
        }
        retCommandAttribs.AddAttribute(param);
	}

	return command;
}

//
void PK_ScriptCompiler::InitializeCommonAttribs(PK_tScriptCommand &cmd, PK_CommandAttributes &attributes)
{
	cmd.bAsync = attributes.ContainsAttribute("async");
}

} // namespace