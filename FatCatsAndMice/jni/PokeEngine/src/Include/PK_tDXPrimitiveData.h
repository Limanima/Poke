#ifndef _PK_DXPRIMITIVEDATA_H_
#define _PK_DXPRIMITIVEDATA_H_

#include "PK_tPrimitiveData.h"

class ID3D11Buffer;


namespace PK {    

// 
struct PK_tDXPrimitiveData : PK_tPrimitiveData
{
	ID3D11Buffer *m_pVertexBuffer;
	ID3D11Buffer *m_pIndexBuffer;
	int			  m_iVertexSize;
	int           m_iIndexCount;
};

} // namespace

#endif
