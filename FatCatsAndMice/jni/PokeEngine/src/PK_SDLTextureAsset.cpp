#include "PK_Globals.h"
#include "PK_SDLTextureAsset.h"	
#include "PK_Exceptions.h"
#include "PK_Types.h"
#include "PK_Path.h"
#include "PK_MemoryBuffer.h"
#include "PK_Log.h"
#include "PK_Thread.h"
#include "PK_SceneManager.h"
#include <SDL.h>
#include <SDL_Image.h>
#include <assert.h>
#include "PK_OpenGL.h"

namespace PK {
    
PK_SDLTextureAsset::PK_SDLTextureAsset(PK_AssetContainer &assetContainer):
    PK_TextureAsset(assetContainer)
{
	SetTypeName("PK_SDLTextureAsset");
    m_iglTexture = 0;
    m_chBytesPerPixel = 0;
}

PK_SDLTextureAsset::~PK_SDLTextureAsset()
{
    FreeResources();
}
    
//
void PK_SDLTextureAsset::FreeResources()
{
    if (m_iglTexture != 0)
    {
	#if defined(POKE_GL)
        glDeleteTextures(1, &m_iglTexture);
        m_iglTexture = 0;  
    #endif
    }
    m_bLoaded = false;
}

//
void PK_SDLTextureAsset::Load()
{
    if (m_bLoaded)
    {
        throw PK_SystemException("Texture asset named '%s' is already loaded.", __FILE__, __LINE__, GetName().c_str());
    }
    
    // Carregar a imagem
    PK_String sImageFile = GetAssetName();
    if (PK_Path::ContainsExtension(sImageFile) == false)
    {
        sImageFile = PK_Path::CombineExtension(sImageFile, PK_IMAGE_TYPE1_EXTENSION);
    }
     
	SDL_Surface * pSurface = IMG_Load(sImageFile.c_str());
    if (pSurface == NULL)
    {
	    throw PK_SDLException(__FILE__, __LINE__);
    }
     
    // Verificar se width e height sao powers de 2
    if ( (pSurface->w & (pSurface->w - 1)) != 0 ||
         (pSurface->h & (pSurface->h - 1)) != 0 )
    {
        SDL_FreeSurface(pSurface);
        throw PK_SystemException("Poke Engine only supports power of 2 textures.", __FILE__, __LINE__);
    }
    
    // Validar formato, para ja aceita-se so RGBA 32 bits
    if (pSurface->format->BytesPerPixel != 4)
    {
        SDL_FreeSurface(pSurface);
        throw PK_SystemException("Poke Engine only supports 32 bits images in RGBA format.", __FILE__, __LINE__);
    }
    
    m_Size.Set(pSurface->w, pSurface->h);
    m_chBytesPerPixel = pSurface->format->BytesPerPixel;

#if defined(POKE_GL) || defined(POKE_GLES)
    // Gerar um handle para a textura
    glGenTextures( 1, &m_iglTexture);
    assert(glGetError() == GL_NO_ERROR);

    // Fazer bind (diz ao GLES que vamos usar esta textura)
    glBindTexture( GL_TEXTURE_2D, m_iglTexture );
    assert(glGetError() == GL_NO_ERROR);
    
    // Set the texture's stretching properties
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    assert(glGetError() == GL_NO_ERROR);
    
    // FIXME: Nao esta a ter em conta o formato da imagem, para ja assume 32 bits RGBA
    // FIXME: Existe um glCompressedImage2D, ver como se pode utilizar
#ifdef POKE_IOS
    GLenum format = GL_BGRA; // No iOS o formato e diferente e este define nem existe no Android
#else
    GLenum format = GL_RGBA;
#endif
    
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, (int)m_Size.w, (int)m_Size.h, 0, format, GL_UNSIGNED_BYTE, pSurface->pixels);
    assert(glGetError() == GL_NO_ERROR);

    if (glGetError() != GL_NO_ERROR)
    {
        throw PK_SystemException("OpenGL error!", __FILE__, __LINE__);
    }
#endif
	BindTexture(*pSurface);
    SDL_FreeSurface(pSurface);
    
    m_bLoaded = true;
 }


} // namespace
