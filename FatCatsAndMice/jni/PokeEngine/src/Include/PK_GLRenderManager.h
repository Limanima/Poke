#ifndef _PK_GLRenderManager_H_
#define _PK_GLRenderManager_H_

#include "PK_SDLRenderManager.h"
#include "PK_Opengl.h"

namespace PK {

class PK_GLRenderManager : public PK_SDLRenderManager
{
private:


public:
    PK_GLRenderManager(const PK_String &sName);
    void OnInitialize();
    void BeginRender();
    void EndRender();
    void OnCameraChanged(PK_Camera &previousCamera);
    void RenderQuad(const PK_tBoundingSquare &bs, const PK_Color &color);
    void RenderImage(const PK_tPrimitiveData &primitiveData, PK_TextureAsset *pTexture, const PK_Color &color){}
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

    void SetBlendMode(PK_eBlendMode blendMode);
    void SetupViewport();
private:
    void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
    void SetActiveTexture(PK_SDLTextureAsset *pTexture);
};

}
#endif
