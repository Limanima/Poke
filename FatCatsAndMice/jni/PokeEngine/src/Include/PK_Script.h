#ifndef _PK_SCRIPT_H_
#define _PK_SCRIPT_H_

#include "PK_SceneControl.h"
#include "PK_List.h"
#include "PK_Array.h"
#include "PK_Scripting.h"

namespace PK {

class PK_ScriptCommand;
class PK_ScriptAsset;
class PK_2DSceneControl;
class PK_tScriptValue;
struct PK_tScriptVariable;

// 
class PK_Script : public PK_SceneControl
{
private:
	PK_ScriptAsset    *m_pScriptAsset;
    PK_2DSceneControl *m_pActiveControlAs2DSceneControl;
    PK_SceneControl   *m_pActiveControl;
	// Lista de comandos nos script
	PK_Array<PK_ScriptCommand *> m_Commands;
	// Lista de comandos a executar. Sao executados todos os comandos que estiverem
	// nesta lista em simultaneo
	PK_List<PK_ScriptCommand *> m_ExecutingCommands;
    PK_List<PK_tScriptVariable> m_GlobalVars;
    PK_String        m_sScriptAssetName;
	bool			 m_bExecuting;
	int              m_iCurrentCommand;
    int              m_iExecutingAsyncCommands;

public:
	PK_Script(const PK_String &sName);
	~PK_Script();
    void InternalLoad();
    void InternalInitialize();
    void InternalUpdate(const PK_GameTimer &time);
    void SetScriptAsset(PK_ScriptAsset &asset);
    void Break();
    void Execute();
    void GotoBeginning();
    void GotoLabel(const PK::PK_String &sLabel);
    void SetVariable(const PK_String &sName, PK_tScriptValue1 &value);
    void SetVariable(const PK_String &sName, int iValue);
    void SetVariable(const PK_String &sName, const PK_Vector2 &v);
    PK_tScriptVariable GetVariable(const PK_String &sName);
    void SetActiveControl(PK_SceneControl *pControl);

private:
    void ClearGlobalVars();
    PK_tScriptVariable * FindVariable(const PK_String &sName);

public:
    inline void SetScriptAssetName(const PK_String &sName) { m_sScriptAssetName = sName; }
    inline PK_2DSceneControl * GetActive2DControl() { return m_pActiveControlAs2DSceneControl ; } 
    inline PK_SceneControl * GetActiveControl() { return m_pActiveControl; } 
 
};

} // namespace

#endif