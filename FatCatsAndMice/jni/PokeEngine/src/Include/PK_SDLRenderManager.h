#ifndef _PK_SDLRenderManager_H_
#define _PK_SDLRenderManager_H_

#include "PK_Consts.h"
#include "PK_RenderManager.h"
#include "PK_FontAsset.h"
#include "PK_SDLTextureAsset.h"
#include <SDL.h>

namespace PK {

class PK_SDLRenderManager : public PK_RenderManager
{
private:
    SDL_GLContext          m_pGLContext;

protected:
    SDL_Renderer          *m_pRenderer;
    SDL_Window            *m_pWindow;
    PK_TextureAsset       *m_pCurrentTexture;
    PK_eBlendMode          m_currentBlendMode;

public:
    PK_SDLRenderManager(const PK_String &sName);
    void OnInitialize();
	void OnUnInitialize();
	virtual void OnAfterRendererCreated() {}
	inline SDL_Renderer * GetRenderer() { return m_pRenderer; }
    inline SDL_Window * GetWindow() { return m_pWindow; }
    static PK_SDLRenderManager & GetSDLRenderManager();

    virtual void SetBlendMode(PK_eBlendMode blendMode) {}
    virtual void SetActiveTexture(PK_SDLTextureAsset &texture) {}
    virtual void SetupViewport();

protected:
    virtual void CreateInternalShaders() {};
};

}
#endif
