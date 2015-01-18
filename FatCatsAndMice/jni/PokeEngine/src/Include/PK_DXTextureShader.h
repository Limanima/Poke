#ifndef _PK_DXTEXTURESHADER_H_
#define _PK_DXTEXTURESHADER_H_

#include "PK_Shader.h"
#include "PK_Vector2.h"
#include "PK_DXRenderManager.h"
#include "PK_Matrix4.h"
#include "PK_tPrimitiveData.h"

class ID3D11PixelShader;
class ID3D11VertexShader;
class ID3D11InputLayout;

namespace PK {
	
struct PK_tTextureShaderConstantData
{
	PK_Matrix4 model;
	PK_Matrix4 view;
	PK_Matrix4 projection;
	PK_Color color;
};

// 
struct PK_tDXTextureShaderData : PK_tPrimitiveData
{
	struct PK_tVertexFormat
	{
		float x, y, z;    
		float tx, ty;
	};
	ID3D11Buffer *m_pVertexBuffer;
	ID3D11Buffer *m_pIndexBuffer;
	int			  m_iVertexSize;
	int           m_iIndexCount;
};

class PK_DXTextureShader : public PK_Shader
{
private:
	PK_DXRenderManager *m_pRenderManager;
	ID3D11PixelShader  *m_pPixelShader;
	ID3D11VertexShader *m_pVertexShader;
	ID3D11InputLayout  *m_pInputLayout;
	D3D11_RenderData   *m_pD3DRenderData;
	ID3D11Buffer       *m_pConstantBuffer;
	PK_tTextureShaderConstantData m_constantBufferData;
	ID3D11SamplerState *m_pSamplerState;

public:
    PK_DXTextureShader(PK_DXRenderManager &renderManager);
	~PK_DXTextureShader();
    void Initialize();
	PK_tDXTextureShaderData & CreateRenderData(const PK_tBoundingSquare &bs, PK_Vector2 texCoords[]);
	void Execute() {}
	void Execute(const PK_tPrimitiveData &primitiveData, const PK_Color &color, const PK_Matrix3 &matModel, const PK_TextureAsset &texture);


};
    
} // namespace

#endif
