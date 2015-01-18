#ifndef _PK_DXBASICSHADER_H_
#define _PK_DXBASICSHADER_H_

#include "PK_Shader.h"
#include "PK_Vector2.h"
#include "PK_DXRenderManager.h"
#include "PK_Matrix4.h"
#include "PK_tPrimitiveData.h"

class ID3D11PixelShader;
class ID3D11VertexShader;
class ID3D11InputLayout;

namespace PK {
	
struct PK_tBasicShaderConstantData
{
	PK_Matrix4 model;
	PK_Matrix4 view;
	PK_Matrix4 projection;
	PK_Color color;
};

// 
struct PK_tDXBasicShaderData : PK_tPrimitiveData
{
	struct PK_tVertexFormat
	{
		float x, y, z;    
	};
	ID3D11Buffer *m_pVertexBuffer;
	ID3D11Buffer *m_pIndexBuffer;
	int			  m_iVertexSize;
	int           m_iIndexCount;
};

class PK_DXBasicShader : public PK_Shader
{
private:
	PK_DXRenderManager *m_pRenderManager;
	ID3D11PixelShader  *m_pPixelShader;
	ID3D11VertexShader *m_pVertexShader;
	ID3D11InputLayout  *m_pInputLayout;
	D3D11_RenderData   *m_pD3DRenderData;
	ID3D11Buffer       *m_pConstantBuffer;
	PK_tBasicShaderConstantData m_constantBufferData;

public:
    PK_DXBasicShader(PK_DXRenderManager &renderManager);
	~PK_DXBasicShader();
    void Initialize();
	PK_tDXBasicShaderData & CreateRenderData(const PK_tBoundingSquare &bs);
	void Execute() {}
	void Execute(const PK_tPrimitiveData &primitiveData, const PK_Color &color, const PK_Matrix3 &matModel);

};
    
} // namespace

#endif
