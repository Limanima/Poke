#ifndef _PK_GLRenderManager_H_
#define _PK_GLRenderManager_H_

#include "PK_SDLRenderManager.h"
#include "PK_Matrix4.h"


#include <d3d11_1.h>

/* Vertex shader, common values */
#define Float4X4 PK_Matrix4
typedef struct
{
    Float4X4 model;
    Float4X4 projectionAndView;
} VertexShaderConstants;

/* Private renderer data */
typedef struct
{
    void *hDXGIMod;
    void *hD3D11Mod;
    IDXGIFactory2 *dxgiFactory;
    IDXGIAdapter *dxgiAdapter;
    ID3D11Device1 *d3dDevice;
    ID3D11DeviceContext1 *d3dContext;
    IDXGISwapChain1 *swapChain;
    DXGI_SWAP_EFFECT swapEffect;
    ID3D11RenderTargetView *mainRenderTargetView;
    ID3D11RenderTargetView *currentOffscreenRenderTargetView;
    ID3D11InputLayout *inputLayout;
    ID3D11Buffer *vertexBuffer;
    ID3D11VertexShader *vertexShader;
    ID3D11PixelShader *colorPixelShader;
    ID3D11PixelShader *texturePixelShader;
    ID3D11PixelShader *yuvPixelShader;
    ID3D11BlendState *blendModeBlend;
    ID3D11BlendState *blendModeAdd;
    ID3D11BlendState *blendModeMod;
    ID3D11SamplerState *nearestPixelSampler;
    ID3D11SamplerState *linearSampler;
    D3D_FEATURE_LEVEL featureLevel;

    /* Rasterizers */
    ID3D11RasterizerState *mainRasterizer;
    ID3D11RasterizerState *clippedRasterizer;

    /* Vertex buffer constants */
    VertexShaderConstants vertexShaderConstantsData;
    ID3D11Buffer *vertexShaderConstants;

    /* Cached renderer properties */
    DXGI_MODE_ROTATION rotation;
    ID3D11RenderTargetView *currentRenderTargetView;
    ID3D11RasterizerState *currentRasterizerState;
    ID3D11BlendState *currentBlendState;
    ID3D11PixelShader *currentShader;
    ID3D11ShaderResourceView *currentShaderResource;
    ID3D11SamplerState *currentSampler;
} D3D11_RenderData;


namespace PK {

class PK_DXBasicShader;
class PK_DXTextureShader;

class PK_DXRenderManager : public PK_SDLRenderManager
{
private:
	D3D11_RenderData      *m_pD3DRenderData;
	PK_DXBasicShader      *m_pColorShader;
	PK_DXTextureShader    *m_pTextureShader;
	ID3D11RasterizerState1 * m_pRasterState;
	ID3D11DepthStencilState * m_pDSState;
	ID3D11BlendState	  *m_pAlphaBlend;
	ID3D11BlendState	  *m_pCurrentBlend;

public:
    PK_DXRenderManager(const PK_String &sName);
    void OnInitialize();
	void OnAfterRendererCreated();

	void CreateInternalShaders();
    void OnCameraChanged(PK_Camera &previousCamera);
	void BeginRender();
	void EndRender();
	void SetBlendMode(PK_eBlendMode blendMode);
	void RenderQuad(const PK_tBoundingSquare &bs, const PK_Color &color);
	void RenderQuad(const PK_tPrimitiveData &primitiveData, const PK_Color &color, const PK_Matrix3 &matModel);
	  void RenderImage(const PK_tPrimitiveData &primitiveData, const PK_TextureAsset &texture, const PK_Color &color, const PK_Matrix3 &matModel); 
	void RenderImage(const PK_tBoundingSquare &bsDest, PK_TextureAsset *pTexture, const PK_Color &color);
    void RenderImage(const PK_tTextureFrame &bsSource, const PK_tBoundingSquare &bsDest, const PK_TextureAsset &texture, const PK_Color &color);
    void RenderSprite(PK_SpriteAsset &sprite, unsigned int uiFrameNr, const PK_Color &color, const PK_Matrix3 &matModel);
	void RenderSprite(PK_SpriteAsset &sprite, const PK_tBoundingSquare &bs, unsigned int iFrameNr, const PK_Color &color);
    void RenderSprite(PK_SpriteAsset &sprite, const PK_Vector2 &vPosition, unsigned int uiFrameNr, const PK_Color &color, const PK_Vector2 &vPivot, float fRotation);
    void RenderText(const PK_String &sText, PK_FontAsset &font, PK_Vector2 &vPosition, const PK_Color &color);
    void RenderPolygon(PK_Vector2 *vertices, unsigned int uiNumVertices, const PK_Color &color);
    void RenderSolidPolygon(PK_Vector2 *vertices, unsigned int uiNumVertices, const PK_Color &color);
    void RenderCircle(PK_Vector2 &center, float fRadius, const PK_Color &color, unsigned int uiSegments);
    void RenderSolidCircle(PK_Vector2 &center, float fRadius, const PK_Color &color, unsigned int uiSegments);
    void RenderSegment(PK_Vector2 &v1, PK_Vector2 &v2, const PK_Color &color);
    void RenderPoint(PK_Vector2 &v1, float fSize, const PK_Color &color);
	void SetupViewport();

    PK_tPrimitiveData & CreateColorShaderPrimitiveData(PK_tBoundingSquare &bs);
    PK_tPrimitiveData & CreateTextureShaderPrimitiveData(PK_tBoundingSquare &bs, PK_Vector2 texCoords[]);
	inline D3D11_RenderData & GetD3DData() { return *m_pD3DRenderData; }
	static PK_DXRenderManager * GetDXRenderManager();

private:
    void SetActiveTexture(PK_SDLTextureAsset *pTexture);
};

}
#endif
