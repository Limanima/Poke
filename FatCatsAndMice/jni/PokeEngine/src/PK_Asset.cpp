#include "PK_Asset.h"
#include "PK_AssetContainer.h"

namespace PK {

PK_Asset::PK_Asset(PK_eAssetType type, PK_AssetContainer &assetContainer)
{
	SetTypeName("PK_Asset");
	m_Type = type;
    m_pAssetContainer = &assetContainer;
    m_pAssetContainer->Grab();
    m_bLoaded = false;
}

PK_Asset::~PK_Asset()
{
    if (m_pAssetContainer != NULL)
    {
        m_pAssetContainer->Release();
        m_pAssetContainer = NULL;
    }
}


} // namespace