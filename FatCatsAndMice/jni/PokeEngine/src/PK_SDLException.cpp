#include "PK_SDLException.h"
#include "PK_Config.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#ifdef PK_SDL_NET
  #include <SDL_net.h>
#endif

namespace PK {

PK_SDLException::PK_SDLException(const char * pszSourceFile, int iLineNumber) :
  PK_Exception("", pszSourceFile, iLineNumber)
{
	SetMessage(SDL_GetError());
}
    
PK_SDLException::PK_SDLException(PK_eSDLLib sdlLibSource, const char * pszSourceFile, int iLineNumber) :
    PK_Exception("", pszSourceFile, iLineNumber)
{
    switch(sdlLibSource)
    {
        case SDLLib_SDL:
            SetMessage(SDL_GetError());
            break;
            
        case SDLLib_SDL_Mixer:
            SetMessage(Mix_GetError());
            break;
            
        case SDLLib_SDL_Image:
            SetMessage(IMG_GetError());
            break;

#ifdef PK_SDL_NET
        case SDLLib_SDL_Net:
            SetMessage(SDLNet_GetError());
            break;
#endif
        default:
            break;
            
    }
}

} // namespace
