#ifndef _PK_OPENGL_H_
#define _PK_OPENGL_H_

#include "PK_Config.h"

#ifdef POKE_GL
	#define WINDOWS_MEAN_AND_LEAN
	#include <windows.h>
	#include <gl/gl.h>
#endif

#ifdef POKE_GLES 
  #ifdef POKE_SDL
	#include <SDL_opengles2.h>
  #endif
#endif

#endif
