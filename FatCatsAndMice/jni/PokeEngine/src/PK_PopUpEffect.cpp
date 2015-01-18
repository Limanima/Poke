#include "PK_PopUpEffect.h"

namespace PK {
    
//
PK_PopUpEffect::PK_PopUpEffect(const PK_String &sName, float fSquashLimit, float fSpeed, float fDecay):
	PK_Effect(sName)
{
    Initialize(fSquashLimit, fSpeed, fDecay, PK_Vector3(1.0f, 1.0f, 1.0f));
}

//
PK_PopUpEffect::PK_PopUpEffect(const PK_String &sName, float fSquashLimit, float fSpeed, float fDecay, const PK_Vector3 &vTargetScale):
	PK_Effect(sName)
{
    Initialize(fSquashLimit, fSpeed, fDecay, vTargetScale);
}
    
//
void PK_PopUpEffect::Initialize(float fSquashLimit, float fSpeed, float fDecay, const PK_Vector3 &vTargetScale)
{
    SetTypeName("PK_PopUpEffect");
    m_fSquashLimit = m_fInitialSquashLimit = fSquashLimit;
    m_fDecay = fDecay;
    m_fSpeed = fSpeed;
    m_vTargetScale = vTargetScale;
    InternalReset();
}
    
//
void PK_PopUpEffect::OnUpdate(const PK_GameTimer &time)
{
    float fDelta = ((float)time.GetEllapsedTime() * m_fSpeed / 1000.0f) * m_iDirection;
    float x = m_vScale.x + fDelta;
    float y = m_vScale.y - fDelta;

    if (x < m_fSquashLimit)
    {
        m_iDirection *= -1;
        m_fSquashLimit += m_fDecay;
        x = m_fSquashLimit;
        y = (m_vTargetScale.y - m_fSquashLimit) + m_vTargetScale.y;
    }
    else
    if (y < m_fSquashLimit)
    {
        m_iDirection *= -1;
        m_fSquashLimit += m_fDecay;
        y = m_fSquashLimit;
        x = (m_vTargetScale.x - m_fSquashLimit) + m_vTargetScale.x;
    }
        
           
    m_vScale = PK_Vector3(x, y, m_vScale.z);

    if (m_fSquashLimit >= m_vTargetScale.x)
    {
        SetEnded(true);
        m_vScale = m_vTargetScale;
    }
}
    
//
void PK_PopUpEffect::InternalReset()
{
    PK_Effect::InternalReset();
    m_fSquashLimit = m_fInitialSquashLimit;
    m_iDirection = -1;
    m_vScale = m_vTargetScale;
}

}