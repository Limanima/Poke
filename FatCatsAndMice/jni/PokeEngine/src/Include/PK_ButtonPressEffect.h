#ifndef _PK_BUTTONPRESSEFFECT_H_
#define _PK_BUTTONPRESSEFFECT_H_

#include "PK_Effect.h"

namespace PK {

class PK_Timer;

class PK_ButtonPressEffect : public PK_Effect
{
private:
    float m_fDepth;
    int   m_iState;
    PK_Timer m_Timer;

public:
    PK_ButtonPressEffect(const PK_String &sName, float fDepth, int iDowntime);
    void OnUpdate(const PK_GameTimer &time);
    void Timer_OnTimer(PK::PK_Object &sender);
    void Reset();
};

}

#endif
