#include "PK_ButtonPressEffect.h"
#include "PK_Globals.h"

namespace PK {
    
#define STATE_UP   0
#define STATE_DOWN 1

//
PK_ButtonPressEffect::PK_ButtonPressEffect(const PK_String &sName, float fDepth, int iDowntime):
	PK_Effect(sName)
{
    SetTypeName("PK_ButtonPressEffect");
    m_fDepth = fDepth;
    m_iState = STATE_UP;
    m_Timer.SetAlarmTime(iDowntime);
    m_Timer.SetEnabled(false);
    m_Timer.SetWithSnooze(false);
    m_Timer.OnTimer.Set(new PK::PK_ObjectCallback<PK_ButtonPressEffect>(*this, &PK_ButtonPressEffect::Timer_OnTimer));
}
    
//
void PK_ButtonPressEffect::OnUpdate(const PK_GameTimer &time)
{
  if (m_iState == STATE_UP)
  {
      m_iState = STATE_DOWN;
      m_vPositionDelta.y = m_fDepth;
      m_Timer.SetEnabled(true);
  }
  else
  {
      m_vPositionDelta.y = 0.0f;
      m_Timer.Update();
  }
}

//
void PK_ButtonPressEffect::Timer_OnTimer(PK::PK_Object &sender)
{
    m_vPositionDelta.y = -m_fDepth;
    SetEnded(true);
}

//
void PK_ButtonPressEffect::Reset()
{
   m_iState = STATE_UP;
   m_Timer.SetEnabled(false);
   m_Timer.Reset();
}

}