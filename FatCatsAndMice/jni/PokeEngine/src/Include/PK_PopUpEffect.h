#ifndef _PK_POPUPEFFECT_H_
#define _PK_POPUPEFFECT_H_

#include "PK_Effect.h"
#include "PK_Vector3.h"

namespace PK {

class PK_PopUpEffect : public PK_Effect
{
private:
    float m_fInitialSquashLimit;
    float m_fSquashLimit;
    float m_fDecay; 
    float m_fSpeed;
    int m_iDirection;
    PK_Vector3 m_vTargetScale;
    
public:
    PK_PopUpEffect(const PK_String &sName, float fSquashLimit, float fSpeed, float fDecay);
    PK_PopUpEffect(const PK_String &sName, float fSquashLimit, float fSpeed, float fDecay, const PK_Vector3 &vTargetScale);
    void OnUpdate(const PK_GameTimer &time);
    void InternalReset();

private:
    void Initialize(float fSquashLimit, float fSpeed, float fDecay, const PK_Vector3 &vTargetScale);
};

}

#endif
