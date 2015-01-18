#ifndef _RENDERMANAGER_H_
#define _RENDERMANAGER_H_

#include <glm/glm.hpp>
#include "PK_Consts.h"
#include "PK_Component.h"
#include "PK_List.h"
#include "PK_tBoundingSquare.h"
#include "PK_tAABoundingSquare.h"
#include "PK_Shader.h"
#include "PK_Camera.h"
#include "PK_Types.h"
#include "PK_Exceptions.h"

namespace PK {

class PK_SpriteAsset;
class PK_TextureAsset;
class PK_FontAsset;
struct PK_tPrimitiveData;

class PK_RenderManager : public PK_Component
{
protected:
    PK_Color             m_ClearColor;
    PK_List<PK_Shader *> m_Shaders;
    bool                 m_bShadersInitialized;
    PK_Shader          * m_pCurrentShader;
    PK_Camera          * m_pCurrentCamera;
    PK_Camera          * m_pDefaultCamera;
    bool                 m_bInitialized;
    
    PK_tSize             m_ViewportSize; // Viewport (resolucao real do device)
    PK_tAABoundingSquare m_SafeFrame;    // A parte do RenderSize que esta visivel no viewport
    PK_tSize             m_WindowSize;   // FIXME. remover e substituir por m_Viewport porque �� a mesma coisa. Tamanho real do frame de renderer (client rect no windows, ecran num device)
    PK_tAABoundingSquare m_frame;    // Bouding square na escala do game resolution
    PK_tAABoundingSquare m_safeFame; // Zona visivel no ecran dentro de m_Frame
    PK_tAABoundingSquare m_Viewport; // Tamanho real do frame de renderer (client rect no windows, ecran num device)

public:
    PK_RenderManager(const PK_String &sName);
    ~PK_RenderManager();
    virtual void WaitForEnd() {}
    virtual void BeginRender() = 0;
    virtual void EndRender() = 0;
    virtual void OnCameraChanged(PK_Camera &previousCamera) { }

    virtual void RenderQuad(const PK_tBoundingSquare &bs, const PK_Color &color) = 0;
	virtual void RenderQuad(const PK_tPrimitiveData &primitiveData, const PK_Color &color, const PK_Matrix3 &matModel ) 
	{
		throw PK_NotImplementedException("PK_RenderManager::RenderQuad", __FILE__, __LINE__);
	}
	virtual void RenderImage(const PK_tPrimitiveData &primitiveData, const PK_TextureAsset &texture, const PK_Color &color, const PK_Matrix3 &matModel) 
	{
		throw PK_NotImplementedException("PK_RenderManager::RenderImage", __FILE__, __LINE__);
	}
    virtual void RenderImage(const PK_tBoundingSquare &bsDest, PK_TextureAsset *pTexture, const PK_Color &color) = 0;
    virtual void RenderImage(const PK_tTextureFrame &bsSource, const PK_tBoundingSquare &bsDest, const PK_TextureAsset &texture, const PK_Color &color) = 0;
	virtual void RenderSprite(PK_SpriteAsset &sprite, unsigned int uiFrameNr, const PK_Color &color, const PK_Matrix3 &matModel) { }

	virtual void RenderSprite(PK_SpriteAsset &sprite, const PK_tBoundingSquare &bs, unsigned int uiFrameNr, const PK_Color &color) = 0;
    virtual void RenderSprite(PK_SpriteAsset &sprite, const PK_Vector2 &vPosition, unsigned int uiFrameNr, const PK_Color &color, const PK_Vector2 &vPivot, float fRotation) = 0;
    virtual void RenderText(const PK_String &sText, PK_FontAsset &font, PK_Vector2 &vPosition, const PK_Color &color) = 0;
    virtual void RenderPolygon(PK_Vector2 *vertices, unsigned int uiNumVertices, const PK_Color &color) = 0;
    virtual void RenderSolidPolygon(PK_Vector2 *vertices, unsigned int uiNumVertices, const PK_Color &color) = 0;
    virtual void RenderCircle(PK_Vector2 &center, float fRadius, const PK_Color &color, unsigned int uiSegments) = 0;
    virtual void RenderSolidCircle(PK_Vector2 &center, float fRadius, const PK_Color &color, unsigned int uiSegments) = 0;
    virtual void RenderSegment(PK_Vector2 &v1, PK_Vector2 &v2, const PK_Color &color) = 0;
    virtual void RenderPoint(PK_Vector2 &v1, float fSize, const PK_Color &color) = 0;
 
    virtual PK_tPrimitiveData & CreateColorShaderPrimitiveData(PK_tBoundingSquare &bs) 
	{
		throw PK_NotImplementedException("PK_RenderManager::CreateColorShaderPrimitiveData", __FILE__, __LINE__);
	}
	 
	virtual PK_tPrimitiveData & CreateTextureShaderPrimitiveData(PK_tBoundingSquare &bs, PK_Vector2 texCoords[]) 
	{
		throw PK_NotImplementedException("PK_RenderManager::CreateTextureShaderPrimitiveData", __FILE__, __LINE__);
	}

	virtual void SetBlendMode(PK_eBlendMode blendMode) = 0;


    // Clear color
    inline PK_Color GetClearColor()  { return m_ClearColor;}
    inline void SetClearColor(const PK_Color &color) { m_ClearColor = color; }

    // Camera currente
    inline PK_Camera & GetCamera()  { return *m_pCurrentCamera;}
    inline PK_Camera & GetDefaultCamera() { return *m_pDefaultCamera; }
    void SetToDefaultCamera();
    virtual void SetCamera(PK_Camera &camera);
    
    // Screen size
    inline PK_tSize GetViewportSize() { return m_ViewportSize; }
    inline PK_tSize GetWindowSize() { return m_WindowSize; }

    inline PK_tAABoundingSquare & GetViewport() { return  m_Viewport; }
	inline PK_tAABoundingSquare & GetFrame() { return  m_frame; }
	inline PK_tAABoundingSquare & GetSafeFrame() { return  m_safeFame; }

    // Shaders
    void SetShader(PK_Shader *pShader);
    void AddShader(PK_Shader *pShader);
    void InitializeShaders();

    
    // Flag de inicializazcao
    inline bool IsInitialized() { return m_bInitialized; }
    
    PK_Vector2 GetViewportRendererProportion()
    {
        float fx = (float)m_frame.size.w / (float)m_ViewportSize.w;
        float fy = (float)m_frame.size.h / (float)m_ViewportSize.h;
        return PK_Vector2(fx, fy);
    }
};
} // namespace

#endif
