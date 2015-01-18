#ifndef _PK_TIMER_H_
#define _PK_TIMER_H_

#include "PK_Object.h"
#include "PK_Callback.h"
#include "PK_ObjectCallback.h"

namespace PK {
    
class PK_Timer : public PK_Object
{
private:
    unsigned int  m_uiEllapsedMsecs;
    unsigned int  m_uiTotalEllapsedMescs;
    unsigned int  m_uiLastTimeMescs;
    unsigned int  m_uiAlarmTimeMsecs;
    bool          m_bWithSnooze;
    bool          m_bEnabled;
public:
    PK_Callback<PK::PK_IObjectCallback> OnTimer;

public:
    PK_Timer();
    PK_Timer(const PK_String &sName);
    PK_Timer(const PK_String &sName, int iTimeMSecs, bool bWithSNooze, bool bEnabled);
    ~PK_Timer();
    void Update();
    void Reset();
private:
    void Initialize(int iTimeMSecs, bool bWithSNooze, bool bEnabled);

public:
    inline unsigned int GetEllapsedTime() const { return m_uiEllapsedMsecs; }
    inline void SetEllapsedTime(unsigned int uiEllapsed) { m_uiEllapsedMsecs = uiEllapsed; }
    inline void SetWithSnooze(bool bSnooze) { m_bWithSnooze = bSnooze; }
    inline void SetAlarmTime(unsigned int uiMsecs) { m_uiAlarmTimeMsecs = uiMsecs; }
    inline void SetEnabled(bool bEnabled) { m_bEnabled = bEnabled; }
};
    
} // namespace

#endif
