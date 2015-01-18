#ifndef _PK_SDLMUSICREASSET_H_
#define _PK_SDLMUSICREASSET_H_

#include <sdl.h>
#include <SDL_mixer.h>
#include "PK_Asset.h"
#include "PK_MusicAsset.h"

namespace PK {
class PK_AssetContainer;

// Asset do tipo musica utilizando SDL
class PK_SDLMusicAsset : public PK_MusicAsset
{
    Mix_Music * m_pMusic;
    
public:
	PK_SDLMusicAsset(PK_AssetContainer &assetContainer);
	~PK_SDLMusicAsset();
    void FreeResources();
    void Load();
    
    inline Mix_Music * GetChunk() { return m_pMusic; }
};

} // namespace

#endif