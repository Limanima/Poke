#ifndef _PK_SCRIPTASSET_H_
#define _PK_SCRIPTASSET_H_

#include "PK_Asset.h"
#include "PK_Array.h"
#include "PK_Scripting.h"

namespace PK {
   
class PK_MemoryBuffer;

// 
class PK_ScriptAsset : public PK_Asset
{
protected:
	PK_Array<PK_tScriptCommand *> m_Commands;

public:
	PK_ScriptAsset(PK_AssetContainer &assetContainer);
	~PK_ScriptAsset();
    void Load();
	void Unload();

public:
	PK_tScriptCommand & GetCommand(unsigned int iCommandIdx);
	inline PK_Array<PK_tScriptCommand *> & GetCommands() { return m_Commands; }
	inline unsigned long GetCommandCount() { return m_Commands.GetCount(); }
};

} // namespace

#endif