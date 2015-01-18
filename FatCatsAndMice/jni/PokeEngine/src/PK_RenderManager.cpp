#include "PK_RenderManager.h"
#include "PK_Exceptions.h"
#include "PK_Profiler.h"


namespace PK {

PK_RenderManager::PK_RenderManager(const PK_String &sName) :
  PK_Component(sName)
{
    SetClearColor(glm::vec4(0,0,0,1.0));
    m_bShadersInitialized = false;
    m_pCurrentShader = NULL;
    m_pCurrentCamera = NULL;
    m_bInitialized = false;
    m_pDefaultCamera = NULL;
}
    
// Liberta todos os resources utilizados
PK_RenderManager::~PK_RenderManager()
{
    for(PK_ListIterator(PK_Shader *) itor = m_Shaders.Begin(); itor != m_Shaders.End(); itor++)
    {
        (*itor)->OnUnload();
        (*itor)->Release();
    }
    m_Shaders.Clear();
        
    PK_FREE(m_pDefaultCamera);
    PK_FREE(m_pCurrentCamera);
    PK_FREE(m_pCurrentShader);
}

//
void PK_RenderManager::SetToDefaultCamera()
{
    if (m_pCurrentCamera == m_pDefaultCamera)
    {
        return;
    }
    SetCamera(*m_pDefaultCamera);
}

// Seta a camera currente
void PK_RenderManager::SetCamera(PK_Camera &camera)
{
    if (&camera == m_pCurrentCamera)
    {
        return;
    }

    PK_Camera *pPrevCamera = m_pCurrentCamera;
    if (m_pCurrentCamera != NULL)
    {
        m_pCurrentCamera->Release();
    }
    m_pCurrentCamera = &camera;
    m_pCurrentCamera->Grab();
    OnCameraChanged(*pPrevCamera);
}


// Executa o Initialize em todos os shaders
void PK_RenderManager::InitializeShaders()
{
    if (m_bShadersInitialized)
    {
        throw PK_SystemException("Shaders have already been initialized.", __FILE__, __LINE__);
    }
    
    for(PK_ListIterator(PK_Shader *) itor = m_Shaders.Begin(); itor != m_Shaders.End(); itor++)
    {
        (*itor)->Initialize();
    }

    m_bShadersInitialized = true;
}

// Seta o shader currente
void PK_RenderManager::SetShader(PK_Shader * pShader)
{
    if (pShader == NULL)
    {
        throw PK_NullArgumentException("pShader",__FILE__, __LINE__);
    }
    
    if (m_pCurrentShader != NULL)
    {
        m_pCurrentShader->Release();
    }
    
    m_pCurrentShader = pShader;
    m_pCurrentShader->Grab();
}
    
// Adiciona um shader a lista de shaders
void PK_RenderManager::AddShader(PK_Shader *pShader)
{
    if (pShader == NULL)
    {
        throw PK_NullArgumentException("pShader",__FILE__, __LINE__);
    }
    
    if (m_bShadersInitialized)
    {
        throw PK_SystemException("Cannot add shaders after initialization.", __FILE__, __LINE__);
    }
    
    pShader->Grab();
    m_Shaders.Add(pShader);
}


}// namespace
