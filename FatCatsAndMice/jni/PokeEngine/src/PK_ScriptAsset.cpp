#include "PK_ScriptAsset.h"
#include "PK_MemoryBuffer.h"
#include "PK_Path.h"
#include "PK_FileReader.h"
#include "PK_ClassFactory.h"
#include "PK_Exceptions.h"
#include "PK_MemoryBufferReader.h"
#include "PK_ScriptCompiler.h"
#include "PK_PauseCmd.h"

namespace PK {
//
PK_ScriptAsset::PK_ScriptAsset(PK_AssetContainer &assetContainer) :
	PK_Asset(AssetType_Script, assetContainer)
{
	SetTypeName("PK_ScriptAsset");
}

//
PK_ScriptAsset::~PK_ScriptAsset()
{
	Unload();
}

//
void PK_ScriptAsset::Unload()
{

}
 
//
void PK_ScriptAsset::Load()
{
    if (m_bLoaded)
    {
        throw PK_SystemException("Script asset named '%s' is already loaded.", __FILE__, __LINE__, GetName().c_str());
    }
    
    PK_String sFilename = PK_Path::CombineExtension(GetAssetName(), PK_SCRIPT_EXTENSION);
 	PK_MemoryBuffer memBuffer;
    PK_FileReader file;
    file.ReadFile(sFilename, memBuffer); 
    PK_ScriptCompiler compiler;
    compiler.Compile(memBuffer.GetAsStr(), *this); 

    m_bLoaded = true;
}


} // namespace
