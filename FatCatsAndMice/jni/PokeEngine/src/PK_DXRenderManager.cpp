#include "PK_DXRenderManager.h"
#include "PK_DXBasicShader.h"
#include "PK_DXTextureShader.h"
#include "PK_tDXPrimitiveData.h"
#include "PK_DXException.h"
#include "PK_SpriteAsset.h"
#include "PK_Globals.h"
#include "PK_tSpriteFrame.h"

#include <SDL.h>
#include <../include/SDL_syswm.h>
#include <directxmath.h>
#include <directxmathmatrix.inl>
#include <windows.ui.core.h>
#include <windows.graphics.display.h>

#include <../include/SDL_config.h>
#include <../src/dynapi/SDL_dynapi.h>
#include <../src/render/SDL_sysrender.h>

#define CHECK_HRES if (FAILED(hRes)) throw PK_DXException(hRes, "", "", __FILE__, __LINE__);

struct PK_tXYZColorVertex
{
    float x, y, z;    
};

namespace PK {

//
PK_DXRenderManager::PK_DXRenderManager(const PK_String &sName) :
    PK_SDLRenderManager(sName)
{
	SetTypeName("PK_DXRenderManager");
	m_pRasterState = NULL;
	m_pColorShader = NULL;
	m_pTextureShader = NULL;
	m_pD3DRenderData = NULL;
	m_pAlphaBlend = NULL;
	m_pDSState = NULL;
	m_pCurrentBlend = NULL;
}

//
void PK_DXRenderManager::OnInitialize()
{
	PK_SDLRenderManager::OnInitialize();
}

//
void PK_DXRenderManager::OnAfterRendererCreated()
{
	SDL_Renderer *pSdlRenderer = PK_SDLRenderManager::GetSDLRenderManager().GetRenderer();
	m_pD3DRenderData = (D3D11_RenderData *) pSdlRenderer->driverdata;	

	// alpha blend
    D3D11_BLEND_DESC blendDesc;
    blendDesc.AlphaToCoverageEnable = FALSE;
    blendDesc.IndependentBlendEnable = FALSE;
    blendDesc.RenderTarget[0].BlendEnable = true;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	HRESULT hRes = m_pD3DRenderData->d3dDevice->CreateBlendState(&blendDesc, &m_pAlphaBlend);
	if (FAILED(hRes))
	{
		throw PK_DXException(hRes, "ID3D11Device1", "CreateBuffer", __FILE__, __LINE__);
	}

}

//
void PK_DXRenderManager::CreateInternalShaders()
{
	// Shader cor
    m_pColorShader = new PK_DXBasicShader(*this);
    PK_CHECK_OBJECT_ALLOC(PK_DXBasicShader, m_pColorShader);
    m_pColorShader->Grab();
    AddShader(m_pColorShader);

	// Shader textura
    m_pTextureShader = new PK_DXTextureShader(*this);
    PK_CHECK_OBJECT_ALLOC(PK_DXTextureShader, m_pTextureShader);
    m_pTextureShader->Grab();
    AddShader(m_pTextureShader);
}

//
void PK_DXRenderManager::BeginRender()
{
	m_pD3DRenderData->d3dContext->OMSetRenderTargets(
	1,
	&m_pD3DRenderData->mainRenderTargetView,
	NULL);	
	m_pD3DRenderData->d3dContext->ClearRenderTargetView(
		m_pD3DRenderData->mainRenderTargetView,
		(float*)&GetClearColor());

}

//
void PK_DXRenderManager::EndRender()
{
	UINT syncInterval = 1;
    UINT presentFlags = 0;
    HRESULT hRes = m_pD3DRenderData->swapChain->Present(syncInterval, presentFlags);
	if (FAILED(hRes))
	{
		throw PK_DXException(hRes, "ID3D11Device1", "CreateBuffer", __FILE__, __LINE__);
	}
}

//
void PK_DXRenderManager::OnCameraChanged(PK_Camera &previousCamera)
{

}
//
void PK_DXRenderManager::RenderQuad(const PK_tBoundingSquare &bs, const PK_Color &color)
{

}

//
void PK_DXRenderManager::RenderQuad(const PK_tPrimitiveData &primitiveData, const PK_Color &color, const PK_Matrix3 &matModel)
{
	PK_tDXPrimitiveData *pData = (PK_tDXPrimitiveData *)&primitiveData;
	UINT stride = pData->m_iVertexSize;
	UINT offset = 0;
	m_pD3DRenderData->d3dContext->IASetIndexBuffer(
		(ID3D11Buffer *)pData->m_pIndexBuffer,
		DXGI_FORMAT_R16_UINT,
		0);	
	
	m_pD3DRenderData->d3dContext->IASetVertexBuffers(
		0,
		1,
		&pData->m_pVertexBuffer,
		&stride,
		&offset);

	m_pColorShader->Execute(primitiveData, color, matModel);
}

//
void PK_DXRenderManager::RenderImage(const PK_tPrimitiveData &primitiveData, const PK_TextureAsset &texture, const PK_Color &color, const PK_Matrix3 &matModel) 
{
	PK_SDLTextureAsset *pSdlTExture = (PK_SDLTextureAsset *)&texture;
    PK_tDXPrimitiveData *pData = (PK_tDXPrimitiveData *)&primitiveData;
	UINT stride = pData->m_iVertexSize;
	UINT offset = 0;
	m_pD3DRenderData->d3dContext->IASetIndexBuffer(
		(ID3D11Buffer *)pData->m_pIndexBuffer,
		DXGI_FORMAT_R16_UINT,
		0);	
	
	m_pD3DRenderData->d3dContext->IASetVertexBuffers(
		0,
		1,
		&pData->m_pVertexBuffer,
		&stride,
		&offset);


	m_pTextureShader->Execute(primitiveData, color, matModel, texture);
	
}

//
void PK_DXRenderManager::RenderImage(const PK_tBoundingSquare &bsDest, PK_TextureAsset *pTexture, const PK_Color &color)
{

}

//
void PK_DXRenderManager::RenderImage(const PK_tTextureFrame &bsSource, const PK_tBoundingSquare &bsDest, const PK_TextureAsset &texture, const PK_Color &color)
{

}

//
void PK_DXRenderManager::RenderSprite(PK_SpriteAsset &sprite, const PK_tBoundingSquare &bs, unsigned int uiFrameNr, const PK_Color &color)
{
	
}

//
void PK_DXRenderManager::RenderSprite(PK_SpriteAsset &sprite, unsigned int uiFrameNr, const PK_Color &color, const PK_Matrix3 &matModel)
{
	PK_SDLTextureAsset *pSdlTExture = (PK_SDLTextureAsset *)sprite.GetTexture();
    PK_tSpriteFrame *pFrame = sprite.GetFramePtr(uiFrameNr);
	PK_tDXPrimitiveData *pData = (PK_tDXPrimitiveData *)pFrame->m_pFrameRenderData;
	UINT stride = pData->m_iVertexSize;
	UINT offset = 0;
	m_pD3DRenderData->d3dContext->IASetIndexBuffer(
		(ID3D11Buffer *)pData->m_pIndexBuffer,
		DXGI_FORMAT_R16_UINT,
		0);	
	
	m_pD3DRenderData->d3dContext->IASetVertexBuffers(
		0,
		1,
		&pData->m_pVertexBuffer,
		&stride,
		&offset);


	m_pTextureShader->Execute(*pFrame->m_pFrameRenderData, color, matModel, *pSdlTExture);
}

//
void PK_DXRenderManager::RenderSprite(PK_SpriteAsset &sprite, const PK_Vector2 &vPosition, unsigned int uiFrameNr, const PK_Color &color, const PK_Vector2 &vPivot, float fRotation)
{
 
}

//
void PK_DXRenderManager::RenderText(const PK_String &sText, PK_FontAsset &font, PK_Vector2 &vPosition, const PK_Color &color)
{
}

//
void PK_DXRenderManager::RenderPolygon(PK_Vector2 *vertices, unsigned int uiNumVertices, const PK_Color &color)
{

}

//
void PK_DXRenderManager::RenderSolidPolygon(PK_Vector2 *vertices, unsigned int uiNumVertices, const PK_Color &color)
{

}

//
void PK_DXRenderManager::RenderCircle(PK_Vector2 &center, float fRadius, const PK_Color &color, unsigned int uiSegments)
{

 }

//
void PK_DXRenderManager::RenderSolidCircle(PK_Vector2 &center, float fRadius, const PK_Color &color, unsigned int uiSegments)
{
 
}

//
void PK_DXRenderManager::RenderSegment(PK_Vector2 &v1, PK_Vector2 &v2, const PK_Color &color)
{
}

//
void PK_DXRenderManager::RenderPoint(PK_Vector2 &v1, float fSize, const PK_Color &color)
{
}

//
void PK_DXRenderManager::SetBlendMode(PK_eBlendMode blendMode)
{
	ID3D11BlendState	*pBlend = NULL;
	switch(blendMode)
	{
		case PK::BlendMode_AlphaTransparency:
			pBlend = m_pAlphaBlend;
			break;

		case PK::BlendMode_None:
			break;
	}
	if (pBlend != m_pCurrentBlend)
	{
		m_pD3DRenderData->d3dContext->OMSetBlendState(pBlend, 0, 0xFFFFFFFF);
		m_pCurrentBlend = pBlend;
	}
}


//
PK_tPrimitiveData & PK_DXRenderManager::CreateColorShaderPrimitiveData(PK_tBoundingSquare &bs)
{
	PK_tDXBasicShaderData *pData = &m_pColorShader->CreateRenderData(bs);
	return *pData;
}

//
PK_tPrimitiveData & PK_DXRenderManager::CreateTextureShaderPrimitiveData(PK_tBoundingSquare &bs, PK_Vector2 texCoords[])
{
	PK_tDXTextureShaderData *pData = &m_pTextureShader->CreateRenderData(bs, texCoords);
	return *pData;
}

//
void PK_DXRenderManager::SetupViewport()
{
	PK_SDLRenderManager::SetupViewport();
	/*
	D3D11_VIEWPORT vp[1];
	vp[0].Width = GetSafeFrame().size.w- 100;
    vp[0].Height = GetSafeFrame().size.h;
    vp[0].MinDepth = 0;
    vp[0].MaxDepth = 1;
    vp[0].TopLeftX = 0;
    vp[0].TopLeftY = 0;

	m_pD3DRenderData->d3dContext->RSSetViewports( 1, vp );*/
}

//static 
PK_DXRenderManager * PK_DXRenderManager::GetDXRenderManager()
{
	return (PK_DXRenderManager *)&PokeEngine.GetRenderManager();
}

} // namespace
