#include "PK_FileAsset.h"
#include "PK_Exceptions.h"
#include "PK_Log.h"
#include "PK_FileReader.h"
#include "PK_ClassFactory.h"

namespace PK {
//
PK_FileAsset::PK_FileAsset(PK_AssetContainer &assetContainer) :
	PK_Asset(AssetType_File, assetContainer)
{
	SetTypeName("PK_FileAsset");
}

//
PK_FileAsset::~PK_FileAsset()
{
	Unload();
}

//
void PK_FileAsset::Unload()
{
    m_bLoaded = false;
}
 
//
void PK_FileAsset::Load()
{
    if (m_bLoaded)
    {
        throw PK_SystemException("SpriteSet asset named '%s' is already loaded.", __FILE__, __LINE__, GetName().c_str());
    }
    PK_String sFilename = GetAssetName();
    PK_FileReader file;
    file.ReadFile(sFilename, m_data); 
  
    m_bLoaded = true;
}

} // namespace
