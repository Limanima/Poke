#ifndef _PK_SPRITESETASSET_H_
#define _PK_SPRITESETASSET_H_

#include "PK_Asset.h"
#include "PK_String.h"
#include "PK_Array.h"


namespace PK {
class PK_AssetContainer;
class PK_SpriteAsset;
class PK_TextureAsset;
class PK_DataFileRecord;
    
// Guarda uma textura
class PK_SpriteSetAsset : public PK_Asset
{
protected:
	PK_Array<PK_SpriteAsset *> m_Sprites;
	PK_String					  m_sImageAssetName;
	PK_TextureAsset		    * m_pTexture;

public:
	PK_SpriteSetAsset(PK_AssetContainer &assetContainer);
	~PK_SpriteSetAsset();
    void Load();
	void Unload();
    PK_SpriteAsset * GetSprite(const PK_String & sName);
    inline PK_TextureAsset * GetTexture() { return m_pTexture; }

	void InitFromDataFileRecord(PK_DataFileRecord & record);
};

} // namespace

#endif