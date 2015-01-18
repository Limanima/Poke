#ifndef _PK_THREAD_H_
#define _PK_THREAD_H_

#include "PK_Object.h"

namespace PK {
    
    
class PK_Thread : public PK_Object
{
private:
    unsigned long long  m_lThreadId;
    void * m_thHandle;

public:
    PK_Thread(const PK_String &sName = "");
    ~PK_Thread();
    int WaitExit();
    void StartThread(int (*lpThreadFunction)(void*), void * param = NULL);
    inline unsigned long long  GetThreadId() { return m_lThreadId; }

    static void PokeEngineInitialize();
    static bool IsBackgroundThread();
    static unsigned long long  GetCurrentThreadId();
};
    
} // namespace

#endif
