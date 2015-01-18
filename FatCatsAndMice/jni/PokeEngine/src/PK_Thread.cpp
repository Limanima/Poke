#include "PK_Thread.h"
#include "PK_Exceptions.h"
#include "PK_Log.h"

#define PK_SDL_THREAD

#ifndef PK_SDL_THREAD
    #if defined(POKE_IOS) || defined(POKE_ANDROID)
        #include <pthread.h>
        #define PK_POSIX_THREAD
        #define PK_THREAD_IN_TYPE pthread_t
    #elif defined(POKE_WINDOWS)
        #define WINDOWS_MEAN_AND_LEAN
        #include <windows.h>
        #define PK_WINAPI_THREAD
    #elif defined(POKE_WINPHONE)
        #include <thread>
        #define PK_CPP_THREAD
    #endif 
#endif

#ifdef PK_SDL_THREAD
#include <SDL.h>
#endif

namespace PK {

unsigned long long g_lMainThreadId;

#ifdef PK_SDL_THREAD

//
PK_Thread::PK_Thread(const PK_String &sName) :
    PK_Object(sName)
{
    m_thHandle = NULL;
}

//
PK_Thread::~PK_Thread()
{
    if (m_thHandle != NULL)
    {
        SDL_DetachThread((SDL_Thread*) m_thHandle);
    }
}

//
int PK_Thread::WaitExit()
{
    if (m_thHandle == NULL)
    {
        throw PK_SystemException("Cannot wait for thread '%s' to exit that was not started.", __FILE__, __LINE__, GetName().c_str());
    }
    int iRetCode;
    SDL_WaitThread((SDL_Thread*) m_thHandle, &iRetCode);
    m_thHandle = NULL; // SDL_WaitThread destroi o handle
    return iRetCode;
}

//
void PK_Thread::StartThread(int (*lpThreadFunction)(void*), void * param)
{
    if (m_thHandle != NULL)
    {
        throw PK_SystemException("Cannot start same thread twice. Thread name is '%s'.", __FILE__, __LINE__, GetName().c_str());
    }

    m_thHandle = (void*) SDL_CreateThread(lpThreadFunction, GetName().c_str(), param);
    if (m_thHandle == NULL) 
    {
        throw PK_SDLException(SDLLib_SDL, __FILE__, __LINE__);
    } 

}

// static
void PK_Thread::PokeEngineInitialize()
{
	g_lMainThreadId = PK_Thread::GetCurrentThreadId();
}

// static 
bool PK_Thread::IsBackgroundThread()
{
    return (g_lMainThreadId != GetCurrentThreadId());
}

// static 
unsigned long long  PK_Thread::GetCurrentThreadId()
{
    return SDL_GetThreadID(NULL);
}

#else // todos os outros casos, remover se SDL thread funcionar

#ifdef PK_POSIX_THREAD
unsigned long long ThreadIdToLong(pthread_t thread)
{
    pthread_t ptid = thread;
    uint64_t threadId = 0;
    memcpy(&threadId, &ptid, std::min(sizeof(threadId), sizeof(ptid)));
    return threadId;
}
#endif
    
    
PK_Thread::PK_Thread()
{
  m_lThreadId = 0;
  m_thHandle = NULL;
}

//
PK_Thread::~PK_Thread()
{
    #if defined(PK_WINAPI_THREAD)
    if(m_thHandle != NULL)
    {
       CloseHandle(m_thHandle);
    }
    #endif
}

//
void PK_Thread::WaitExit()
{
    throw PK_NotImplementedException("PK_Thread::WaitExit()", __FILE__, __LINE__);
}

//
void PK_Thread::StartThread(void (*lpThreadFunction)(void*), void * param)
{
  int ret = 0;
#if defined(PK_POSIX_THREAD)
  pthread_t t;
  ret = pthread_create((pthread_t *)&t, NULL, (void *(*)(void *))lpThreadFunction, (void *) param);
  m_lThreadId = ThreadIdToLong(t);
#elif defined(PK_WINAPI_THREAD)
  SECURITY_ATTRIBUTES threadAtrib;
  threadAtrib.nLength = sizeof (SECURITY_ATTRIBUTES);
  threadAtrib.lpSecurityDescriptor = NULL;
  threadAtrib.bInheritHandle = TRUE;
  
  m_thHandle = ::CreateThread(&threadAtrib, 0, (LPTHREAD_START_ROUTINE)lpThreadFunction, param, 0, (LPDWORD) &m_lThreadId);
  if (m_thHandle == NULL)
  {
    ret = GetLastError();
  }

#elif defined(PK_CPP_THREAD)
  std::thread thread = std::thread(lpThreadFunction, param);
  //m_lThreadId = thread.get_id();
  	throw PK_NotImplementedException("PK_Thread::StartThread()", __FILE__, __LINE__);

  
#elif
    IMPLEMENTAR!!
#endif

  if (ret != 0)
  {
    throw PK_SystemException("Thread could not be started. Error code = %d.", __FILE__, __LINE__, ret);
  }
}

// static
void PK_Thread::PokeEngineInitialize()
{
	g_lMainThreadId = PK_Thread::GetCurrentThreadId();
}

// static
unsigned long long PK_Thread::GetCurrentThreadId()
{
    #if defined(PK_POSIX_THREAD)
    return ThreadIdToLong(pthread_self());
    #elif defined(PK_WINAPI_THREAD)
    return ::GetCurrentThreadId();
    #elif defined(PK_CPP_THREAD)
    throw PK_NotImplementedException("PK_Thread::GetCurrentThreadId()", __FILE__, __LINE__);
    // return std::this_thread::get_id();
    #elif
    IMPLEMENTAR!!
    #endif
}


// static
bool PK_Thread::IsBackgroundThread()
{
#if defined(PK_POSIX_THREAD)
    return (g_lMainThreadId != ThreadIdToLong(pthread_self()));
#elif defined(PK_WINAPI_THREAD)
    return (g_lMainThreadId != GetCurrentThreadId());
#elif defined( PK_CPP_THREAD)
	throw PK_NotImplementedException("PK_Thread::IsBackgroundThread()", __FILE__, __LINE__);
    //return (g_lMainThreadId != std::this_thread::get_id());
#elif
    IMPLEMENTAR!!
#endif
}

//
bool PK_Thread::IsActive()
{
    if (m_lThreadId == 0)
    {
        return false;
    }

#if defined(PK_WINAPI_THREAD)
    DWORD result = WaitForSingleObject(m_thHandle, 0);
    return (result == WAIT_OBJECT_0);
#elif defined (PK_CPP_THREAD)
	throw PK_NotImplementedException("PK_Thread::IsActive()", __FILE__, __LINE__);
#endif
}

#endif // PK_SDL_THREAD
} // namespace
