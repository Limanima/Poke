#include "PK_Mutex.h"
#include "PK_Exceptions.h"
#include <sdl.h>

namespace PK {

PK_Mutex::PK_Mutex(const PK_String &sName) :
   PK_Object(sName)
{
    SetTypeName("PK_Mutex");
    m_pHandle = NULL;
    m_bLocked = false;
}

//
PK_Mutex::~PK_Mutex()
{
    if (m_pHandle != NULL)
    {
        SDL_DestroyMutex((SDL_mutex*) m_pHandle);
    }
}

//
void PK_Mutex::Initialize()
{
    if (IsInitialized())
    {
        throw PK_SystemException("Cannot initialize mutex named '%' because it was already initialized.", __FILE__, __LINE__, GetName().c_str());
    }

    m_pHandle = (void *) SDL_CreateMutex();
    if (m_pHandle == NULL)
    {
        throw PK_SDLException(SDLLib_SDL, __FILE__, __LINE__);
    }
}

//
bool PK_Mutex::Lock()
{
    if (!IsInitialized())
    {
        throw PK_SystemException("Cannot lock Mutex named '%s' because it is not initialized. Use PK_Mutex::Initialize().", __FILE__, __LINE__, GetName().c_str());
    }

    if (m_bLocked)
    {
        return true;
    }

    if (SDL_LockMutex((SDL_mutex*) m_pHandle) < 0)
    {
        throw PK_SDLException(SDLLib_SDL, __FILE__, __LINE__);
    }
    m_bLocked = true;
    return true;
}
    
//
void PK_Mutex::Unlock()
{
    if (!IsInitialized())
    {
        throw PK_SystemException("Cannot lock Mutex named '%s' because it is not initialized. Use PK_Mutex::Initialize().", __FILE__, __LINE__, GetName().c_str());
    }

    if (!m_bLocked)
    {
        return;
    }

    if (SDL_UnlockMutex((SDL_mutex*) m_pHandle) < 0)
    {
        throw PK_SDLException(SDLLib_SDL, __FILE__, __LINE__);
    }
    m_bLocked = false;
}

} // namespace
#if 0
#if defined(POKE_IOS) || defined(POKE_ANDROID)
    #include <pthread.h>
    #define PK_POSIX_THREAD
#elif defined POKE_WINDOWS
    #define WINDOWS_MEAN_AND_LEAN
    #include <windows.h>
    #define PK_WINAPI_THREAD
#endif 

namespace PK {


PK_Mutex::PK_Mutex(const PK_String &sName) :
   PK_Object(sName)
{
    SetTypeName("PK_Mutex");
    m_bInitialized = false;
}

//
PK_Mutex::~PK_Mutex()
{
    if (m_bInitialized)
    {
#ifdef PK_WINAPI_THREAD
        CloseHandle((HANDLE)m_lMutexId);
#endif
        
#ifdef PK_POSIX_THREAD
        pthread_mutex_destroy(&m_lMutexId);
#endif
    }
}

//
void PK_Mutex::Initialize()
{
    if (IsInitialized())
    {
        throw PK_SystemException("Mutex named '%s' is already initialized.", __FILE__, __LINE__, GetName().c_str());
    }

#ifdef PK_WINAPI_THREAD
    HANDLE handle = CreateMutex(NULL, false, GetName().c_str());
    if (handle == NULL)
    {
        throw PK_SystemException("Error in CreateMutex() for mutex named '%s'. GetLastError()='%d'", 
            __FILE__, __LINE__, GetName().c_str(), GetLastError());
    }
    m_lMutexId = (long)handle;
#endif
    
#ifdef PK_POSIX_THREAD
    pthread_mutex_init(&m_lMutexId, NULL );
#endif
    m_bInitialized = true;
}

//
bool PK_Mutex::Lock()
{
    if (!IsInitialized())
    {
        return false;
        //throw PK_SystemException("Cannot lock Mutex named '%s' because it is not initialized. Use PK_Mutex::Initialize().", __FILE__, __LINE__, GetName().c_str());
    }
#ifdef PK_WINAPI_THREAD
    DWORD dwWaitResult = WaitForSingleObject((HANDLE)m_lMutexId, INFINITE); 
    return (dwWaitResult == WAIT_OBJECT_0);
#endif
    
#ifdef PK_POSIX_THREAD
    return (pthread_mutex_lock(&m_lMutexId) == 0);
#endif
}
    
//
void PK_Mutex::Unlock()
{
    if (!IsInitialized())
    {
        throw PK_SystemException("Cannot lock Mutex named '%s' because it is not initialized. Use PK_Mutex::Initialize().", __FILE__, __LINE__, GetName().c_str());
    }
#ifdef PK_WINAPI_THREAD
    ReleaseMutex((HANDLE)m_lMutexId);
#endif
    
#ifdef PK_POSIX_THREAD
    pthread_mutex_unlock(&m_lMutexId);
#endif
}
} // namespace

#endif  // 0
