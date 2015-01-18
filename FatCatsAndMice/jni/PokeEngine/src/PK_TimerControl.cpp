#include "PK_TimerControl.h"

namespace PK { 

//
PK_TimerControl::PK_TimerControl(const PK_String &sName) :
  PK_SceneControl(sName)
{
    InitializeInstance(1000, false, false);
}

//
PK_TimerControl::PK_TimerControl(const PK_String &sName, int iTimeMSecs, bool bWithSNooze, bool bEnabled) :
  PK_SceneControl(sName)
{
    InitializeInstance(iTimeMSecs, bWithSNooze, bEnabled);
}

//
void PK_TimerControl::InitializeInstance(int iTimeMSecs, bool bWithSNooze, bool bEnabled)
{
    PK_SceneControl::SetTypeName("PK_TimerControl");
    m_Timer.SetAlarmTime(iTimeMSecs);
    m_Timer.SetWithSnooze(bWithSNooze);
    m_Timer.SetEnabled(bEnabled);
    m_Timer.OnTimer.Set(new PK::PK_ObjectCallback<PK_TimerControl>(*this, &PK_TimerControl::Timer_OnTimer));
}

//
void PK_TimerControl::InitFromDataFileRecord(PK_DataFileRecord &record)
{
    PK_SceneControl::InitFromDataFileRecord(record);
}


// Chama o Update do proprio e dos filhos
void PK_TimerControl::InternalUpdate(const PK_GameTimer &time)
{
    PK_SceneControl::InternalUpdate(time);
    m_Timer.Update();
}

//
unsigned int PK_TimerControl::GetEllapsedTime()
{
    return m_Timer.GetEllapsedTime();
}

//
void PK_TimerControl::SetWithSnooze(bool bSnooze)
{
    m_Timer.SetWithSnooze(bSnooze);
}

//
void PK_TimerControl::SetAlarmTime(unsigned int uiMsecs)
{
    m_Timer.SetAlarmTime(uiMsecs);
}


//
void PK_TimerControl::Reset()
{
    m_Timer.Reset();
}

//
void PK_TimerControl::SetEnabled(bool bEnabled)
{
  PK_SceneControl::SetEnabled(bEnabled);
  m_Timer.Reset();
  m_Timer.SetEnabled(bEnabled);
}

//
void PK_TimerControl::Timer_OnTimer(PK::PK_Object &sender)
{
    if (OnTimer.HasCallback())
    {
        OnTimer->Execute(*this);
    }
}
} // namespace
