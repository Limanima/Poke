#include "PK_SDLDXTextureAsset.h"	
#include "PK_DXRenderManager.h"	

namespace PK {

// 
PK_SDLDXTextureAsset::PK_SDLDXTextureAsset(PK_AssetContainer &assetContainer):
    PK_SDLTextureAsset(assetContainer)
{
	SetTypeName("PK_SDLDXTextureAsset");
	m_pTexture = NULL;
	m_pDXData = NULL;
}

//
PK_SDLDXTextureAsset::~PK_SDLDXTextureAsset()
{
	if (m_pTexture != NULL)
	{
		SDL_DestroyTexture(m_pTexture);
	}
}

//
void PK_SDLDXTextureAsset::BindTexture(SDL_Surface &surface)
{
	if (m_pTexture != NULL)
	{
		throw PK_SystemException("Texture is already binded.", __FILE__, __LINE__);
	}
	PK_DXRenderManager *pRenderManeger = PK_DXRenderManager::GetDXRenderManager();
	m_pTexture = SDL_CreateTextureFromSurface(pRenderManeger->GetRenderer(), &surface);
	if (m_pTexture == NULL)
	{
		throw PK_SDLException(__FILE__, __LINE__);
	}
	m_pDXData = (D3D11_TextureData*) m_pTexture->driverdata;
}


} // namespace
