#include "PK_DXTextureShader.h"
#include "PK_Exceptions.h"
#include "PK_DXRenderManager.h"
#include "PK_DXException.h"
#include "PK_FileReader.h"
#include "PK_tDXPrimitiveData.h"
#include "PK_MathHelper.h"
#include "PK_TextureAsset.h"
#include "PK_SDLDXTextureAsset.h"

namespace PK {

PK_DXTextureShader::PK_DXTextureShader(PK_DXRenderManager &renderManager)
{
    SetTypeName("PK_DXTextureShader");
	m_pRenderManager = &renderManager;
	m_pD3DRenderData = NULL;
	m_pPixelShader = NULL;
	m_pVertexShader = NULL;
	m_pInputLayout = NULL;
	m_pSamplerState = NULL;
}

//
PK_DXTextureShader::~PK_DXTextureShader()
{
}

//
void PK_DXTextureShader::Initialize()
{

	m_pD3DRenderData = &m_pRenderManager->GetD3DData();

	PK_MemoryBuffer memBuffer;
	PK_FileReader reader;
	reader.ReadFile("TextPixelShader.cso", memBuffer);

	HRESULT hRes = m_pD3DRenderData->d3dDevice->CreatePixelShader(
				memBuffer.GetData(),
				memBuffer.GetLength(),
				nullptr,
				&m_pPixelShader);

	if (FAILED(hRes))
	{
		throw PK_DXException(hRes, "ID3D11Device1", "CreatePixelShader", __FILE__, __LINE__);
	}

	reader.ReadFile("TextVertexShader.cso", memBuffer);
    hRes = m_pD3DRenderData->d3dDevice->CreateVertexShader(
				memBuffer.GetData(),
				memBuffer.GetLength(),
				nullptr,
				&m_pVertexShader);

	if (FAILED(hRes))
	{
		throw PK_DXException(hRes, "ID3D11Device1", "CreateVertexShader", __FILE__, __LINE__);
	}

	
	const D3D11_INPUT_ELEMENT_DESC vertexDesc[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 }
		,{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	hRes =  m_pD3DRenderData->d3dDevice->CreateInputLayout(
			vertexDesc,
			ARRAYSIZE(vertexDesc),
			memBuffer.GetData(),
			memBuffer.GetLength(),
			&m_pInputLayout);
	if (FAILED(hRes))
	{
		throw PK_DXException(hRes, "ID3D11Device1", "CreateInputLayout", __FILE__, __LINE__);
	}


	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(PK_tTextureShaderConstantData), D3D11_BIND_CONSTANT_BUFFER);	
	hRes =  m_pD3DRenderData->d3dDevice->CreateBuffer(
		&constantBufferDesc,
		nullptr,
		&m_pConstantBuffer);
	if (FAILED(hRes))
	{
		throw PK_DXException(hRes, "ID3D11Device1", "CreateInputLayout", __FILE__, __LINE__);
	}
	D3D11_SAMPLER_DESC samplerDesc;
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

    // The sampler does not use anisotropic filtering, so this parameter is ignored.
    samplerDesc.MaxAnisotropy = 0;

    // Specify how texture coordinates outside of the range 0..1 are resolved.
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

    // Use no special MIP clamping or bias.
    samplerDesc.MipLODBias = 0.0f;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    // Don't use a comparison function.
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

    // Border address mode is not used, so this parameter is ignored.
    samplerDesc.BorderColor[0] = 0.0f;
    samplerDesc.BorderColor[1] = 0.0f;
    samplerDesc.BorderColor[2] = 0.0f;
    samplerDesc.BorderColor[3] = 0.0f;

    hRes = m_pD3DRenderData->d3dDevice->CreateSamplerState(
        &samplerDesc,
        &m_pSamplerState);
	if (FAILED(hRes))
	{
		throw PK_DXException(hRes, "ID3D11Device1", "CreateSamplerState", __FILE__, __LINE__);
	}
}

//
PK_tDXTextureShaderData & PK_DXTextureShader::CreateRenderData(const PK_tBoundingSquare &bs, PK_Vector2 texCoords[])
{
	PK_tDXTextureShaderData *pData = new PK_tDXTextureShaderData();
	pData->m_pVertexBuffer = NULL;

	PK_tDXTextureShaderData::PK_tVertexFormat bsVertices[4] = 
	{ {bs.m_Vertices[0].x, bs.m_Vertices[0].y, 0.0f, texCoords[0].x, texCoords[0].y}, 
	  {bs.m_Vertices[1].x, bs.m_Vertices[1].y, 0.0f, texCoords[1].x, texCoords[1].y}, 
	  {bs.m_Vertices[2].x, bs.m_Vertices[2].y, 0.0f, texCoords[2].x, texCoords[2].y}, 
	  {bs.m_Vertices[3].x, bs.m_Vertices[3].y, 0.0f, texCoords[3].x, texCoords[3].y} 
	};

	D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
		vertexBufferData.pSysMem = bsVertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(bsVertices), D3D11_BIND_VERTEX_BUFFER);
		
	HRESULT hRes = m_pD3DRenderData->d3dDevice->CreateBuffer(
				&vertexBufferDesc,
				&vertexBufferData,
				&pData->m_pVertexBuffer);
	if (FAILED(hRes))
	{
		throw PK_DXException(hRes, "ID3D11Device1", "CreateBuffer", __FILE__, __LINE__);
	}

	unsigned short indices[] = 
		{ 0, 1, 2,
		  2, 3, 0
		};

	D3D11_SUBRESOURCE_DATA indexBufferData = {0};
	indexBufferData.pSysMem = indices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(indices), D3D11_BIND_INDEX_BUFFER);
	hRes = m_pD3DRenderData->d3dDevice->CreateBuffer(
			&indexBufferDesc,
			&indexBufferData,
			&pData->m_pIndexBuffer);
	if (FAILED(hRes))
	{
		throw PK_DXException(hRes, "ID3D11Device1", "CreateBuffer", __FILE__, __LINE__);
	}
	pData->m_iVertexSize = sizeof(PK_tDXTextureShaderData::PK_tVertexFormat);
	pData->m_iIndexCount = ARRAYSIZE(indices);
	return *pData;
}

// Executa o shader
void PK_DXTextureShader::Execute(const PK_tPrimitiveData &primitiveData, const PK_Color &color, const PK_Matrix3 &matModel, const PK_TextureAsset &texture)
{
	PK_tDXPrimitiveData *pData = (PK_tDXPrimitiveData *)&primitiveData;
	PK_SDLDXTextureAsset * pDXTextureAsset = (PK_SDLDXTextureAsset *)&texture;
	PK_Matrix4 m;
	PK_MathHelper::FromM3ToM4(matModel, m);
	m_constantBufferData.view = PK_Matrix4(PK_Matrix3(1.0));
	m_constantBufferData.model = glm::transpose(m);
	m_constantBufferData.projection = m_pRenderManager->GetCamera().GetProjectionMatrix();
	m_constantBufferData.color = color;
		
	m_pD3DRenderData->d3dContext->UpdateSubresource(
		m_pConstantBuffer,
		0,
		NULL,
		&m_constantBufferData,
		0,
		0);
	
	m_pD3DRenderData->d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pD3DRenderData->d3dContext->IASetInputLayout(m_pInputLayout);

	m_pD3DRenderData->d3dContext->VSSetShader(
		m_pVertexShader,
		nullptr,
		0
		);
	
	m_pD3DRenderData->d3dContext->VSSetConstantBuffers(
		0,
		1,
		&m_pConstantBuffer);
		
	m_pD3DRenderData->d3dContext->PSSetShader(
		m_pPixelShader,
		nullptr,
		0);
	
	ID3D11ShaderResourceView *pView = pDXTextureAsset->GetResourceView();
    m_pD3DRenderData->d3dContext->PSSetShaderResources(
            0,
            1,
			&pView);

    m_pD3DRenderData->d3dContext->PSSetSamplers(
        0,
        1,
        &m_pSamplerState);
	
	m_pD3DRenderData->d3dContext->DrawIndexed(
		pData->m_iIndexCount,
		0,
		0);   
}

    
} // namespace