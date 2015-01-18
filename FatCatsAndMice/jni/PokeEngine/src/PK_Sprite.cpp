#include "PK_Globals.h"
#include "PK_Sprite.h"
#include "PK_Config.h"

namespace PK {

    
PK_Sprite::PK_Sprite(const PK_String &sName) :
    PK_2DSceneControl(sName)
{
    SetTypeName("PK_SceneSprite");
    m_pSpriteAsset = NULL;
    m_uiEllapsedTime = 0;
    m_bAnimationActive = true;
    m_uiCurrentFrame = 0;
    m_bWithShadow = false;
}

//
PK_Sprite::~PK_Sprite()
{
    FreeResources();
}

//
void PK_Sprite::FreeResources()
{
    SetSprite(NULL);
    PK_2DSceneControl::FreeResources();
}

//
void PK_Sprite::InitFromDataFileRecord(PK_DataFileRecord &record)
{
    PK_2DSceneControl::InitFromDataFileRecord(record);
}

// Carrega o sprite
void PK_Sprite::InternalLoad()
{ 
    if (m_sSpriteAssetName.length() > 0)
    {
        PK_String sContainerName = GetAssetContainerName();
        SetSprite(PokeEngine.GetAssetManager().LoadSprite(m_sSpriteAssetName, sContainerName));
    }
    PK_2DSceneControl::InternalLoad();
}
    
//
void PK_Sprite::InternalUpdate(const PK_GameTimer &time)
{
    if (!IsEnabled())
    {
        return;
    }

    if (m_pSpriteAsset != NULL && m_bAnimationActive)
    {
        unsigned int uiFrameTime = (m_pSpriteAsset->GetFramePtr(m_uiCurrentFrame)->m_uiPlayingTime == 0? (1000 / m_uiFps) : m_pSpriteAsset->GetFramePtr(m_uiCurrentFrame)->m_uiPlayingTime);
        m_uiEllapsedTime += time.GetEllapsedTime();
        while (m_uiEllapsedTime > uiFrameTime)
        {
            m_uiEllapsedTime -= uiFrameTime;
            m_uiCurrentFrame++;
            if (m_uiCurrentFrame >= m_pSpriteAsset->GetFrameCount())
            {
                m_uiCurrentFrame = 0;
                if (OnLastFrame.HasCallback())
                {
                    OnLastFrame->Execute(*this);
                }
            }
        }
    }
    PK_2DSceneControl::InternalUpdate(time);
}
    
//
void PK_Sprite::InternalAfterDrawBackground()
{
    if (m_pSpriteAsset != NULL) 
    {
        // PERFORMANCE: Isto pode ser melhorado, nao precisa de estar sempre a ser calculado
        PK_tBoundingSquare bsDest;
        bsDest = m_pSpriteAsset->GetFrame(m_uiCurrentFrame).m_bsFrame;
        PK_Matrix3 mat = *GetTransformMatrix();
        mat *= glm::translate(-GetPivot());
        bsDest.TransformInPlace(mat);
        if (m_bWithShadow)
        {
            PK_tBoundingSquare bsDestShadow = bsDest;
            bsDestShadow.TransformInPlace(m_vShadowDepth);
            PokeEngine.GetRenderManager().RenderSprite(*m_pSpriteAsset, bsDestShadow, m_uiCurrentFrame, m_ShadowColor);
        }
#ifdef PK_USEVERTEXBUFFERS
		PokeEngine.GetRenderManager().RenderSprite(*m_pSpriteAsset, m_uiCurrentFrame, GetColor(), mat);
#else
        PokeEngine.GetRenderManager().RenderSprite(*m_pSpriteAsset, bsDest, m_uiCurrentFrame, GetColor());
#endif
    }
    PK_2DSceneControl::InternalAfterDrawBackground();
}
    
//
void PK_Sprite::InternalUnload()
{
    SetSprite(NULL);
    PK_2DSceneControl::InternalUnload();
}


//
void PK_Sprite::Copy(PK_SceneControl &copyFrom)
{
    PK_2DSceneControl::Copy(copyFrom);
    PK_Sprite *pCopyFrom = (PK_Sprite *) &copyFrom;
    SetSprite(pCopyFrom->m_pSpriteAsset);
    m_uiEllapsedTime = pCopyFrom->m_uiEllapsedTime;
    m_bAnimationActive = pCopyFrom->m_bAnimationActive;
    m_uiCurrentFrame = pCopyFrom->m_uiCurrentFrame;
    SetFps(pCopyFrom->m_uiFps);
    SetShadow(pCopyFrom->m_bWithShadow, pCopyFrom->m_vShadowDepth, pCopyFrom->m_ShadowColor);
}

// 
void PK_Sprite::SetSprite(PK_SpriteAsset *pAsset)
{
    if (m_pSpriteAsset != NULL)
    {
        m_pSpriteAsset->Release();
        m_pSpriteAsset = NULL;
    }
    if (pAsset != NULL)
    {
        m_pSpriteAsset = pAsset;
        m_uiFps = m_pSpriteAsset->GetFps();
        m_pSpriteAsset->Grab();
        SetSize(m_pSpriteAsset->GetSize());
        SetPivot(m_pSpriteAsset->GetPivot());
    }
}

//
void PK_Sprite::SetShadow(bool bEnable, const PK_Vector2 vDepth, const PK_Color shadowColor)
{
    m_bWithShadow = bEnable;
    m_vShadowDepth = vDepth;
    m_ShadowColor = shadowColor;
}

//
PK_tAABoundingSquare PK_Sprite::GetCollisionBox(unsigned int idx)
{
    if (m_pSpriteAsset == NULL)
    {
        throw PK_SystemException("Cannot retrieve collision box with index '%d' becasue the Sprite Asset is not set or not loaded.", 
            __FILE__, __LINE__, idx);

    }

    return m_pSpriteAsset->GetCollisionBox(idx);
}

//
void PK_Sprite::SetCurrentFrame(unsigned int uiFrame)
{
    if (uiFrame > GetFrameCount())
    {
        throw PK_ArgumentOutOfRangeException("frame", __FILE__, __LINE__);
    }
    m_uiCurrentFrame = uiFrame;
}
 
//
unsigned long PK_Sprite::GetFrameCount()
{
    return (m_pSpriteAsset == NULL? 0 : m_pSpriteAsset->GetFrameCount());
}

} // namespace
