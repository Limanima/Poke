#ifndef _PK_SDLMANAGER_H_
#define _PK_SDLMANAGER_H_

#include "PK_EventManager.h"
#include <sdl.h>

namespace PK {
    
class PK_SDLInputManager;

// O SDL necessita de um manager proprio, isto porque e necessario fazer SDL_PollEvent em todos os loops
class PK_SDLManager : public PK_EventManager
{
private:
    PK_SDLInputManager * m_pInputManager;
    bool                 m_bInitialized;
    
public:
    PK_SDLManager(const PK_String &sName);
    ~PK_SDLManager();
    void OnInitialize();
    void OnUpdate(const PK_GameTimer &time);
    void SetSDLInputManager(PK_SDLInputManager *pManager);

private:
    inline static int HandleAppEvents(void *userdata, SDL_Event *event);
};

}
#endif