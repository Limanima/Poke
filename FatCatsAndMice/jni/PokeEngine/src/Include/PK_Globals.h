#ifndef _PK_GLOBALS_H_
#define _PK_GLOBALS_H_

#include "PK_PokeEngine.h"

#ifdef DECLARE_POKE_VARS
#define EXTERNAL 
#else
#define EXTERNAL extern
#endif

namespace PK {
    
EXTERNAL PK_PokeEngine PokeEngine;

} // namespace

#endif
