#ifndef _PK_SLEEP_H_
#define _PK_SLEEP_H_

#ifdef POKE_WINDOWS
    #define WINDOWS_MEAN_AND_LEAN
    #include <windows.h>

    #define PK_Sleep(t) Sleep(t)
#endif

#endif

