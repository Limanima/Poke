#ifndef _PK_SDLEXCEPTION_H_
#define _PK_SDLEXCEPTION_H_

#include "PK_Exception.h"

namespace PK {

enum PK_eSDLLib
{
    SDLLib_SDL,
    SDLLib_SDL_Image,
    SDLLib_SDL_Mixer,
    SDLLib_SDL_Net,
};
    
class PK_SDLException : public PK_Exception
{

  public:
	PK_SDLException(const char * pszSourceFile, int iLineNumber);
    PK_SDLException(PK_eSDLLib sdlLibSource, const char * pszSourceFile, int iLineNumber);
};

}
#endif

