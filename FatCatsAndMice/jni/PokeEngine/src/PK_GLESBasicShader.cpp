#include <assert.h>
#include <sdl.h>
#include "PK_GLESBasicShader.h"
#include "PK_Camera.h"
#include "PK_Globals.h"
#include "PK_Exceptions.h"

#define VERTEX_SHADER_CODE \
"attribute vec2 vPosition;" \
"uniform mat4 matViewProjection;" \
"void main()" \
"{" \
"  gl_Position = vec4(vPosition.xy, 0, 1) * matViewProjection;" \
"}"

#define COLOR_SHADER_CODE \
"precision mediump float;" \
"uniform vec4 vColor;" \
"void main()" \
"{" \
"  gl_FragColor = vColor;" \
"}"

namespace PK {

PK_GLESBasicShader::PK_GLESBasicShader(const PK_GLESRenderManager &renderManager) :
    PK_GLESShader(renderManager)
{
    SetTypeName("PK_GLESBasicShader");
    SetVertexShaderCode(VERTEX_SHADER_CODE);
    SetColorShaderCode(COLOR_SHADER_CODE);
    m_iPositionParamHandle = -1;
    m_iColorParamHandle = -1;
    m_iViewProjMatrixHandle = -1;
}
    
//
void PK_GLESBasicShader::Initialize()
{
    PK_GLESShader ::Initialize();
    
    // Obter o handle do parametro que tem a matrix de transformacao
    m_iViewProjMatrixHandle = glGetUniformLocation(m_uiProgram, "matViewProjection");
    assert(m_iViewProjMatrixHandle != -1);
    
    // Obter o handle do parametro que tem o array de vertices
    m_iPositionParamHandle = glGetAttribLocation(m_uiProgram, "vPosition");
    assert(m_iPositionParamHandle != -1);

    // Obter o handle do paramentro que tem a cor
    m_iColorParamHandle = glGetUniformLocation(m_uiProgram, "vColor");
    assert(m_iColorParamHandle != -1);
 
}
    
// Executa o shader
void PK_GLESBasicShader::Execute(PK_Vector2 *pVertices, const unsigned int uiVertexCount, unsigned short * puiFaceIndexes, unsigned int uiFaceCount, const PK_Color &color)
{
    assert(m_uiProgram != 0);
    
    glUseProgram(m_uiProgram);
    
    PK_Camera * pCamera = &PokeEngine.GetRenderManager().GetCamera();
    assert(pCamera != NULL); // Isto n deve acontecer, basta um assert
   
    // Apply the projection and view transformation
    glUniformMatrix4fv(m_iViewProjMatrixHandle, 1,  GL_FALSE, &(*(pCamera->GetProjectionMatrixPtr()))[0][0]);
    
    // Set color for drawing the triangle
    glUniform4f(m_iColorParamHandle, color.r, color.g, color.b, color.a);
    
    // Enable a handle to the triangle vertices
    glEnableVertexAttribArray(m_iPositionParamHandle);
   
    // Prepare the triangle coordinate data
    glVertexAttribPointer(m_iPositionParamHandle, 2, GL_FLOAT, GL_FALSE, 4 * 2, pVertices);
 
    // Desenha as faces
    glDrawElements(GL_TRIANGLES, uiFaceCount * 3, GL_UNSIGNED_SHORT, puiFaceIndexes);
    
    // Disable vertex array
    glDisableVertexAttribArray(m_iPositionParamHandle);
}

    
} // namespace