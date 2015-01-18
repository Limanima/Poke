#ifndef _PK_SCENESPRITE_H_
#define _PK_SCENESPRITE_H_
 
#include "PK_2DSceneControl.h"
#include "PK_SpriteAsset.h"
#include "PK_Sprite.h"
#include "PK_tSize.h"

namespace PK {

class PK_Sprite : public PK_2DSceneControl
{

private:
    PK_String           m_sSpriteAssetName; // Inclui o nome do spriteset spriteset\sprite
    PK_SpriteAsset    * m_pSpriteAsset;
    unsigned int        m_uiEllapsedTime;
    bool                m_bAnimationActive;
    unsigned int        m_uiCurrentFrame;
    unsigned int        m_uiFps;

    // Shadow support
    bool                m_bWithShadow;
    PK_Vector2          m_vShadowDepth;
    PK_Color            m_ShadowColor;

public:
    PK_Callback<PK::PK_IObjectCallback> OnLastFrame;

public:
    PK_Sprite(const PK_String &sName = "");
    ~PK_Sprite();
    void FreeResources();
    void InitFromDataFileRecord(PK_DataFileRecord &record);
    // Internal
    void InternalLoad();
    void InternalUpdate(const PK_GameTimer &time);
    void InternalAfterDrawBackground();
    void InternalUnload();
    virtual void Copy(PK_SceneControl &copyFrom);

    void SetSprite(PK_SpriteAsset *pAsset);
    void SetShadow(bool bEnable, const PK_Vector2 vDepth, const PK_Color shadowColor);
    PK_tAABoundingSquare GetCollisionBox(unsigned int idx);

    void SetCurrentFrame(unsigned int uiFrame);
    unsigned long GetFrameCount();
    
    // Nome do resource do sprite
    inline void SetSpriteAssetName(const PK_String &sAssetName) { m_sSpriteAssetName = sAssetName; };
    inline PK_SpriteAsset * GetSpriteAsset() { return m_pSpriteAsset; }
    inline unsigned int GetCurrentFrame() { return m_uiCurrentFrame; }
    inline unsigned int GetFps() { return m_uiFps; }
    inline void SetFps(unsigned int uiFps) { m_uiFps = uiFps; }
	inline bool GetWithAnimation() { return m_bAnimationActive; }
	inline void SetWithAnimation(bool bWithAnimation) { m_bAnimationActive = bWithAnimation; }
};

}

#endif
