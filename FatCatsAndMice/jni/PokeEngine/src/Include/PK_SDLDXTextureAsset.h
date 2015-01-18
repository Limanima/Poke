#ifndef _PK_SDLDXTEXTUREASSET_H_
#define _PK_SDLDXTEXTUREASSET_H_

#include "PK_SDLTextureAsset.h"
#include <d3d11_1.h>

// SDL Structures
struct SDL_SW_YUVTexture;

/* Define the SDL texture structure */
struct SDL_Texture
{
    const void *magic;
    Uint32 format;              /**< The pixel format of the texture */
    int access;                 /**< SDL_TextureAccess */
    int w;                      /**< The width of the texture */
    int h;                      /**< The height of the texture */
    int modMode;                /**< The texture modulation mode */
    SDL_BlendMode blendMode;    /**< The texture blend mode */
    Uint8 r, g, b, a;           /**< Texture modulation values */

    SDL_Renderer *renderer;

    /* Support for formats not supported directly by the renderer */
    SDL_Texture *native;
    SDL_SW_YUVTexture *yuv;
    void *pixels;
    int pitch;
    SDL_Rect locked_rect;

    void *driverdata;           /**< Driver specific texture representation */

    SDL_Texture *prev;
    SDL_Texture *next;
};

/* Per-texture data */
typedef struct
{
    ID3D11Texture2D *mainTexture;
    ID3D11ShaderResourceView *mainTextureResourceView;
    ID3D11RenderTargetView *mainTextureRenderTargetView;
    ID3D11Texture2D *stagingTexture;
    int lockedTexturePositionX;
    int lockedTexturePositionY;
    D3D11_FILTER scaleMode;

    /* YV12 texture support */
    SDL_bool yuv;
    ID3D11Texture2D *mainTextureU;
    ID3D11ShaderResourceView *mainTextureResourceViewU;
    ID3D11Texture2D *mainTextureV;
    ID3D11ShaderResourceView *mainTextureResourceViewV;
    Uint8 *pixels;
    int pitch;
    SDL_Rect locked_rect;
} D3D11_TextureData;

namespace PK {

// 
class PK_SDLDXTextureAsset : public PK_SDLTextureAsset
{
private:
	SDL_Texture *m_pTexture;
	D3D11_TextureData *m_pDXData;

public:
	PK_SDLDXTextureAsset(PK_AssetContainer &assetContainer);
	~PK_SDLDXTextureAsset();

	void BindTexture(SDL_Surface &surface);
	inline ID3D11ShaderResourceView * GetResourceView() { return m_pDXData->mainTextureResourceView; }

};

} // namespace

#endif