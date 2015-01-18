#include "PK_Consts.h"
#include "PK_SDLSoundAsset.h"	
#include "PK_Exceptions.h"
#include "PK_Types.h"
#include "PK_Path.h"
#include <SDL.h>

namespace PK {
    
PK_SDLSoundAsset::PK_SDLSoundAsset(PK_AssetContainer &assetContainer):
    PK_SoundAsset(assetContainer)
{
	SetTypeName("PK_SDLSoundAsset");

}

PK_SDLSoundAsset::~PK_SDLSoundAsset()
{
    FreeResources();
}
    
//
void PK_SDLSoundAsset::FreeResources()
{
    if (m_pSound != NULL)
    {
        Mix_FreeChunk(m_pSound);
        m_pSound = NULL;
    }
    m_bLoaded = false;
}
    

//
void PK_SDLSoundAsset::Load()
{
    if (m_bLoaded)
    {
        throw PK_SystemException("Sound Effect asset named '%s' is already loaded.", __FILE__, __LINE__, GetName().c_str());
    }
    
    PK_String sFilename = GetAssetName();
    if (!PK_Path::ContainsExtension(sFilename))
    {
        sFilename = PK_Path::CombineExtension(sFilename, PK_SOUND_TYPE1_EXTENSION);
    }

    m_pSound = Mix_LoadWAV(sFilename.c_str());
    if (m_pSound == NULL)
    {
        throw PK_SDLException(SDLLib_SDL_Mixer, __FILE__, __LINE__);
    }

    m_bLoaded = true;
}

} // namespace
