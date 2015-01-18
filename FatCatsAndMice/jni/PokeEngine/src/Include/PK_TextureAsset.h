#ifndef _PK_TEXTUREASSET_H_
#define _PK_TEXTUREASSET_H_

#include "PK_Asset.h"
#include "PK_tSize.h"
#include "PK_Exceptions.h"

namespace PK {

// Guarda uma textura
class PK_TextureAsset : public PK_Asset
{
protected:
    PK_tSize m_Size;
    char     m_chBytesPerPixel;
 
public:
	PK_TextureAsset(PK_AssetContainer &assetContainer) :
		PK_Asset(AssetType_Texture, assetContainer)
	{
	}
    virtual void Load() = 0;
    
    inline PK_tSize GetSize() const
    {
        return m_Size;
    }
};

} // namespace

#endif
