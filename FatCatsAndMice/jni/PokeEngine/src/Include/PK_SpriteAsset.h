#ifndef _PK_SPRITEASSET_H_
#define _PK_SPRITEASSET_H_

#include "PK_Asset.h"
#include "PK_DataFileRecord.h"
#include "PK_tSize.h"
#include "PK_tBoundingSquare.h"
#include "PK_tSpriteFrame.h"
#include "PK_Array.h"
#include "PK_SpriteSetAsset.h"

namespace PK {
class PK_AssetContainer;
class PK_TextureAsset;
struct PK_tPrimitiveData;

class PK_SpriteAsset : public PK_Asset
{
private:
	unsigned int		           m_uiFps;
	PK_Array<PK_tSpriteFrame >     m_Frames;
    PK_Array<PK_tAABoundingSquare> m_CollisionBoxes;
    PK_tSize                       m_Size;
    PK_SpriteSetAsset            * m_pSpriteSet;
    PK_Vector2                     m_vPivot;
	PK_tPrimitiveData             *m_pPrimitiveData;
  
    
public:
    PK_SpriteAsset(PK_AssetContainer &assetContainer, PK_SpriteSetAsset &spriteSet);
	~PK_SpriteAsset();
	void InitFromDataFileRecord(PK_DataFileRecord & record);
    void Load();
	void Unload();
    PK_tAABoundingSquare GetCollisionBox(unsigned int idx);
    
    // Size
    inline PK_tSize GetSize() { return m_Size; }
    // Pivot
    inline PK_Vector2 GetPivot() { return m_vPivot; }
  
    // Frames
    inline PK_Array<PK_tSpriteFrame > * GetFrames() { return &m_Frames; }
    // Obter um frame (pointer)
    inline PK_tSpriteFrame * GetFramePtr(unsigned int uiFrameNr)
        { return &m_Frames[uiFrameNr]; }
    inline PK_tSpriteFrame GetFrame(unsigned int uiFrameNr)
    { return m_Frames[uiFrameNr]; }
    
    // Fps
    inline unsigned int GetFps() { return m_uiFps; }
    // FrameCount
    inline unsigned long GetFrameCount() { return m_Frames.GetCount(); }
    
    // Texture
    inline PK_TextureAsset * GetTexture() { return m_pSpriteSet->GetTexture(); }
    
    inline PK_Array<PK_tAABoundingSquare> & GetCollisionBoxes() { return m_CollisionBoxes; }
   

};

} // namespace

#endif