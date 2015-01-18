#ifndef _PK_MUTEX_H_
#define _PK_MUTEX_H_
#include "PK_Object.h"

namespace PK {
    
class PK_Mutex : public PK_Object
{
    void * m_pHandle;
    bool   m_bLocked;

public:
    PK_Mutex(const PK_String &sName = "");
    ~PK_Mutex();
    void Initialize();
	bool Lock();
    void Unlock();

    inline bool IsInitialized() { return (m_pHandle != NULL); }
};

} // namespace

#if 0
#if defined(POKE_WINDOWS) || defined(POKE_WINPHONE)
#define WINDOWS_MEAN_AND_LEAN
    #include <windows.h>
    #define PK_WINAPI_THREAD
#else
    #include <pthread.h>
    #define PK_POSIX_THREAD
#endif

namespace PK {
    
class PK_Mutex : public PK_Object
{
private:
#ifdef PK_POSIX_THREAD
    pthread_mutex_t m_lMutexId;
#else
    DWORD  m_lMutexId;
#endif
    bool m_bInitialized;

public:
    PK_Mutex(const PK_String &sName = "");
    ~PK_Mutex();
    void Initialize();
	bool Lock();
    void Unlock();

    inline bool IsInitialized() { return m_bInitialized; }
};
    
} // namespace
#endif 

#endif
