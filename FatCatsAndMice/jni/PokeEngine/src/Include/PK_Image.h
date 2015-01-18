#ifndef _PK_IMAGE_H_
#define _PK_IMAGE_H_

#include "PK_String.h"
#include "PK_2DSceneControl.h"
#include "PK_TextureAsset.h"

namespace PK {

class PK_Image : public PK_2DSceneControl
{

private:
    PK_String            m_sTextureAssetName;
    PK_TextureAsset * m_pTexture;

public:
    PK_Image(const PK_String &sName = "");
    ~PK_Image();
    void InitFromDataFileRecord(PK_DataFileRecord &record);
    void OnLoad();
    void OnDraw();
    void OnUnload();
    void SetTexture(PK_TextureAsset *pTexture);
    
    // Nome do asset da textura
    inline void SetTextureAssetName(const PK_String &sAssetName) { m_sTextureAssetName = sAssetName; };
};

}

#endif
