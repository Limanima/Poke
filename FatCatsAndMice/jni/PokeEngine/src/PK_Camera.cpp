#include "PK_Globals.h"
#include "PK_Camera.h"
#include "PK_Exceptions.h"
#include "PK_Types.h"
#include "PK_Vector4.h"
#include "PK_Config.h"

namespace PK { 
    
PK_Camera::PK_Camera()
{
    SetTypeName("PK_Camera");
    SetView(PK_Matrix4(1.0));
    SetProjection(PK_Matrix4(1.0));
} 
    
void PK_Camera::SetProjection(const PK_Matrix4 &proj)
{
    m_matProjection = proj;
    m_matViewProjection = m_matProjection * m_matView;
    m_matViewProjectionInverse = glm::inverse(m_matViewProjection);
}
    
void PK_Camera::SetView(const PK_Matrix4 &view)
{
    m_matView = view;
    m_matViewProjection = m_matProjection * m_matView;
}
    
// Cria uma camera 2D com relacao 1->1 com o ecran
// Static
PK_Camera * PK_Camera::Create2D(const PK_String & sName, const PK_tSize &viewportSize)
{
    // Verificar se o render manager ja esta inicializado.
    // E necessario porque precisamos de saber o tamanho do ecran para criar a camera
    if (PokeEngine.GetRenderManager().IsInitialized() == false)
    {
        throw PK_SystemException("Camera cannot be created. RenderManager is not initialized.", __FILE__, __LINE__);
    }
    
    PK_Camera * pCamera = new PK_Camera();
    if (pCamera == NULL)
    {
        throw PK_OutOfMemoryException("PK_Camera", sizeof(PK_Camera), __FILE__, __LINE__);
    }
    pCamera->m_Viewport = viewportSize;
    pCamera->SetName(sName);
	PK_Matrix4 matView = PK_Matrix4(1.0);
    pCamera->SetView(matView);
    
    float right = (viewportSize.w / 2);
    float left = -(viewportSize.w / 2);
    float top = (viewportSize.h / 2);
    float bottom = -(viewportSize.h / 2);
    float near1 = 0.0f;
    float far1 = 1.0f;
    
    float a = 2.0f / (right - left);
    float b = 2.0f / (top - bottom);
    float c = -2.0f / (far1 - near1);
    
    float tx = -(right + left)/(right - left);
    float ty = -(top + bottom)/(top - bottom);
    float tz = - (far1 + near1)/(far1 - near1);
    
	// opengl

    PK_Matrix4 mat;
#if defined (POKE_GL) || defined (POKE_GLES)
    mat[0] = glm::vec4(a, 0, 0, tx);
    mat[1] = glm::vec4(0, b, 0, ty);
    mat[2] = glm::vec4(0, 0, c, tz);
    mat[3] = glm::vec4(0, 0, 0, 1);
#elif defined (POKE_DX)
    mat[0] = glm::vec4(a, 0, 0, tx);
    mat[1] = glm::vec4(0, b, 0, ty);
    mat[2] = glm::vec4(0, 0, -c, -tz);
    mat[3] = glm::vec4(0, 0, 0, 1);
#else
	IMPLEMENTAR!!
#endif
    pCamera->SetProjection(mat);

    pCamera->InitFrames(viewportSize);

    return pCamera;
}

// Converte um ponto de camera view para world view
// Retirado da source do gluUnproject http://collagefactory.blogspot.pt/2010/03/gluunproject-source-code.html
PK_Vector2 PK_Camera::Unproject(const PK_Vector2 &vPoint)
{

    PK_Vector4 v4;

    PK_tSize viewport = PokeEngine.GetRenderManager().GetViewportSize();
    v4.x = ((vPoint.x - (viewport.w / 2) ) / viewport.w) * 2;
    v4.y = ((-vPoint.y + (viewport.h / 2) ) / viewport.h) * 2;

    v4 = m_matViewProjectionInverse * v4;
    return PK_Vector2(v4.x + m_safeFrameBorder.x, 
                      v4.y + m_safeFrameBorder.y);
}

// Converte um ponto de camera view para world view
PK_Vector2 PK_Camera::UnprojectOffset(const PK_Vector2 &vOffset)
{
    PK_Vector4 v4;

    PK_tSize res = PokeEngine.GetRenderManager().GetWindowSize();
    v4.x = vOffset.x * m_Viewport.w / res.w;
    v4.y = vOffset.y * m_Viewport.h / res.h;
    
    return PK_Vector2(v4.x, v4.y);
}

//
void PK_Camera::InitFrames(const PK_tSize &viewportSize)
{

    m_frame.Set((viewportSize.w / 2), (viewportSize.h / 2), viewportSize.w, viewportSize.h);

    PK_tSize windowRes = PokeEngine.GetRenderManager().GetWindowSize();
    PK_tSize gameRes = PokeEngine.GetSettings().GetGameResolution();
    gameRes = viewportSize;
    float fGameAspectRatio = (float)gameRes.w / (float)gameRes.h; // Aspect ratio definido para o jogo
    float fRendererAspectRatio = (float)windowRes.w / (float)windowRes.h; // aspect ratio do screen
    float vw, vh;
    float vx, vy;

    if (fGameAspectRatio == fRendererAspectRatio) // Nao ha corte, frame = safe frame = viewport
    {
        vw = (float)windowRes.w;
        vh = (float)windowRes.h;
        vx = vy = 0; 
        m_safeFrame = m_frame;
    }
    else
    if (fRendererAspectRatio < fGameAspectRatio) // Corta nos lados
    {
        vh = (float)windowRes.h;
        vw = (float)((float)gameRes.w * (float)windowRes.h / (float)gameRes.h);
        vx = -(vw - windowRes.w) / 2;
        vy = 0;
        
        // O safe frame e em coordenadas do jogo e nao da janela
        float fw = (float)(windowRes.w * gameRes.h / windowRes.h);
        m_safeFrame = PK_tAABoundingSquare((int)-(fw / 2),(int)-(gameRes.h / 2), (int)fw, (int)gameRes.h);
    }
    else // corta em cima/baixo
    {
        vw = (float)windowRes.w;
        vh = (float)gameRes.h * (float)windowRes.w / (float)gameRes.w;
        vy = -(vh - windowRes.h) / 2;
        vx = 0;

        // O safe frame e em coordenadas do jogo e nao da janela
        float fh = (float)(windowRes.h * gameRes.w / windowRes.w);
        m_safeFrame = PK_tAABoundingSquare((int)-(gameRes.w / 2),(int)-(fh / 2), (int)gameRes.w, (int)fh);
   }

   m_safeFrameBorder = PK_Vector2((m_frame.size.w - m_safeFrame.size.w) / 2,
                                  (m_frame.size.h - m_safeFrame.size.h) / 2);
}
} // namespace
