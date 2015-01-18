#ifndef _PK_2DSCENECONTROL_H_
#define _PK_2DSCENECONTROL_H_

#include "PK_SceneControl.h"
#include "PK_Vector2.h"
#include "PK_Matrix4.h"
#include "PK_BodyCollisionCallback.h"
#include "PK_Callback.h"
#include "PK_MathHelper.h"

namespace PK {

class PK_SpriteAsset;
class PK_Body;
class PK_PhysicsManager;
struct PK_tPrimitiveData;

class PK_2DSceneControl : public PK_SceneControl
{
private:
    PK_2DSceneControl *m_p2DParent;
    PK_tSize           m_Size;
    
    // Relativo ao pai
    PK_Vector2         m_vPosition;
    float              m_fRotation; // Em graus
    PK_Vector2         m_vScale;
    // Relativo a scene
    PK_Vector2         m_vWorldPosition;
    float              m_fWorldRotation; // Em graus
    PK_Vector2         m_vWorldScale;
    
    PK_tBoundingSquare m_bsClientRect;  // Client rect transformado
    PK_Color           m_Color;
    PK_Color           m_BlendedColor;  // A cor misturada com o parent
    PK_Color           m_BackgroundColor;
    PK_Matrix3         m_matTransform;  // Matrix de transformacao do objecto (utiliza a world position, scale e rotation
    unsigned int       m_uiRefreshFlags;
    unsigned int       m_uiChildRefreshFlags;
    PK_Vector2         m_vPivot; // Centro do objecto
    unsigned int       m_uiPivotAligment; 
    unsigned int       m_uiDockStyle;
    PK_tSize           m_SizeBeforeDock;
    unsigned int       m_uiParentAlignment;
    PK_tMargins        m_Padding; // Margem utilizado no padding

    // Suporte para imagem de background
    PK_SpriteAsset     *m_pBackgroundSprite;
    PK_String           m_sBackgroundSpriteAssetName;
    PK_eImageSizeMode   m_BackgroundImageFitMode;
    PK_tBoundingSquare  m_bsBackgroundImage;
	PK_tPrimitiveData  *m_pClientRectRenderData;

    // Suporte para fisica
    PK_Body            *m_pAttachedBody;
    bool                m_bWithPhysics;
    PK_tBodyDefinition  m_BodyDefinition;
    bool                m_bSuppressBodyTransformUpdates; // Se true, setar a posicao, scale ou rotacao no objecto nao vai fazer update no body

  public:
    PK_Callback<PK_IBodyCollisionCallback> OnBodyCollision;

  public:
    PK_2DSceneControl(const PK_String &sName = "");
    ~PK_2DSceneControl();
    void InitFromDataFileRecord(PK_DataFileRecord &record);
    virtual void InternalLoad();
    virtual void InternalUnload();
    virtual void InternalUpdate(const PK_GameTimer &time);
    virtual void InternalDraw();
    virtual void InternalAfterDrawBackground() {};
    void InternalAddedToScene();
    virtual void Copy(PK_SceneControl &copyFrom);

    void Move(const PK_Vector2 &vOffset);
    void Move(float x, float y);
    void Rotate(float fOffset);
    void Scale(const PK_Vector2 &vOffset);
    void Scale(float x, float y);
    void UpdateLayout();
    void UpdatePosition();
    void UpdateTransformMatrix();
    void UpdateClientRect();
	void UpdateClientRectPrimitiveData();
    void UpdateWorldPosition();
    void UpdateWorldRotation();
    void UpdateWorldScale();
    void UpdateBackgroundImage();
    void UpdateBackgroundImageRect();
    void UpdatePivot();
    void UpdateBlendedColor();
    void UpdateSize();
    void UpdatePhysicsBody();
    void UpdateChildsDock();
    void AlignToParent();
    void DockToRect(const PK_tAABoundingSquare &bsRect, PK_tAABoundingSquare &retBs);
    void InvalidateChilds(unsigned int uiFlags);
    void SetParent(PK_SceneControl * pNewParent);
    void ApplyEffects();
    void RemoveControlImmediate(PK_SceneControl *pControl);

    // Suporte para fisica
    void AttachBody(PK_Body &body);
    PK_Body * CreateBody();
    void DettachFromBody();
    void SetWithPhysics(bool bWithPhysics, PK_eBodyType bodyType = BodyType_Dynamic);
    void ApplyForce(const PK_Vector2 &vForce);
    PK_PhysicsManager * GetPhysicsManager();
    void SetBodyDefinition(const PK_tBodyDefinition &definition);
    void SetBodyDefinition(PK_eBodyType bodyType, PK_eControlBodyShapeMode type);
    PK_tBodyDefinition  & GetBodyDefinition() { return m_BodyDefinition; }
    inline bool WithPhysics() { return m_bWithPhysics; }
    inline bool HasBody() { return (m_pAttachedBody != NULL); }
    inline PK_Body * GetBody() { return m_pAttachedBody; }
   
    // Suporte para imagem de background
    void SetBackgroundImage(PK_SpriteAsset *pSprite);
    void SetBackgroundImage(const PK_String &sAssetName);
    inline void SetBackgroundImageFitMode(PK_eImageSizeMode mode)
    {
        m_BackgroundImageFitMode = mode;
        m_uiRefreshFlags |= RefreshFlags_BackgroundImageRect;
    }
    inline PK_eImageSizeMode GetBackgroundFitMode() { return m_BackgroundImageFitMode; }
    PK_tBoundingSquare * GetBackgroundImageRect();
    
    inline void Invalidate(unsigned int uiFlags) { m_uiRefreshFlags |= uiFlags; }
    inline void Invalidate()
    {
        m_uiRefreshFlags = RefreshFlags_All;
        InvalidateDock();
        InvalidateChilds(RefreshFlags_All);
    }
    
    // Position
    inline PK_Vector2 GetPosition() 
    { 
        if (m_uiRefreshFlags & RefreshFlags_Position)
        {
            UpdatePosition();
        }        
        return m_vPosition; 
    }
    inline void SetPosition(const PK_Vector2 &vPosition) 
    { 
        SetPosition(vPosition.x, vPosition.y);
    }
    inline void SetPosition(float x, float y)
    {
        if (m_vPosition.x != x || m_vPosition.y != y)
        {
            m_vPosition = PK_Vector2(x, y);
            m_uiRefreshFlags |= RefreshFlags_WorldPosition | RefreshFlags_ClientRect | RefreshFlags_TransformMatrix;
        }
    }

    // ClienRect
    inline PK_tBoundingSquare GetClientRect() 
    { 
        if (m_uiRefreshFlags & RefreshFlags_ClientRect)
        {
            UpdateClientRect();
        }        
        return m_bsClientRect; 
    }

    // Left, top, bottom, right
    inline float GetBottom() 
    {
        return (GetClientRect().GetMinY());
    }

    // Left, top, bottom, right
    inline float GetTop() 
    {
        //return (GetPosition().y + (GetSize().h  / 2) + GetPivot().y);
        return (GetClientRect().GetMaxY());
    }

    // Size
    inline PK_tSize GetSize() 
    { 
        if (m_uiRefreshFlags & RefreshFlags_Size)
        {
            UpdateSize();
        }
        return m_Size; 
    }
    inline void SetSize(const PK_tSize &size)
    {
        SetSize(size.w, size.h);
    }
    void SetSize(float w, float h);
    inline void SetWidth(float w) { SetSize(w, GetSize().h); }
    inline float GetWidth() { return GetSize().h; }
    inline void SetHeight(float h) { SetSize(GetSize().w, h); }
    inline float GetHeight() { return GetSize().w; }
 

    // Rotation
    inline float GetRotation() { return m_fRotation; }
    inline void SetRotation(float fRotation)
    { 

      if (m_fRotation != fRotation)
      {
        if (fRotation > 180 || fRotation < -180)
        {
            fRotation = PK_MathHelper::NormalizeAngle(fRotation);
        }
        m_fRotation = fRotation;
        m_uiRefreshFlags |= RefreshFlags_WorldRotation;
        m_uiChildRefreshFlags |= RefreshFlags_WorldRotation;
      }
    }
    
    // Scale
    inline PK_Vector2 GetScale() { return m_vScale; }
    inline void SetScale(float fScale) 
    { 
        SetScale(PK_Vector2(fScale, fScale));
    }
    inline void SetScale(float fx, float fy)
    {
        SetScale(PK_Vector2(fx, fy));
    }
    inline void SetScale(const PK_Vector2 &vScale)
    { 
      if (m_vScale != vScale)
      {
        m_vScale = vScale;
        m_uiRefreshFlags |= RefreshFlags_WorldScale;
        m_uiChildRefreshFlags |= RefreshFlags_WorldScale;
      }
    }
    
    // World position
    inline PK_Vector2 GetWorldPosition() 
    { 
        if (m_uiRefreshFlags & RefreshFlags_WorldPosition)
        {
            UpdateWorldPosition();
        }
        return m_vWorldPosition; 
    }
    inline void SetWorldPosition(const PK_Vector2 &vPosition)
    {
        SetWorldPosition(vPosition.x, vPosition.y);
    }
    void SetWorldPosition(float x, float y);
    
    // World rotation
    inline float GetWorldRotation() 
    { 
        if (m_uiRefreshFlags & RefreshFlags_WorldRotation)
        {
            UpdateWorldRotation();
        }
        return m_fWorldRotation; 
    }
    inline void SetWorldRotation(float fRotation)
    {
        if (fRotation != m_fWorldRotation)
        {
            m_fWorldRotation = fRotation;
            m_uiRefreshFlags |= RefreshFlags_TransformMatrix;
        }
    }

    // World scale
    inline PK_Vector2 GetWorldScale() 
    { 
        if (m_uiRefreshFlags & RefreshFlags_WorldScale)
        {
            UpdateWorldScale();
        }
        return m_vWorldScale; 
    }
    inline void SetWorldScale(const PK_Vector2 &vScale)
    {
        if (m_vWorldScale != vScale)
        {
            m_vWorldScale = vScale;
            m_uiRefreshFlags |= RefreshFlags_TransformMatrix;
        }
    } 
    
    // Blended color (cor misturada com o pai)
    inline PK_Color GetBlendedColor()
    {
        if (m_uiRefreshFlags & RefreshFlags_BlendedColor)
        {
            UpdateBlendedColor();
        }
        return m_BlendedColor;
    }
    inline PK_Color GetColor()
    {
        return m_Color;
    }
    inline void SetColor(const PK_Color &color)
    {
        if (m_Color != color)
        {
            m_Color = color;
            m_uiRefreshFlags |= RefreshFlags_BlendedColor;
            m_uiChildRefreshFlags |= RefreshFlags_BlendedColor;
        }
    }

    // Background color
    inline PK_Color GetBackgroundColor()
    {
        return m_BackgroundColor;
    }
    inline void SetBackgroundColor(const PK_Color &color)
    {
		SetBackgroundColor(color.r, color.g, color.b, color.a);
    }
    inline void SetBackgroundColor(const float r,  const float g, const float b, const float a)
    {
		m_BackgroundColor = PK_Color(r, g, b, a);
		if (a != 0.0f && m_pClientRectRenderData != NULL)
		{
			m_uiRefreshFlags |= RefreshFlags_CliRectPrimitiveData;
		}  
    }
    // Pivot
    inline PK_Vector2 GetPivot() 
    { 
        if (m_uiRefreshFlags & RefreshFlags_Pivot)
        {
            UpdatePivot();
        }
        return m_vPivot; 
    }
    inline void SetPivot(float x, float y)
    {
        SetPivot(PK_Vector2(x,y));
    }
    inline void SetPivot(const PK_Vector2 &vPivot) 
    { 
        if (m_vPivot != vPivot)
        {
            m_vPivot = vPivot; 
            m_uiRefreshFlags |= RefreshFlags_TransformMatrix | RefreshFlags_Position;
            m_uiChildRefreshFlags |= RefreshFlags_TransformMatrix | RefreshFlags_Position;
            InvalidateDock();
        }
    }

    // Pivot aligment
    inline unsigned int GetPivotAligment() { return m_uiPivotAligment; }
    inline void SetPivotAligment(unsigned int aligment) 
    { 
        if(m_uiPivotAligment != aligment)
        {
            m_uiPivotAligment = aligment; 
            m_uiRefreshFlags |= RefreshFlags_TransformMatrix | RefreshFlags_Pivot;
        }
    }

    // Dock style
    inline unsigned int GetDockStyle() { return m_uiDockStyle; }
    inline void SetDockStyle(unsigned int dockStyle) 
    { 
        if(m_uiDockStyle != dockStyle)
        {
            if (m_uiDockStyle == DockStyle_None)
            {
                m_SizeBeforeDock = GetSize();
            }
            m_uiDockStyle = dockStyle;
            InvalidateDock();
        }
    }
    
    // Padding
    inline PK_tMargins GetPadding() { return m_Padding; }
    inline void SetPadding(float padding)
    {
        SetPadding(PK_tMargins(padding, padding, padding, padding));
    }
    inline void SetPadding(float left, float top, float right, float bottom)
    {
        SetPadding(PK_tMargins(left, top, right, bottom));
    }
    inline void SetPadding(const PK_tMargins &padding)
    {
        if (m_Padding != padding)
        {
            m_Padding = padding;
            InvalidateChildDocks();
        }
    }
    
    // Parent aligment
    inline unsigned int GetParentAlignment() { return m_uiParentAlignment; }
    inline void SetParentAlignment(unsigned int aligment) 
    { 
        if (m_uiParentAlignment != aligment)
        {
            m_uiRefreshFlags |= RefreshFlags_Position;
            m_uiParentAlignment = aligment; 
        }
    }

    inline bool Is2DControl() { return true; }
    
    // Transform matrix
    PK_Matrix3 * GetTransformMatrix();
    
    inline void InvalidateChildDocks() { m_uiRefreshFlags |= RefreshFlags_ChildDocks; }
    void InvalidateDock();
    inline PK_2DSceneControl * Get2DParent() { return m_p2DParent; }

};

}
#endif
