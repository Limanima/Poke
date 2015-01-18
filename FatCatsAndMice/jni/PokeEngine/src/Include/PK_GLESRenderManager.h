#ifndef _PK_GLESRenderManager_H_
#define _PK_GLESRenderManager_H_

#include <SDL.h>
#include "PK_Consts.h"
#include "PK_SDLRenderManager.h"
#include "PK_GLESBasicShader.h"
#include "PK_GLESTextureShader.h"
#include "PK_FontAsset.h"

namespace PK {

class PK_GLESRenderManager : public PK_SDLRenderManager
{
private:
    PK_GLESBasicShader    *m_pBasicShader;
    PK_GLESTextureShader  *m_pTextureShader;
    
public:
    PK_GLESRenderManager(const PK_String &sName);
    ~PK_GLESRenderManager();
    void OnUnload();
    void BeginRender();
    void EndRender();
    void WaitForEnd();
    void OnCameraChanged(PK_Camera &previousCamera);
    
    // Metodos de render
    void RenderQuad(const PK_tBoundingSquare &bs, const PK_Color &color);
    void RenderImage(const PK_tBoundingSquare &bsDest, PK_TextureAsset *pTexture, const PK_Color &color);
    void RenderImage(const PK_tTextureFrame &bsSource, const PK_tBoundingSquare &bsDest, const PK_TextureAsset &texture, const PK_Color &color);
    void RenderSprite(PK_SpriteAsset &sprite, const PK_tBoundingSquare &bs, unsigned int iFrameNr, const PK_Color &color);
    void RenderSprite(PK_SpriteAsset &sprite, const PK_Vector2 &vPosition, unsigned int uiFrameNr, const PK_Color &color, const PK_Vector2 &vPivot, float fRotation);
    void RenderText(const PK_String &sText, PK_FontAsset &font, PK_Vector2 &vPosition, const PK_Color &color);
    void RenderPolygon(PK_Vector2 *vertices, unsigned int uiNumVertices, const PK_Color &color);
    void RenderSolidPolygon(PK_Vector2 *vertices, unsigned int uiNumVertices, const PK_Color &color);
    void RenderCircle(PK_Vector2 &center, float fRadius, const PK_Color &color, unsigned int uiSegments);
    void RenderSolidCircle(PK_Vector2 &center, float fRadius, const PK_Color &color, unsigned int uiSegments);
    void RenderSegment(PK_Vector2 &v1, PK_Vector2 &v2, const PK_Color &color);
    void RenderPoint(PK_Vector2 &v1, float fSize, const PK_Color &color);

    void SetActiveTexture(PK_SDLTextureAsset &texture);
    void SetActiveShader(PK_GLESShader &shader);
    void SetBlendMode(PK_eBlendMode blendMode);
    void SetupViewport();

	static PK_GLESRenderManager * GetSDLRenderManager();
private:
    void CreateInternalShaders();
};

}
#endif
