#ifndef _PK_TIMERCONTROL_H_
#define _PK_TIMERCONTROL_H_

#include "PK_SceneControl.h"
#include "PK_Timer.h"

namespace PK {


class PK_TimerControl : public PK_SceneControl
{
  private:
    PK_Timer m_Timer;
  public:
    PK_Callback<PK::PK_IObjectCallback> OnTimer;
  
public:
    PK_TimerControl(const PK_String &sName = "");
    PK_TimerControl(const PK_String &sName, int iTimeMSecs, bool bWithSNooze, bool bEnabled);
    void InitializeInstance(int iTimeMSecs, bool bWithSNooze, bool bEnabled);
    void InitFromDataFileRecord(PK_DataFileRecord &record);
    void InternalUpdate(const PK_GameTimer &time);

    unsigned int GetEllapsedTime();
    void SetWithSnooze(bool bSnooze);
    void SetAlarmTime(unsigned int uiMsecs);
    void Reset();
    void SetEnabled(bool bEnabled);
   
private:
    void Timer_OnTimer(PK::PK_Object &sender);

};

}
#endif
