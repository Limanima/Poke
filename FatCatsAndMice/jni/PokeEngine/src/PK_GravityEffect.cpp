#include "PK_GravityEffect.h"

namespace PK {
    
//
PK_GravityEffect::PK_GravityEffect(const PK_String &sName, float fGravity, float fInitialSpeed):
	PK_Effect(sName)
{
    Initialize(fGravity, fInitialSpeed);
}
    

//
void PK_GravityEffect::Initialize(float fGravity, float fInitialSpeed)
{
    SetTypeName("PK_GravityEffect");
    m_fInitialSpeed = fInitialSpeed;
    m_fGravity = fGravity;
    m_t = 0;
    m_fPrev = 0;
}
    
//
void PK_GravityEffect::OnUpdate(const PK_GameTimer &time)
{
    m_t += (time.GetEllapsedTime() / 100);
            
    float y = (float)((m_fInitialSpeed * m_t) - 0.5f * m_fGravity * (m_t * m_t));
    m_vPositionDelta = PK_Vector3(0.0f, -(y -m_fPrev), 0.0f);
    m_fPrev = y;
}


}