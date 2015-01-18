#include <sdl.h>
#include "PK_Timer.h"
#include "PK_Log.h"

namespace PK {

//    
PK_Timer::PK_Timer()
{
   Initialize(0,  false,  false);
}

//    
PK_Timer::PK_Timer(const PK_String &sName) :
  PK_Object(sName)
{
   Initialize(0,  false,  false);
}

//    
PK_Timer::PK_Timer(const PK_String &sName, int iTimeMSecs, bool bWithSNooze, bool bEnabled) :
  PK_Object(sName)
{
   Initialize(iTimeMSecs,  bWithSNooze,  bEnabled);
}

//
PK_Timer::~PK_Timer()
{
}

//
void PK_Timer::Initialize(int iTimeMSecs, bool bWithSNooze, bool bEnabled)
{
    SetTypeName("PK_Timer");
    Reset();
    m_uiAlarmTimeMsecs = iTimeMSecs;
    m_bWithSnooze = bWithSNooze;
    m_bEnabled = bEnabled;
}

//
void PK_Timer::Update()
{
    unsigned int uiCurrentTime;

    if (!m_bEnabled)
    {
      return;
    }

    // FIXME: funcionar sem ser com SDL
    uiCurrentTime = SDL_GetTicks();
    if (m_uiLastTimeMescs == -1)
    {
        m_uiLastTimeMescs = uiCurrentTime;
    }
    m_uiEllapsedMsecs = uiCurrentTime - m_uiLastTimeMescs;
    m_uiLastTimeMescs = uiCurrentTime;
    // Alarme? Ver se vai chamar callback
    if (m_bEnabled)
    {
        m_uiTotalEllapsedMescs += m_uiEllapsedMsecs;
        if (m_uiTotalEllapsedMescs > m_uiAlarmTimeMsecs)
        {
            m_uiEllapsedMsecs = m_uiTotalEllapsedMescs; 
            m_uiTotalEllapsedMescs = 0;
            m_bEnabled = m_bWithSnooze;
   
            if(OnTimer.HasCallback())
            {
                OnTimer->Execute(*this);
            }
        }
    }
}

//
void PK_Timer::Reset()
{
    m_uiEllapsedMsecs = 0;
    m_uiTotalEllapsedMescs = 0;
    m_uiLastTimeMescs = -1;
}

} // namespace