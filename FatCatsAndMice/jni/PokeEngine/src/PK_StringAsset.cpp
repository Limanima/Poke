#include "PK_StringAsset.h"
#include "PK_Exceptions.h"
#include "PK_Log.h"
#include "PK_Path.h"
#include "PK_DataFile.h"

namespace PK {
//
PK_StringAsset::PK_StringAsset(PK_AssetContainer &assetContainer) :
	PK_Asset(AssetType_String, assetContainer)
{
	SetTypeName("PK_StringAsset");
}

//
PK_StringAsset::~PK_StringAsset()
{
	Unload();
}

//
void PK_StringAsset::Unload()
{
    m_bLoaded = false;
}
 
//
void PK_StringAsset::Load()
{
    if (m_bLoaded)
    {
        throw PK_SystemException("String asset named '%s' is already loaded.", __FILE__, __LINE__, GetName().c_str());
    }
    
    PK_String sFilename = GetAssetName();
    if (!PK_Path::ContainsExtension(sFilename))
    {
        sFilename = PK_Path::CombineExtension(GetAssetName(), PK_STRING_ASSET_EXTENSION);
    }
    
    PK_DataFile df;
    df.LoadFromXML(sFilename);
    PK_DataFileRecord *pRoot = df.GetRoot();
    if (pRoot == NULL)
    {
        throw PK_SystemException("Could not load Font named %s because there's no root record.", __FILE__, __LINE__, sFilename.c_str());
    }
    InitFromDataFileRecord(*pRoot);

    m_bLoaded = true;
}

// 
void PK_StringAsset::InitFromDataFileRecord(PK_DataFileRecord & record)
{
    m_strings.Clear();
    PK_List<PK_DataFileRecord *> stringsRec;
    record.SelectRecords("stringAsset/string", stringsRec, false);
    
    for(PK_ListIterator(PK_DataFileRecord *) itor = stringsRec.Begin(); itor != stringsRec.End(); itor++)
    {
      PK_DataFileRecord *stringRec = (*itor);
      PK_String id = stringRec->GetFieldValue_String("id");
      PK_String val = stringRec->GetFieldValue_String("value");
      m_strings.Add(id, val);
    }
}

//
PK_String PK_StringAsset::GetString(const PK_String &stringId)
{
    return m_strings[stringId];
}

} // namespace
