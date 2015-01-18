#include "PK_Globals.h"
#include "PK_Exceptions.h"
#include "PK_SDLRenderManager.h"
#include "PK_SDLTextureAsset.h"
#include "PK_Log.h"
#include "PK_OpenGL.h"

namespace PK {

//-----------------------------------------------------
PK_SDLRenderManager::PK_SDLRenderManager(const PK_String &sName) :
    PK_RenderManager(sName)
{
	SetTypeName("PK_SDLRenderManager");
    m_pWindow = NULL;
    m_pRenderer = NULL;
    m_pGLContext = NULL;
    m_pCurrentTexture = NULL;
    SetBlendMode(BlendMode_None);
}
    
//
void PK_SDLRenderManager::OnInitialize()
{
    if (IsInitialized())
    {
        throw PK_SystemException("Render manager is already initialized.", __FILE__, __LINE__);
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_Init(SDL_INIT_VIDEO); 
	SDL_SetHint(SDL_HINT_RENDER_DIRECT3D11_DEBUG, "1");

    // Verificar se a resolução é mais pequena do que a pretendida pelo jogo
    SDL_DisplayMode currentDisplayInfo;
    if (SDL_GetCurrentDisplayMode(0, &currentDisplayInfo) != 0)
    {
		throw PK_SDLException(__FILE__, __LINE__);
	}

    PK_tSize gameRes = PokeEngine.GetSettings().GetGameResolution();
    if (gameRes.w > currentDisplayInfo.w ||
        gameRes.h > currentDisplayInfo.h)
    {
        if (gameRes.w > currentDisplayInfo.w)
        {
            int saveW = (int)gameRes.w; 
            gameRes.w = (float)currentDisplayInfo.w;
            gameRes.h = (float)(gameRes.w * currentDisplayInfo.h / saveW);
#ifdef POKE_WINDOWS
            // Martelada para se ver a caption da janela, rever isto...
            gameRes.w = ((float)gameRes.w * 0.95f);
            gameRes.h = ((float)gameRes.h * 0.95f);
#endif
        }

        if (gameRes.h > currentDisplayInfo.h)
        {
            
            gameRes.w = gameRes.w * currentDisplayInfo.h / gameRes.h;
            gameRes.h = (float)currentDisplayInfo.h;
#ifdef POKE_WINDOWS
            // Martelada para se ver a caption da janela, rever isto...
            gameRes.w = ((float)gameRes.w * 0.95f);
            gameRes.h = ((float)gameRes.h * 0.95f);
#endif
        }

    }

    if (PokeEngine.GetSettings().GetForceWindowSize())
    {
        gameRes.h = PokeEngine.GetSettings().GetWindowSize().h;
        gameRes.w = PokeEngine.GetSettings().GetWindowSize().w;
    }


    int flags = 0;
#ifdef POKE_GL
	flags += SDL_WINDOW_OPENGL;
#endif
#ifndef POKE_WINDOWS
    flags += SDL_WINDOW_FULLSCREEN;
#endif
    if(SDL_CreateWindowAndRenderer((int)gameRes.w, (int)gameRes.h, flags, &m_pWindow, &m_pRenderer) < 0)
    {
		throw PK_SDLException(__FILE__, __LINE__);
	}
#ifdef POKE_GL
    // Criar um contexto para opengl
    m_pGLContext = SDL_GL_CreateContext(m_pWindow);
    if (m_pGLContext == NULL)
    {
		throw PK_SDLException(__FILE__, __LINE__);        
    }
#endif
	OnAfterRendererCreated();

    int w, h;
    SDL_GetWindowSize(m_pWindow, &w, &h);
    m_WindowSize = PK_tSize((float)w, (float)h);
    SetupViewport();

   
    // Criar um shader basico e setar como currente
    CreateInternalShaders();
    
    // Inicializar os shaders
    PK_RenderManager::InitializeShaders();

    m_bInitialized = true;
    
    // Criar uma camera por defeito
    PK_tSize res = PokeEngine.GetRenderManager().GetWindowSize();
    if (PokeEngine.GetSettings().GetUpscaleFlag() == true)
    {
        res = PokeEngine.GetSettings().GetGameResolution();
    }
    
    m_pDefaultCamera = PK_Camera::Create2D(PK_DEFAULT_2DCAMERA_NAME, PK_tSize((float)res.w, (float)res.h));
    m_pDefaultCamera->Grab();
    SetCamera(*m_pDefaultCamera);

    SetBlendMode(BlendMode_AlphaTransparency);
    
    m_pCurrentShader = NULL;
}
    
//
void PK_SDLRenderManager::OnUnInitialize()
{

    if (m_pGLContext != NULL)
    {
        SDL_GL_DeleteContext(m_pGLContext);
        m_pGLContext = NULL;
    }
    

    PK_RenderManager::OnUnInitialize();
}

// Static
PK_SDLRenderManager & PK_SDLRenderManager::GetSDLRenderManager()
{
	return *((PK_SDLRenderManager *)&PokeEngine.GetRenderManager());
}

//
void PK_SDLRenderManager::SetupViewport()
{
    if (m_pWindow == NULL)
    {
        throw PK_SystemException("Render manager has not been initialized.", __FILE__, __LINE__);
    }
    
    // Guardar o tamanho do ecran
    PK_tSize windowRes = GetWindowSize();
    PK_tSize gameRes = PokeEngine.GetSettings().GetGameResolution();
    float fGameAspectRatio = (float)gameRes.w / (float)gameRes.h; // Aspect ratio definido para o jogo
    float fRendererAspectRatio = (float)windowRes.w / (float)windowRes.h; // aspect ratio do screen
    float vw, vh;
    float vx, vy;

    m_frame = PK_tAABoundingSquare(-(gameRes.w / 2),- (gameRes.h / 2), gameRes.w, gameRes.h);
    if (fGameAspectRatio == fRendererAspectRatio) // Nao ha corte, frame = safe frame = viewport
    {
        vw = (float)windowRes.w;
        vh = (float)windowRes.h;
        vx = vy = 0; 
        m_safeFame = m_frame;
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
        m_safeFame = PK_tAABoundingSquare((int)-(fw / 2),(int)-(gameRes.h / 2), (int)fw, (int)gameRes.h);
    }
    else // corta em cima/baixo
    {
        vw = (float)windowRes.w;
        vh = (float)gameRes.h * (float)windowRes.w / (float)gameRes.w;
        vy = -(vh - windowRes.h) / 2;
        vx = 0;

        // O safe frame e em coordenadas do jogo e nao da janela
        float fh = (float)(windowRes.h * gameRes.w / windowRes.w);
        m_safeFame = PK_tAABoundingSquare((int)-(gameRes.w / 2),(int)-(fh / 2), (int)gameRes.w, (int)fh);
   }
    m_Viewport.Set(vx, vy, vw, vh);
    m_ViewportSize.Set((int) vw, (int)vh);
}
 
} // namespace
