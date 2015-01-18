
#include "PK_GLESShader.h"
#include "PK_Exceptions.h"
#include "PK_GLESException.h"
#include "PK_GLESRenderManager.h"
 
namespace PK {
    
PK_GLESShader::PK_GLESShader(const PK_GLESRenderManager &renderManager)
{
    SetTypeName("PK_GLESShader");
    m_pRenderManager = (PK_GLESRenderManager*)&renderManager;
    m_uiProgram = 0;
}

PK_GLESShader::~PK_GLESShader()
{
    OnUnload();
}
  
// Compila e prepara o shader para poder ser utilizado
void PK_GLESShader::Initialize()
{
    if (m_uiProgram != 0)
    {
        throw PK_SystemException("Shader already initialized", __FILE__, __LINE__);
    }
        
    int iVertexShader = CompileShader(m_sVertexShaderCode, GL_VERTEX_SHADER);
    int iColorShader = CompileShader(m_sColorShaderCode, GL_FRAGMENT_SHADER);
    
    m_uiProgram = glCreateProgram();
    glAttachShader(m_uiProgram, iVertexShader);   // add the vertex shader to program
    if (glGetError() != GL_NO_ERROR)
    {
        throw PK_GLESException(__FILE__, __LINE__);
    }
    
    glAttachShader(m_uiProgram, iColorShader); // add the fragment shader to program
    if (glGetError() != GL_NO_ERROR)
    {
        throw PK_GLESException(__FILE__, __LINE__);
    }
    
    glLinkProgram(m_uiProgram);
    if (glGetError() != GL_NO_ERROR)
    {
        throw PK_GLESException(__FILE__, __LINE__);
    }
}

//
void PK_GLESShader::OnUnload()
{
    if (m_uiProgram != 0)
    {
        glDeleteProgram(m_uiProgram);
        m_uiProgram = 0;
    }
}

// Compila um shader e devolve o id atribuido pelo OpenGL
int PK_GLESShader::CompileShader(PK_String &sCode, const int iShaderType)
{
    int iShader = glCreateShader(iShaderType);
    const char * pszCode = sCode.c_str();
    glShaderSource(iShader, 1, &pszCode, NULL);
    glCompileShader(iShader);
    int iCompileStatus = 0;
    glGetShaderiv(iShader, GL_COMPILE_STATUS, &iCompileStatus);
    if (iCompileStatus != GL_TRUE)
    {
        throw PK_SystemException("Error compiling shader.", __FILE__, __LINE__);
    }
    
    return iShader;
}


} // namespace
