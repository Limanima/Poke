#ifndef _PK_GLESTEXTURESHADER_H_
#define _PK_GLESTEXTURESHADER_H_

#include "PK_Vector3.h"
#include "PK_Vector2.h"
#include "PK_Matrix4.h"
#include "PK_Color.h"
#include "PK_GLESShader.h"
#include "PK_SDLTextureAsset.h"
#include "PK_Globals.h"

namespace PK {
    
struct PK_tTriangle
{
    PK_Vector2 v1, v2, v3;
};
struct PK_tTriangleTextCoord
{
   PK_Vector2 t1, t2, t3;
};

class PK_GLESTextureShader : public PK_GLESShader
{
private:
    int m_uViewProjMatrixHandle;
    int m_aPositionInHandle;
    int m_aTexCoordinateInHandle;
    
    // Fragment shader
    int m_uColorInHandle;
    int m_uTextureHandle;
    PK_tTriangle  * m_pTriangleBatch;
    PK_tTriangleTextCoord * m_pTexCoordsBatch;
    
    int               m_iTriangleBatchCount;
    unsigned short  * m_puiFaceIndexes;

    PK_Color               m_lastColorUsed;
    PK_SDLTextureAsset *m_pLastTextureUsed;


public:
    PK_GLESTextureShader(const PK_GLESRenderManager &renderManager);
    ~PK_GLESTextureShader();
    void Initialize();
    void OnUnload();
    void Execute(const PK_Vector2 *pVertices, const unsigned int uiVertexCount, unsigned char * puiFaceIndexes, unsigned int uiFaceCount, PK_Vector2 *pTextureCoords, const PK_Color &color, const PK_SDLTextureAsset &pTexture);

    inline void Commit()
    {
    	Commit(PokeEngine.GetRenderManager().GetCamera());
    }

    void Commit(PK_Camera &camera);
};
    
} // namespace

#endif
