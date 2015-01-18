#define WINDOWS_MEAN_AND_LEAN
#include <Windows.h>
#include "PK_MathHelper.h"
#include <gl\GL.h>
#include "PK_GLRenderManager.h"
#include "PK_Globals.h"
#include "PK_Exceptions.h"
#include "PK_Log.h"
#include "PK_Color.h"
#include "PK_SpriteAsset.h"
#include "PK_TextureAsset.h"

namespace PK {

#define PK_GL_RENDER_MANAGER_NAME "__PK_glRenderManager__"

//
PK_GLRenderManager::PK_GLRenderManager(const PK_String &sName) :
    PK_SDLRenderManager(sName)
{
	SetTypeName("PK_GLRenderManager");
}

//
void PK_GLRenderManager::OnInitialize()
{
    PK_SDLRenderManager::OnInitialize();

    glMatrixMode(GL_PROJECTION);
    PK_Matrix4 g = GetCamera().GetProjectionMatrix();
    glLoadMatrixf(&g[0][0]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

//
void PK_GLRenderManager::BeginRender()
{
    glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

//
void PK_GLRenderManager::EndRender()
{
    if (m_pCurrentShader != NULL)
    {
        m_pCurrentShader->Commit();
    }
    SDL_GL_SwapWindow(m_pWindow);
}

//
void PK_GLRenderManager::OnCameraChanged(PK_Camera &previousCamera)
{
    glMatrixMode(GL_PROJECTION);
    PK_Matrix4 g = GetCamera().GetProjectionMatrix();
    glLoadMatrixf(&g[0][0]);
}
//
void PK_GLRenderManager::RenderQuad(const PK_tBoundingSquare &bs, const PK_Color &color)
{
    SetActiveTexture(NULL);
    glBegin(GL_QUADS);
    glColor4f(color.r, color.g, color.b, color.a); 
    glVertex2f(bs.m_Vertices[0].x, bs.m_Vertices[0].y);
    glVertex2f(bs.m_Vertices[1].x, bs.m_Vertices[1].y);
    glVertex2f(bs.m_Vertices[2].x, bs.m_Vertices[2].y);
    glVertex2f(bs.m_Vertices[3].x, bs.m_Vertices[3].y);
    glEnd();
}

//
void PK_GLRenderManager::RenderImage(const PK_tBoundingSquare &bsDest, PK_TextureAsset *pTexture, const PK_Color &color)
{
    assert(pTexture != NULL);
    PK_SDLTextureAsset *pSdlTExture = (PK_SDLTextureAsset *)pTexture;
    SetActiveTexture(pSdlTExture);

    glBegin(GL_QUADS);
    glColor4f(color.r, color.g, color.b, color.a); 
    glTexCoord2f(0,0); 
    glVertex2f(bsDest.m_Vertices[0].x, bsDest.m_Vertices[0].y);
    glTexCoord2f(0,1); 
    glVertex2f(bsDest.m_Vertices[1].x, bsDest.m_Vertices[1].y);
    glTexCoord2f(1,1); 
    glVertex2f(bsDest.m_Vertices[2].x, bsDest.m_Vertices[2].y);
    glTexCoord2f(1,0);
    glVertex2f(bsDest.m_Vertices[3].x, bsDest.m_Vertices[3].y);
    glEnd();
}

//
void PK_GLRenderManager::RenderImage(const PK_tTextureFrame &bsSource, const PK_tBoundingSquare &bsDest, const PK_TextureAsset &texture, const PK_Color &color)
{
    PK_SDLTextureAsset *pSdlTExture = (PK_SDLTextureAsset *)&texture;
    SetActiveTexture(pSdlTExture);
    
    glBegin(GL_QUADS);
    glColor4f(color.r, color.g, color.b, color.a); 
    glTexCoord2f(bsSource.textCoords[0].x, bsSource.textCoords[0].y); 
    glVertex2f(bsDest.m_Vertices[0].x, bsDest.m_Vertices[0].y);
    glTexCoord2f(bsSource.textCoords[1].x, bsSource.textCoords[1].y); 
    glVertex2f(bsDest.m_Vertices[1].x, bsDest.m_Vertices[1].y);
    glTexCoord2f(bsSource.textCoords[2].x, bsSource.textCoords[2].y); 
    glVertex2f(bsDest.m_Vertices[2].x, bsDest.m_Vertices[2].y);
    glTexCoord2f(bsSource.textCoords[3].x, bsSource.textCoords[3].y); 
    glVertex2f(bsDest.m_Vertices[3].x, bsDest.m_Vertices[3].y);
    glEnd();
}

//
void PK_GLRenderManager::RenderSprite(PK_SpriteAsset &sprite, const PK_tBoundingSquare &bs, unsigned int uiFrameNr, const PK_Color &color)
{
    PK_SDLTextureAsset *pSdlTExture = (PK_SDLTextureAsset *)sprite.GetTexture();
    PK_tSpriteFrame *pFrame = sprite.GetFramePtr(uiFrameNr);
    SetActiveTexture(pSdlTExture);
    glBegin(GL_QUADS);
    glColor4f(color.r, color.g, color.b, color.a); 
    glTexCoord2f(pFrame->m_vTexCoords[0].x, pFrame->m_vTexCoords[0].y); 
    glVertex2f(bs.m_Vertices[0].x, bs.m_Vertices[0].y);
    glTexCoord2f(pFrame->m_vTexCoords[1].x, pFrame->m_vTexCoords[1].y); 
    glVertex2f(bs.m_Vertices[1].x, bs.m_Vertices[1].y);
    glTexCoord2f(pFrame->m_vTexCoords[2].x, pFrame->m_vTexCoords[2].y); 
    glVertex2f(bs.m_Vertices[2].x, bs.m_Vertices[2].y);
    glTexCoord2f(pFrame->m_vTexCoords[3].x, pFrame->m_vTexCoords[3].y);
    glVertex2f(bs.m_Vertices[3].x, bs.m_Vertices[3].y);
    glEnd();
}

//
void PK_GLRenderManager::RenderSprite(PK_SpriteAsset &sprite, const PK_Vector2 &vPosition, unsigned int uiFrameNr, const PK_Color &color, const PK_Vector2 &vPivot, float fRotation)
{
    PK_Matrix3 matTransform;
    matTransform = PK_Matrix3(1.0f);
    if (vPivot.x != 0 || vPivot.y != 0)
    {
        matTransform = glm::translate(vPivot);
    }
    
    if (fRotation != 0)
    {
      matTransform *= glm::translate(vPosition + vPivot) * glm::rotate(fRotation);
    }
    else
    {
      matTransform *= glm::translate(vPosition + vPivot);
    }
    PK_tBoundingSquare bsDest;
    bsDest = sprite.GetFrame(uiFrameNr).m_bsFrame;
    bsDest.TransformInPlace(matTransform);
    PokeEngine.GetRenderManager().RenderSprite(sprite, bsDest, uiFrameNr, color);
}

//
void PK_GLRenderManager::RenderText(const PK_String &sText, PK_FontAsset &font, PK_Vector2 &vPosition, const PK_Color &color)
{
}

//
void PK_GLRenderManager::RenderPolygon(PK_Vector2 *vertices, unsigned int uiNumVertices, const PK_Color &color)
{
    SetActiveTexture(NULL);
    glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < uiNumVertices; ++i)
	{
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();
}

//
void PK_GLRenderManager::RenderSolidPolygon(PK_Vector2 *vertices, unsigned int uiNumVertices, const PK_Color &color)
{
    SetActiveTexture(NULL);
    glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_TRIANGLE_FAN);
	for (unsigned int i = 0; i < uiNumVertices; ++i)
	{
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();
	
}

//
void PK_GLRenderManager::RenderCircle(PK_Vector2 &center, float fRadius, const PK_Color &color, unsigned int uiSegments)
{

 }

//
void PK_GLRenderManager::RenderSolidCircle(PK_Vector2 &center, float fRadius, const PK_Color &color, unsigned int uiSegments)
{
    SetActiveTexture(NULL);
	const float k_increment = (const float)(2.0f * PK_MATH_PI / uiSegments);
	float theta = 0.0f;
     
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_TRIANGLE_FAN);
	for (unsigned int i = 0; i < uiSegments; ++i)
	{
		PK_Vector2 v = center + fRadius * PK_Vector2(cosf(theta), sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();
}

//
void PK_GLRenderManager::RenderSegment(PK_Vector2 &v1, PK_Vector2 &v2, const PK_Color &color)
{
}

//
void PK_GLRenderManager::RenderPoint(PK_Vector2 &v1, float fSize, const PK_Color &color)
{
}

//
void PK_GLRenderManager::gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
   GLdouble xmin, xmax, ymin, ymax;

   ymax = zNear * tan(fovy * M_PI / 360.0);
   ymin = -ymax;
   xmin = ymin * aspect;
   xmax = ymax * aspect;


   glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}

//
void PK_GLRenderManager::SetActiveTexture(PK_SDLTextureAsset *pTexture)
{
   // FIXME
   // Comentado porque o SDL muda isto algures
   // isto causa problemas quando esta a ler texturas e a mostrar um screen transition ou o loading icon
   // if (m_pCurrentTexture != pTexture)

    // Nao sei bem se este if faz alguma coisa...
 /*   GLint curTextId;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &curTextId);
    if (curTextId != pTexture->GetGlTextureId())
    {*/

    if (pTexture == NULL)
    {
        glDisable(GL_TEXTURE_2D);
        m_pCurrentTexture = pTexture;
        return;
    }
    if (m_pCurrentTexture == NULL)
    {
        glEnable(GL_TEXTURE_2D);
    }
 
    glBindTexture(GL_TEXTURE_2D, pTexture->GetGlTextureId());
    m_pCurrentTexture = pTexture;

}

//
void PK_GLRenderManager::SetBlendMode(PK_eBlendMode blendMode)
{
    if (m_pCurrentShader != NULL)
    {
        m_pCurrentShader->Commit();
    }
    m_currentBlendMode = blendMode;
    if (m_currentBlendMode == BlendMode_AlphaTransparency)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        return;
    }

    if (m_currentBlendMode == BlendMode_None)
    {
        glDisable(GL_BLEND);
    }
}

//
void PK_GLRenderManager::SetupViewport()
{
    PK_SDLRenderManager::SetupViewport();
    PK_tAABoundingSquare viewport = GetViewport();
    glViewport((GLint)viewport.vPosition.x, (GLint)viewport.vPosition.y, (GLsizei)viewport.size.w, (GLsizei)viewport.size.h);
}

} // namespace
