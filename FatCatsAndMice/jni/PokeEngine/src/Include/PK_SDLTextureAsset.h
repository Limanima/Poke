#ifndef _PK_SDLTEXTUREASSET_H_
#define _PK_SDLTEXTUREASSET_H_

#include <sdl.h>
#include "PK_Asset.h"
#include "PK_TextureAsset.h"
#include "PK_MemoryBuffer.h"

struct SDL_Surface;

namespace PK {
class PK_AssetContainer;


// Guarda uma textura
class PK_SDLTextureAsset : public PK_TextureAsset
{
private:
	unsigned int m_iglTexture;

public:
	PK_SDLTextureAsset(PK_AssetContainer &assetContainer);
	~PK_SDLTextureAsset();
    void FreeResources();
    void Load();
	virtual void BindTexture(SDL_Surface &pSurface) {}
    int GetWidth();
    int GetHeight();
    inline unsigned int GetGlTextureId() const { return m_iglTexture; }
};

} // namespace

#endif