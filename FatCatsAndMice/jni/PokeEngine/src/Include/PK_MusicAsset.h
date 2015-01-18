#ifndef _PK_MUSICSOURCE_H_
#define _PK_MUSICSOURCE_H_

#include "PK_Asset.h"

namespace PK {

// Interface para um asset do tipo musica
// Utiliza-se um asset porque o asset pode depender da plataforma
class PK_MusicAsset : public PK_Asset
{
 
public:
	PK_MusicAsset (PK_AssetContainer &assetContainer) :
		PK_Asset(AssetType_Music, assetContainer)
	{
	}
    virtual void Load() = 0;
};

} // namespace

#endif
