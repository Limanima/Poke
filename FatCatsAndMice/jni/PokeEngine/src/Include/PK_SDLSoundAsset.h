#ifndef _PK_SDLSOUNDASSET_H_
#define _PK_SDLSOUNDASSET_H_

#include "PK_Asset.h"
#include "PK_SoundAsset.h"
#include <SDL.h>
#include <SDL_mixer.h>

namespace PK {
class PK_AssetContainer;

// Asset do tipo efeito sonoro (utilizando SDL)
class PK_SDLSoundAsset : public PK_SoundAsset
{
private:
    Mix_Chunk * m_pSound;
  
public:
	PK_SDLSoundAsset (PK_AssetContainer &esourceContainer);
	~PK_SDLSoundAsset();
    void FreeResources();
    void Load();
    
    inline Mix_Chunk * GetChunk() { return m_pSound; }
};

} // namespace

#endif