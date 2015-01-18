#include "PK_SDLMusicAsset.h"	
#include "PK_Exceptions.h"
#include "PK_Types.h"
#include "PK_Path.h"

namespace PK {
    
PK_SDLMusicAsset::PK_SDLMusicAsset(PK_AssetContainer &assetContainer):
    PK_MusicAsset(assetContainer)
{
	SetTypeName("PK_SDLMusicAsset");
    m_pMusic = NULL;
}

PK_SDLMusicAsset::~PK_SDLMusicAsset()
{
    FreeResources();
}
    
//
void PK_SDLMusicAsset::FreeResources()
{
    if (m_pMusic != NULL)
    {
        Mix_FreeMusic(m_pMusic);
        m_pMusic = NULL;
    }
    m_bLoaded = false;
}

//
void PK_SDLMusicAsset::Load()
{
    if (m_bLoaded)
    {
        throw PK_SystemException("Music asset named '%s' is already loaded.", __FILE__, __LINE__, GetName().c_str());
    }
   
    PK_String sFilename = GetAssetName();
    if (!PK_Path::ContainsExtension(sFilename))
    {
        sFilename = PK_Path::CombineExtension(sFilename, PK_MUSIC_TYPE1_EXTENSION);
    }
    
    m_pMusic = Mix_LoadMUS(sFilename.c_str());
    if (m_pMusic == NULL)
    {
        throw PK_SDLException(SDLLib_SDL_Mixer, __FILE__, __LINE__);
    }

    m_bLoaded = true;

}

} // namespace
