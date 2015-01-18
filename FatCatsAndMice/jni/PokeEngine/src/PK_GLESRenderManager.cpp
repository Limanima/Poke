#include <SDL_Image.h>
#include <SDL.h>
#include <assert.h>
#include "PK_Globals.h"
#include "PK_Exceptions.h"
#include "PK_GLESRenderManager.h"
#include "PK_SDLTextureAsset.h"
#include "PK_Log.h"
#include "PK_GLESBasicShader.h"
#include "PK_GLESShader.h"
#include "PK_Color.h"
#include "PK_OpenGL.h"
#include "PK_Vector2.h"
#include "PK_MathHelper.h"
#include "PK_SpriteAsset.h"

namespace PK {

//-----------------------------------------------------
PK_GLESRenderManager::PK_GLESRenderManager(const PK_String &sName) :
    PK_SDLRenderManager(sName)
{
	SetTypeName("PK_GLESRenderManager");

    m_pBasicShader = NULL;
    m_pTextureShader = NULL;
 
    SetBlendMode(BlendMode_None);
}
    
//
PK_GLESRenderManager::~PK_GLESRenderManager()
{
    OnUnload();
}

//
void PK_GLESRenderManager::OnUnload()
{
    PK_FREE(m_pBasicShader);
    PK_FREE(m_pTextureShader);

    PK_RenderManager::OnUnload();
}

//
void PK_GLESRenderManager::BeginRender()
{
    glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}


//
void PK_GLESRenderManager::EndRender()
{
    if (m_pCurrentShader != NULL)
    {
        m_pCurrentShader->Commit();
    }
    SDL_GL_SwapWindow(m_pWindow);
}
    
//
void PK_GLESRenderManager::WaitForEnd()
{
    glFinish();
}
    
//
void PK_GLESRenderManager::OnCameraChanged(PK_Camera &previousCamera)
{
	PK_SDLRenderManager::OnCameraChanged(previousCamera);
	if (m_pCurrentShader != NULL)
	{
		m_pCurrentShader->Commit(previousCamera);
	}
}

// Cria e adiciona os shaders internos usados pelo engine
void PK_GLESRenderManager::CreateInternalShaders()
{
    // Shader basico
    m_pBasicShader = new PK_GLESBasicShader(*this);
    PK_CHECK_OBJECT_ALLOC(PK_GLESBasicShader, m_pBasicShader);
    m_pBasicShader->Grab();
    AddShader(m_pBasicShader);
    
    // Shader para texturas
    m_pTextureShader = new PK_GLESTextureShader(*this);
    PK_CHECK_OBJECT_ALLOC(PK_GLESTextureShader, m_pTextureShader);
    m_pTextureShader->Grab();
    AddShader(m_pTextureShader);
}


// Static
PK_GLESRenderManager * PK_GLESRenderManager::GetSDLRenderManager()
{
	return (PK_GLESRenderManager *)&PokeEngine.GetRenderManager();
}
     

// Desenha uma BB          
void PK_GLESRenderManager::RenderQuad(const PK_tBoundingSquare &bs, const PK_Color &color)
{
    static unsigned short faceIndexes[6] = {0, 1, 2, 2, 3, 0 };

    if (m_pCurrentShader != m_pBasicShader)
    {
        SetActiveShader(*m_pBasicShader);
    } 
     
    if (m_currentBlendMode != BlendMode_None)
    { 
        SetBlendMode(BlendMode_None);
    }
   
    m_pBasicShader->Execute((PK_Vector2 *)bs.m_Vertices, 4, faceIndexes, 2, color);
}

// Desenha uma imagem
// FIXME: mudar *pTexture para &texture
void PK_GLESRenderManager::RenderImage(const PK_tBoundingSquare &bs, PK_TextureAsset *pTexture, const PK_Color &color)
{
    assert(pTexture != NULL);
    
    static PK_Vector2 texCoords[] = {
        PK_Vector2(0.0, 1.0),
        PK_Vector2(0.0, 0.0),
        PK_Vector2(1.0, 0.0),
        PK_Vector2(1.0, 1.0)
    };
    
    static unsigned char faceIndexes[6] = {0, 1, 2, 2, 3, 0 };
    if (m_pCurrentShader != m_pTextureShader)
    {
        SetActiveShader(*m_pTextureShader);
    }

    if (m_currentBlendMode != BlendMode_AlphaTransparency)
    {
        SetBlendMode(BlendMode_AlphaTransparency);
    }

    m_pTextureShader->Execute(bs.m_Vertices, 4, faceIndexes, 2, texCoords, color, *((PK_SDLTextureAsset *) pTexture));
}

//
void PK_GLESRenderManager::RenderImage(const PK_tTextureFrame &bsSource, const PK_tBoundingSquare &bsDest, const PK_TextureAsset &texture, const PK_Color &color)
{
    static unsigned char faceIndexes[6] = {0, 1, 2, 2, 3, 0 };

    if (m_pCurrentShader != m_pTextureShader)
    {
        SetActiveShader(*m_pTextureShader);
    }

    if (m_currentBlendMode != BlendMode_AlphaTransparency)
    {
        SetBlendMode(BlendMode_AlphaTransparency);
    }

    m_pTextureShader->Execute((PK_Vector2 *) bsDest.m_Vertices, 4, faceIndexes, 2, (PK_Vector2*)bsSource.textCoords, color, *((PK_SDLTextureAsset *)&texture));
}
    
//
void PK_GLESRenderManager::RenderSprite(PK_SpriteAsset &sprite, const PK_tBoundingSquare &bs, unsigned int uiFrameNr, const PK_Color &color) 
{
    static unsigned char faceIndexes[6] = {0, 1, 2, 2, 3, 0 };
    
    if (m_pCurrentShader != m_pTextureShader)
    {
        SetActiveShader(*m_pTextureShader);
    }
    
    if (m_currentBlendMode != BlendMode_AlphaTransparency)
    {
        SetBlendMode(BlendMode_AlphaTransparency);
    }

    PK_tSpriteFrame *pFrame = sprite.GetFramePtr(uiFrameNr);
    m_pTextureShader->Execute((PK_Vector2 *) bs.m_Vertices, 4, faceIndexes, 2, pFrame->m_vTexCoords, color, *((PK_SDLTextureAsset *) sprite.GetTexture()));
}

//
void PK_GLESRenderManager::RenderSprite(PK_SpriteAsset &sprite, const PK_Vector2 &vPosition, unsigned int uiFrameNr, const PK_Color &color, const PK_Vector2 &vPivot, float fRotation)
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
    RenderSprite(sprite, bsDest, uiFrameNr, color);
}
//
void PK_GLESRenderManager::RenderText(const PK_String &sText, PK_FontAsset &font, PK_Vector2 &vPosition, const PK_Color &color)
{
    if (m_pCurrentShader != m_pTextureShader)
    {
        SetActiveShader(*m_pTextureShader);
    }
    
    if (m_currentBlendMode != BlendMode_AlphaTransparency)
    {
        SetBlendMode(BlendMode_AlphaTransparency);
    }
    
    PK_tBoundingSquare bsDest;
    for(int i= 0; (i < (int)sText.length()); i++)
    {
        PK_tFontChar *pChar = font.GetChar(sText[i]);
        bsDest.Set(vPosition.x, vPosition.y, pChar->size.w, pChar->size.h);
        PokeEngine.GetRenderManager().RenderImage(pChar->frame, bsDest, *font.GetTexture(), color);
        vPosition.x += pChar->size.w + pChar->iSpacing;
    }       
}


//
void PK_GLESRenderManager::RenderPolygon(PK_Vector2 *vertices, unsigned int uiNumVertices, const PK_Color &color)
{
}

//
void PK_GLESRenderManager::RenderSolidPolygon(PK_Vector2 *vertices, unsigned int uiNumVertices, const PK_Color &color)
{
}

//
void PK_GLESRenderManager::RenderCircle(PK_Vector2 &center, float fRadius, const PK_Color &color, unsigned int uiSegments)
{
}

//
void PK_GLESRenderManager::RenderSolidCircle(PK_Vector2 &center, float fRadius, const PK_Color &color, unsigned int uiSegments)
{
}

//
void PK_GLESRenderManager::RenderSegment(PK_Vector2 &v1, PK_Vector2 &v2, const PK_Color &color)
{
}

//
void PK_GLESRenderManager::RenderPoint(PK_Vector2 &v1, float fSize, const PK_Color &color)
{
}


//
void PK_GLESRenderManager::SetActiveShader(PK_GLESShader &shader)
{
    if (m_pCurrentShader != NULL)
    {
        m_pCurrentShader->Commit();
    }

    shader.Activate();
    m_pCurrentShader = &shader;
}

//
void PK_GLESRenderManager::SetActiveTexture(PK_SDLTextureAsset &texture)
{
  //  if (m_pCurrentTexture != &texture)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.GetGlTextureId());
        m_pCurrentTexture = &texture;
    }
}

//
void PK_GLESRenderManager::SetBlendMode(PK_eBlendMode blendMode)
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
void PK_GLESRenderManager::SetupViewport()
{
    PK_SDLRenderManager::SetupViewport();
    PK_tAABoundingSquare viewport = GetViewport();
    glViewport((GLint)viewport.vPosition.x, (GLint)viewport.vPosition.y, viewport.size.w, viewport.size.h);
}

} // namespace
