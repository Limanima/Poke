#include "PK_Globals.h"
#include "PK_DataFileAsset.h"
#include "PK_Path.h"

namespace PK {

PK_DataFileAsset::PK_DataFileAsset(PK_eAssetType type, PK_AssetContainer &assetContainer, const PK_String &sExtension):
	PK_Asset(type, assetContainer)
{
    m_sAssetExtension = sExtension;
    m_pRootRecord = NULL;
}

//
PK_DataFileAsset::~PK_DataFileAsset()
{
	FreeResources();
}

//
void PK_DataFileAsset::FreeResources()
{
    if (m_pRootRecord != NULL)
    {
        m_pRootRecord->Release();
        m_pRootRecord = NULL;
    }
}
  
//
void PK_DataFileAsset::Load()
{
    if (m_bLoaded)
    {
        throw PK_SystemException("Asset named '%s' is already loaded.", __FILE__, __LINE__, GetName().c_str());
    }

    PK_String sFilename = GetAssetName();
    if (!PK_Path::ContainsExtension(sFilename))
    {
        sFilename = PK_Path::CombineExtension(GetAssetName(), m_sAssetExtension);
    }
    
    PK_DataFile df;
    df.LoadFromXML(sFilename);
    m_pRootRecord = df.GetRoot();
    if (m_pRootRecord == NULL)
    {
        throw PK_SystemException("Could not load Font named %s because there's no root record.", __FILE__, __LINE__, sFilename.c_str());
    }
    m_pRootRecord->Grab();
    m_bLoaded = true;
}

//
PK_DataFileRecord * PK_DataFileAsset::GetRecord(const PK_String &sRecord)
{
    if (!m_bLoaded)
    {
        throw PK_SystemException("cannot get record named '%' because DataFile Asset named '%s' is not loaded.", 
            __FILE__, __LINE__, sRecord.c_str(), GetName().c_str());
    }

    return m_pRootRecord->SelectRecord(sRecord);
}

    
} // namespace
