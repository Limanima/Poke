#include "PK_MotionEffect.h"
#include "PK_Consts.h"
#include "PK_Vector2.h"

namespace PK {
//
PK_MotionEffect::PK_MotionEffect(const PK_String &sName, const PK_Vector3 &m_vInitialSpeed):
	PK_Effect(sName)
{
    SetTypeName("PK_MotionEffect");
    PK_Vector2 gravity = PK_DEFAULT_GRAVITY;
    Reset(gravity.y, m_vInitialSpeed);
}

//
PK_MotionEffect::PK_MotionEffect(const PK_String &sName, float fGravity, const PK_Vector3 &m_vInitialSpeed):
	PK_Effect(sName)
{
    Reset(fGravity, m_vInitialSpeed);
}

//
void PK_MotionEffect::OnUpdate(const PK_GameTimer &time)
{
    m_t += ((float)time.GetEllapsedTime() / 100.0f);
            
    float y = ((m_vInitialSpeed.y * m_t) + 0.5f * (m_fGravity) * (m_t * m_t));

    float x = m_vInitialSpeed.x * m_t;
    m_vPositionDelta = PK_Vector3((x - m_vPrev.x), (y - m_vPrev.y), 0.0f);
    m_vPrev = PK_Vector3(x, y, 0.0f);

    m_vCurrentSpeed = PK_Vector3(m_vInitialSpeed.x, (m_vInitialSpeed.y + (m_fGravity * m_t)), 0.0f);
}

//
void PK_MotionEffect::Reset(const PK_Vector3 &vInitialSpeed)
{
    Reset(m_fGravity, vInitialSpeed);
}

//
void PK_MotionEffect::Reset(float fGravity, const PK_Vector3 &vInitialSpeed)
{
    SetPersistent(true);
    m_fGravity = fGravity;
    m_vInitialSpeed = vInitialSpeed;
    m_t = 0.0f;
    m_vPrev = PK_Vector3(0.0f, 0.0f, 0.0f);
    m_vCurrentSpeed = PK_Vector3(0.0f, 0.0f, 0.0f);
}
}