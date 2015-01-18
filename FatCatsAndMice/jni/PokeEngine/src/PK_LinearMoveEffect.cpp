#include "PK_LinearMoveEffect.h"
#include "PK_MathHelper.h"

namespace PK {


//
PK_LinearMoveEffect::PK_LinearMoveEffect(const PK_String &sName, float fSpeed, float fAngle):
	PK_Effect(sName)
{
    Initialize(fSpeed, fAngle);
}
    

//
void PK_LinearMoveEffect::Initialize(float fSpeed, float fAngle)
{
    SetTypeName("PK_LinearMoveEffect");
    m_fSpeed = fSpeed;
    m_fAngleSin = (float)sin(PK_MathHelper::DegreesToRadians(fAngle));
    m_fAngleCos = (float)cos(PK_MathHelper::DegreesToRadians(fAngle));
    m_vDirection = PK_Vector3((float)m_fAngleCos, -(float)m_fAngleSin, 0.0f);
}
    
//
void PK_LinearMoveEffect::OnUpdate(const PK_GameTimer &time)
{
    float speed = m_fSpeed * time.GetEllapsedTime() / 10;
    m_vPositionDelta = m_vDirection * speed;
}


}