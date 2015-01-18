#include <assert.h>
#include <sdl.h>
#include "PK_GLESTextureShader.h"
#include "PK_GLESRenderManager.h"
#include "PK_Camera.h"
#include "PK_Globals.h"
#include "PK_Exceptions.h"
#include "PK_Assert.h"

// Links sobre texturas
// http://www.raywenderlich.com/4404/opengl-es-2-0-for-iphone-tutorial-part-2-textures
// http://www.learnopengles.com/android-lesson-four-introducing-basic-texturing/
#define VERTEX_SHADER_CODE \
"uniform mat4 u_matViewProjection;" \
"" \
"attribute vec2 a_Position;" \
"attribute vec2 a_TexCoordinate;" \
"" \
"varying vec4 v_Color;" \
"varying vec2 v_TexCoordinate;" \
"void main()" \
"{" \
    "v_TexCoordinate = a_TexCoordinate;" \
    "gl_Position = vec4(a_Position.xy, 0, 1) * u_matViewProjection;" \
"}"


#define COLOR_SHADER_CODE \
"precision mediump float;" \
""\
"uniform sampler2D u_Texture;" \
"uniform vec4 u_Color;" \
""\
"varying vec2 v_TexCoordinate;" \
"void main()" \
"{" \
    "gl_FragColor = u_Color *(texture2D(u_Texture, v_TexCoordinate));" \
"}"

// Numero de triagulos maximo por batch
#define TRIANGLE_BATCH_COUNT  1000
#define COMPONENTS_PER_VERTEX    2  // x, y
#define COMPONENTS_PER_TEX_COORD 2  // tx, ty
#define VERTEX_STRIDE sizeof(PK_Vector2) 
#define TEXTURE_STRIDE sizeof(PK_Vector2)
#define VERTEXES_PER_TRIANGLE 3

namespace PK {
// FIXME: Falta o unload do shader!
PK_GLESTextureShader::PK_GLESTextureShader(const PK_GLESRenderManager &renderManager) :
    PK_GLESShader(renderManager)
{
    SetTypeName("PK_GLESTextureShader");
    SetVertexShaderCode(VERTEX_SHADER_CODE);
    SetColorShaderCode(COLOR_SHADER_CODE);

    m_uViewProjMatrixHandle = -1;
    m_aPositionInHandle = -1;
    m_uColorInHandle = -1;
    m_aTexCoordinateInHandle = -1;
    m_uTextureHandle = -1;
    m_pTriangleBatch = NULL;
    m_pTexCoordsBatch = NULL;
    m_puiFaceIndexes = NULL;
    m_iTriangleBatchCount = 0;
    m_pLastTextureUsed = NULL;
}

//
PK_GLESTextureShader::~PK_GLESTextureShader()
{
    OnUnload();
}

//
void PK_GLESTextureShader::Initialize()
{
    PK_GLESShader::Initialize();

    // Obter o handle do parametro que tem o array de vertices
    m_aPositionInHandle = glGetAttribLocation(m_uiProgram, "a_Position");
    assert(m_aPositionInHandle !=-1);
    
    // Obter o handle do parametro que tem a matrix de transformacao
    m_uViewProjMatrixHandle = glGetUniformLocation(m_uiProgram, "u_matViewProjection");
    assert(m_uViewProjMatrixHandle !=-1);

    // Obter o handle do parametro que tem o array de vertices
    m_uColorInHandle = glGetUniformLocation(m_uiProgram, "u_Color");
    assert(m_uColorInHandle !=-1);
     
    // Obter o handle do parametro que tem o array de vertices
    m_aTexCoordinateInHandle = glGetAttribLocation(m_uiProgram, "a_TexCoordinate");
    assert(m_aTexCoordinateInHandle !=-1);
    
    // Obter o handle do parametro que tem a matrix de transformacao
    m_uTextureHandle = glGetUniformLocation(m_uiProgram, "u_Texture");
    assert(m_uTextureHandle !=-1);

    // Inicializar o array para batch
    m_pTriangleBatch = new PK_tTriangle[TRIANGLE_BATCH_COUNT]; // 3 vertices por triangulo
    m_pTexCoordsBatch = new PK_tTriangleTextCoord[TRIANGLE_BATCH_COUNT];
    m_puiFaceIndexes = new unsigned short[VERTEXES_PER_TRIANGLE * TRIANGLE_BATCH_COUNT];

}

//
void PK_GLESTextureShader::OnUnload()
{
    if (m_pTriangleBatch != NULL)
    {
        delete [] m_pTriangleBatch;
        m_pTriangleBatch = NULL;
    }
    
    if (m_pTexCoordsBatch != NULL)
    {
        delete [] m_pTexCoordsBatch;
        m_pTexCoordsBatch = NULL;
    }
    
    if (m_puiFaceIndexes != NULL)
    {
        delete [] m_puiFaceIndexes;
        m_puiFaceIndexes = NULL;
    }

    PK_GLESShader::OnUnload();
}


//
void PK_GLESTextureShader::Commit(PK_Camera &camera)
{
    if (m_iTriangleBatchCount == 0)
    {
        return;
    }
    PK_ASSERT(m_pLastTextureUsed != NULL);

    m_pRenderManager->SetActiveTexture(*m_pLastTextureUsed);
    glUniform1i(m_uTextureHandle, 0);
    // Aplicar a matriz proj/view
    glUniformMatrix4fv(m_uViewProjMatrixHandle, 1,  GL_FALSE, &(*(camera.GetProjectionMatrixPtr()))[0][0]);
    // Set color for drawing the triangle
    glUniform4f(m_uColorInHandle, m_lastColorUsed.r, m_lastColorUsed.g, m_lastColorUsed.b, m_lastColorUsed.a);

    // Vertices
    glEnableVertexAttribArray(m_aPositionInHandle);
    glVertexAttribPointer(m_aPositionInHandle, COMPONENTS_PER_VERTEX, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, m_pTriangleBatch);

    // Coordenadas de textura
    glEnableVertexAttribArray(m_aTexCoordinateInHandle);
    glVertexAttribPointer(m_aTexCoordinateInHandle, COMPONENTS_PER_TEX_COORD, GL_FLOAT, GL_FALSE, TEXTURE_STRIDE, m_pTexCoordsBatch);
    // Desenha as faces
    glDrawElements(GL_TRIANGLES, m_iTriangleBatchCount * VERTEXES_PER_TRIANGLE, GL_UNSIGNED_SHORT, m_puiFaceIndexes);
    // Disable vertex array
    glDisableVertexAttribArray(m_aPositionInHandle);
    // Disable vertex array
    glDisableVertexAttribArray(m_aTexCoordinateInHandle);
    
    m_iTriangleBatchCount = 0;
}

// Executa o shader
void PK_GLESTextureShader::Execute(const PK_Vector2 *pVertices, const unsigned int uiVertexCount, unsigned char * puiFaceIndexes, unsigned int uiFaceCount, PK_Vector2 *pTextureCoords, const PK_Color &color, const PK_SDLTextureAsset &texture)
{
    PK_ASSERT (&texture != NULL);
        
    if (m_iTriangleBatchCount > 0)
    {
        if (m_iTriangleBatchCount + uiFaceCount >= TRIANGLE_BATCH_COUNT ||
            m_lastColorUsed != color ||
            m_pLastTextureUsed != &texture)
        {
            Commit();
        }
    }

    memcpy(&m_pTriangleBatch[m_iTriangleBatchCount], pVertices, uiVertexCount * sizeof(PK_Vector2));
    memcpy(&m_pTexCoordsBatch[m_iTriangleBatchCount], pTextureCoords, uiVertexCount * sizeof(PK_Vector2));
    int idx = m_iTriangleBatchCount * 3;
    for(int i = 0; i < uiVertexCount; i += 3, m_iTriangleBatchCount++)
    {
        m_puiFaceIndexes[(m_iTriangleBatchCount * 3)] = puiFaceIndexes[i] + idx;
        m_puiFaceIndexes[(m_iTriangleBatchCount * 3) + 1] = puiFaceIndexes[i + 1] + idx;
        m_puiFaceIndexes[(m_iTriangleBatchCount * 3) + 2] = puiFaceIndexes[i + 2] + idx;
    }
    
    m_lastColorUsed = color;
    m_pLastTextureUsed = (PK_SDLTextureAsset*)&texture;
}
    
} // namespace
