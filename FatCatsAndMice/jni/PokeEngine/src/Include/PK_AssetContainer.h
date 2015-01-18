#ifndef _PK_ASSETCONTAINER_H_
#define _PK_ASSETCONTAINER_H_

#include "PK_String.h"
#include "PK_Object.h"
#include "PK_Asset.h"
#include "PK_TextureAsset.h"
#include "PK_List.h"

namespace PK {

class PK_AssetContainer : public PK_Object
{
private:

	int						 m_iContainerId;
	PK_List<PK_Asset *>   m_Assets;

public:
	PK_AssetContainer(const PK_String &sName);
	~PK_AssetContainer();
    void Unload();
 
	void AddAsset(PK_Asset * pAsset);
	void AddAsset(PK_TextureAsset * pAsset);
	PK_Asset * GetAsset(const PK_String &sName, PK_eAssetType type);
	bool ContainsAsset(const PK_String &sName, PK_eAssetType type);
	bool ContainsAsset(PK_Asset * pAsset);
    void UnloadAssetsOfType(PK_eAssetType type);
    inline PK_List<PK_Asset *> * GetAssets() { return &m_Assets; }
};

} // namespace

#endif
