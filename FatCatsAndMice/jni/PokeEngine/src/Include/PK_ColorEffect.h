#ifndef _PK_COLOREFFECT_H_
#define _PK_COLOREFFECT_H_

#include "PK_Effect.h"


namespace PK {
class PK_Effect;

class PK_ColorEffect : public PK_Effect
{
private:
    PK_Color m_StartColor;
    PK_Color m_EndColor;
    float m_fSpeed;
    bool m_bLoop;
    PK_Color m_finalColor;
    
public:
    PK_ColorEffect(const PK_String &sName, const PK_Color &startColor, const PK_Color &endColor, float fSpeed, bool bLoop);
    PK_ColorEffect(const PK_String &sName, const PK_Color &startColor, const PK_Color &endColor, float fSpeed, bool bLoop, const PK_Color finalColor);
    void OnUpdate(const PK_GameTimer &time);
    void InternalReset();

private:
    void Initialize(const PK_Color &startColor, const PK_Color &endColor, float fSpeed, bool bLoop, const PK_Color finalColor);

};

}

#endif
