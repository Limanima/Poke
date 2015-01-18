#ifndef _PK_MOTIONFFECT_H_
#define _PK_MOTIONFFECT_H_

#include "PK_Effect.h"


namespace PK {

class PK_MotionEffect : public PK_Effect
{
private:
    float m_fGravity;
    float m_t;
    PK_Vector3 m_vInitialSpeed;
    PK_Vector3 m_vPrev;
    PK_Vector3 m_vCurrentSpeed;

public:
    PK_MotionEffect(const PK_String &sName, const PK_Vector3 &m_vInitialSpeed);
    PK_MotionEffect(const PK_String &sName, float fGravity, const PK_Vector3 &m_vInitialSpeed);
    void OnUpdate(const PK_GameTimer &time);
    void Reset(const PK_Vector3 &vInitialSpeed);
    void Reset(float fGravity, const PK_Vector3 &vInitialSpeed);

    inline PK_Vector3 GetVelocity() { return m_vCurrentSpeed; }

};

}

#endif
