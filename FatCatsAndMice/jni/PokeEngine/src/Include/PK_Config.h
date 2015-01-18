#ifndef _PK_CONFIG_H_
#define _PK_CONFIG_H_

#if defined(POKE_ANDROID) // Android
  #define POKE_SDL
  #define POKE_GLES
  #define PK_SUPPORTS_KEYBOARD  true
  #define PK_SUPPORTS_MOUSE     false
  #define PK_SUPPORTS_TOUCH     true
  #define PK_SDL_NET
#elif defined(POKE_IOS)  // iOS
  #define POKE_SDL
  #define POKE_GLES
  #define PK_SUPPORTS_KEYBOARD  true
  #define PK_SUPPORTS_MOUSE     false
  #define PK_SUPPORTS_TOUCH     true
  #define PK_SDL_NET
#elif defined (POKE_WINDOWS)  // Windows
  #define POKE_SDL
  #define POKE_GL
  #define PK_SUPPORTS_KEYBOARD  true
  #define PK_SUPPORTS_MOUSE     true
  #define PK_SUPPORTS_TOUCH     false
  #define PK_SDL_NET
#elif defined (POKE_WINPHONE)  // Windows phone
  #define POKE_SDL
  #define POKE_DX
  #define PK_SUPPORTS_KEYBOARD  true
  #define PK_SUPPORTS_MOUSE     true
  #define PK_SUPPORTS_TOUCH     false
  #define PK_USEVERTEXBUFFERS      
#else
  IMPLEMENTAR!!
#endif

#endif
