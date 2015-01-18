#include "PK_SDLGLTextureAsset.h"	
#include "PK_SceneManager.h"
#include <SDL.h>
 
namespace PK {
    
PK_SDLGLTextureAsset::PK_SDLGLTextureAsset(PK_AssetContainer &assetContainer):
    PK_SDLTextureAsset(assetContainer)
{
	SetTypeName("PK_SDLGLTextureAsset");
}
//
void PK_SDLGLTextureAsset::Load()
{
    m_bLoaded = true;
}

 
} // namespace
