#include "PK_SpriteSetAsset.h"
#include "PK_Path.h"
#include "PK_Globals.h"
#include "PK_Exceptions.h"
#include "PK_SpriteAsset.h"
#include "PK_DataFile.h"
#include "PK_Log.h"

namespace PK {
//
PK_SpriteSetAsset::PK_SpriteSetAsset(PK_AssetContainer &assetContainer) :
	PK_Asset(AssetType_SpriteSet, assetContainer)
{
	SetTypeName("PK_SpriteSetAsset");
}

//
PK_SpriteSetAsset::~PK_SpriteSetAsset()
{
	Unload();
}

//
void PK_SpriteSetAsset::Unload()
{
    for(unsigned int i = 0; i < m_Sprites.GetCount(); i++)
	{
        m_Sprites[i]->Unload();
		m_Sprites[i]->Release();
	}
	m_Sprites.Clear();
    if (m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
    m_bLoaded = false;
}
 
//
void PK_SpriteSetAsset::Load()
{
    if (m_bLoaded)
    {
        throw PK_SystemException("SpriteSet asset named '%s' is already loaded.", __FILE__, __LINE__, GetName().c_str());
    }
    
    PK_String sFilename = PK_Path::CombineExtension(GetAssetName(), PK_SPRITESET_EXTENSION);
    PK_DataFile df;
    df.LoadFromXML(sFilename);
	PK_DataFileRecord * pRootRec = df.GetRoot();
	if (pRootRec == NULL)
    {
        throw PK_SystemException("Could not load SpriteSet named %s because there's no root record.", __FILE__, __LINE__, sFilename.c_str());
    }
    InitFromDataFileRecord(*pRootRec);
    
    for(int i = 0; i < m_Sprites.GetCount(); i++)
	{
        m_Sprites[i]->Load();
    }
    m_bLoaded = true;
}
    
// Devolve o Sprite com o nome sName
PK_SpriteAsset * PK_SpriteSetAsset::GetSprite(const PK_String & sName)
{
    for(unsigned int i = 0; i < m_Sprites.GetCount(); i++)
	{
		if (m_Sprites[i]->GetName() == sName)
        {
            return m_Sprites[i];
        }
	}
    
    throw PK_SystemException("Sprite named '%s' does not exist in SpriteSet named '%s'.", __FILE__, __LINE__, sName.c_str(), GetName().c_str());
}
    
//
void PK_SpriteSetAsset::InitFromDataFileRecord(PK_DataFileRecord & record)
{
   
    // Textura
    SetName(record.GetFieldValue_String("Name"));
    m_sImageAssetName = record.GetFieldValue_String("ImageId");
    m_pTexture = PokeEngine.GetAssetManager().LoadTexture(m_sImageAssetName, m_pAssetContainer->GetName());
    m_pTexture->Grab();
    
    // Obter todos os sprites
    PK_List<PK_DataFileRecord * > spriteRecs;
    record.SelectRecords("Sprite", spriteRecs, false);
    if (spriteRecs.GetCount() > 0)
    {
        m_Sprites.Clear();
        m_Sprites.SetSize(spriteRecs.GetCount());
        int i = 0;
        for(PK_ListIterator(PK_DataFileRecord *) itor = spriteRecs.Begin(); itor != spriteRecs.End(); itor++, i++)
        {
            PK_SpriteAsset *pSpriteRes = new PK_SpriteAsset(*m_pAssetContainer, *this);
            PK_CHECK_OBJECT_ALLOC(PK_SpriteAsset, pSpriteRes);
            pSpriteRes->InitFromDataFileRecord(*(*itor));
            m_Sprites[i] = pSpriteRes;
            pSpriteRes->Grab();
        }
    }
}

} // namespace
