#ifndef _PK_SDLGLTEXTUREREASSET_H_
#define _PK_SDLGLTEXTUREREASSET_H_

#include "PK_Asset.h"
#include "PK_SDLTextureAsset.h"

namespace PK {
class PK_AssetContainer;

// Guarda uma textura
class PK_SDLGLTextureAsset : public PK_SDLTextureAsset
{
private:

public:
	PK_SDLGLTextureAsset(PK_AssetContainer &assetContainer);
  void Load();
};

} // namespace

#endif