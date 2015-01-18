#ifndef _PK_SCRIPTCOMPILER_H_
#define _PK_SCRIPTCOMPILER_H_

#include "PK_String.h"
#include "PK_Scripting.h"

namespace PK {

class PK_ScriptAsset;
class PK_CommandAttributes;

//
class PK_ScriptCompiler
{
private:

public:
    PK_ScriptCompiler() {}
    void Compile(const PK_String &script, PK_ScriptAsset &intoAsset);

private:
    PK_eScriptCommand ExtractCommand(const PK_String & commandText, PK_CommandAttributes &retCommandAttribs);
	void InitializeCommonAttribs(PK_tScriptCommand &cmd, PK_CommandAttributes &attributes);
};

} // namespace

#endif