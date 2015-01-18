#ifndef _PK_GRAVITYEFFECT_H_
#define _PK_GRAVITYEFFECT_H_

#include "PK_Effect.h"


namespace PK {

class PK_GravityEffect : public PK_Effect
{
private:
    float m_fGravity;
    double m_t;
    float m_fInitialSpeed;
    float m_fPrev;
    
public:
    PK_GravityEffect(const PK_String &sName, float fGravity, float fInitialSpeed);
    void OnUpdate(const PK_GameTimer &time);

private:
    void Initialize(float fGravity, float fInitialSpeed);

};

}

#endif
