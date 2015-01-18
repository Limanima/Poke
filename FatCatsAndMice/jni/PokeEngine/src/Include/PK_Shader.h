#ifndef _PK_SHADER_H_
#define _PK_SHADER_H_

#include "PK_Object.h"
#include "PK_Color.h"
#include "PK_Vector3.h"

namespace PK {

class PK_Camera;
    
class PK_Shader : public PK_Object
{

public:
    // Inicialize e chamado apenas na inicializacao do engine
    virtual void Initialize() = 0;
    // Executa o shader
    virtual void Execute() = 0;
    virtual void Commit() {}
    virtual void Commit(PK_Camera &camera) {}
    virtual void OnUnload() {}
};
    
} // namespace

#endif
