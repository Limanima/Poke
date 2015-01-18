#ifndef _PK_SOUNDASSET_H_
#define _PK_SOUNDASSET_H_

#include "PK_Asset.h"

namespace PK {

// Interface para um som do tipo efeito sonoro
// E utilizado um interface porque o asset pode depender da plataforma
class PK_SoundAsset : public PK_Asset
{
 
public:
	PK_SoundAsset(PK_AssetContainer &assetContainer) :
		PK_Asset(AssetType_SoundEffect, assetContainer)
	{
	}
    virtual void Load() = 0;
};

} // namespace

#endif
