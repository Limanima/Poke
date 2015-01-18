#ifndef _PK_LINEARMOVEEFFECT_H_
#define _PK_LINEARMOVEEFFECT_H_

#include "PK_Effect.h"


namespace PK {

class PK_LinearMoveEffect : public PK_Effect
{
private:
    float m_fSpeed;
    float m_fAngleSin;
    float m_fAngleCos;
    PK_Vector3 m_vDirection;
    
public:
    PK_LinearMoveEffect(const PK_String &sName, float fSpeed, float fAngle);
    void Initialize(float fSpeed, float fAngle);
    void OnUpdate(const PK_GameTimer &time);

};

}

#endif
