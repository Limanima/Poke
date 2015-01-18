#ifndef _PK_GLESBASICSHADER_H_
#define _PK_GLESBASICSHADER_H_

#include "PK_Vector2.h"
#include "PK_Matrix4.h"
#include "PK_Color.h"
#include "PK_GLESShader.h"

namespace PK {

class PK_GLESBasicShader : public PK_GLESShader
{
private:
    int m_iPositionParamHandle;
    int m_iColorParamHandle;
    int m_iViewProjMatrixHandle;
    
public:
    PK_GLESBasicShader(const PK_GLESRenderManager &renderManager);
    void Initialize();
    void Execute(PK_Vector2 *pVertices, const unsigned int uiVertexCount, unsigned short * puiFaceIndexes, unsigned int uiFaceCount, const PK_Color &color);

};
    
} // namespace

#endif
