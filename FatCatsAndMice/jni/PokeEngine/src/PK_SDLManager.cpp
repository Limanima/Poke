#include "PK_Globals.h"
#include <sdl.h>
#include "PK_SDLManager.h"
#include "PK_SDLInputManager.h"
#include "PK_EventManager.h"

namespace PK {
    
//
PK_SDLManager::PK_SDLManager(const PK_String &sName) :
   PK_EventManager(sName)
{
    SetTypeName("PK_SDLManager");
    m_pInputManager = NULL;
}
   
//
PK_SDLManager::~PK_SDLManager()
{
    if (m_pInputManager != NULL)
    {
        m_pInputManager->Release();
        m_pInputManager = NULL;
    }
}
    
//
void PK_SDLManager::OnInitialize()
{
    PK_EventManager::OnInitialize();
   SDL_SetEventFilter(PK_SDLManager::HandleAppEvents, NULL);
}
    
//
void PK_SDLManager::OnUpdate(const PK_GameTimer &time)
{
    static SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (m_pInputManager != NULL && m_pInputManager->IsInputEvent(event))
        {
            m_pInputManager->AddEvent(event);
        }
     /*   else
        {
            switch(event.type)
            {
                case SDL_APP_DIDENTERBACKGROUND:
                    PokeEngine.OnGameEnteredBackground();
                    break;
     
                case SDL_APP_WILLENTERFOREGROUND:
                    PokeEngine.OnGameEnteredForeground();
                    break;
                    
                case SDL_APP_LOWMEMORY:
                    PokeEngine.OnLowMemoryDetected();
                    break;
                    
                case SDL_APP_TERMINATING:
                    PokeEngine.OnOsIssuedEndGame();
                    break;

                case SDL_WINDOWEVENT:
                    switch (event.window.event) 
                    {
                        case SDL_WINDOWEVENT_CLOSE:
                            PokeEngine.OnCloseGame();
                            break;
                        default:
                            break;
                    }
                    break;
                   
                default:
                    break;
           }
        }*/
    }

	PK_EventManager::OnUpdate(time);
}
    
void PK_SDLManager::SetSDLInputManager(PK_SDLInputManager *pManager)
{
    if (m_pInputManager != NULL)
    {
        m_pInputManager->Release();
    }
        
    m_pInputManager = pManager;
    if (m_pInputManager != NULL)
    {
        m_pInputManager->Grab();
    }
}
    
// static
int PK_SDLManager::HandleAppEvents(void *userdata, SDL_Event *pEvent)
{
    switch(pEvent->type)
    {
        case SDL_APP_WILLENTERBACKGROUND:
            PokeEngine.RespondToEnterBackground();
            break;
                
        case SDL_APP_DIDENTERFOREGROUND:
            PokeEngine.OnGameEnteredForeground();
			PokeEngine.GetEventManager().PostEvent(PK_EVENT_APP_ENTERED_FOREGROUND);
            break;
            
        case SDL_APP_LOWMEMORY:
            PokeEngine.OnLowMemoryDetected();
            break;
                
        case SDL_APP_TERMINATING:
            PokeEngine.OnOsIssuedEndGame();
            break;
                
        case SDL_WINDOWEVENT:
            switch (pEvent->window.event)
            {
                case SDL_WINDOWEVENT_CLOSE:
                    PokeEngine.OnCloseGame();
                    break;
                
                default:
                    break;
            }
            break;
                
        default:
            break;
    }
    
    return 1;
}
    
} // namespace
