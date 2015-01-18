#ifndef _PK_GLESSHADER_H_
#define _PK_GLESSHADER_H_


#include "PK_Shader.h"
#include "PK_String.h"
#include <SDL.h>
#include "PK_OpenGL.h"

namespace PK {

class PK_GLESRenderManager;
    
class PK_GLESShader : public PK_Shader
{
protected:
    GLuint     m_uiProgram;
    PK_String  m_sVertexShaderCode;
    PK_String  m_sColorShaderCode;
    PK_GLESRenderManager *m_pRenderManager;

    
public:
    PK_GLESShader(const PK_GLESRenderManager &renderManager);
    ~PK_GLESShader();
    virtual void Initialize();
    void OnUnload();
    void Execute() {}
    virtual void Activate() { glUseProgram(m_uiProgram); }
    inline void SetVertexShaderCode(const PK_String &sCode)
    { m_sVertexShaderCode = sCode; }
    
    inline void SetColorShaderCode(const PK_String &sCode)
    { m_sColorShaderCode = sCode; }
    
    int CompileShader(PK_String &sCode, const int iShaderType);
};
    
} // namespace

#endif
