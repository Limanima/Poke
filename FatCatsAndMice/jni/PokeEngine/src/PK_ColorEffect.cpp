#include "PK_ColorEffect.h"

namespace PK {
    
//
PK_ColorEffect::PK_ColorEffect(const PK_String &sName, const PK_Color &startColor, const PK_Color &endColor, float fSpeed, bool bLoop):
	PK_Effect(sName)
{
    Initialize(startColor, endColor, fSpeed, bLoop, endColor);
}
    
//
PK_ColorEffect::PK_ColorEffect(const PK_String &sName, const PK_Color &startColor, const PK_Color &endColor, float fSpeed, bool bLoop, const PK_Color finalColor):
    PK_Effect(sName)
{
    Initialize(startColor, endColor, fSpeed, bLoop, finalColor);
}
    
//
void PK_ColorEffect::Initialize(const PK_Color &startColor, const PK_Color &endColor, float fSpeed, bool bLoop, const PK_Color finalColor)
{
    SetTypeName("PK_ColorEffect");
    m_StartColor = startColor;
    m_EndColor = endColor;
    m_Color = startColor;
    m_fSpeed = fSpeed;
    m_bLoop = bLoop;
    m_finalColor = finalColor;
}
    
//
void PK_ColorEffect::OnUpdate(const PK_GameTimer &time)
{
    float fSpeed = m_fSpeed * time.GetEllapsedTime() / 1000.0f;
    m_Color.r += (m_EndColor.r - m_StartColor.r) * fSpeed;
    m_Color.g += (m_EndColor.g - m_StartColor.g) * fSpeed;
    m_Color.b += (m_EndColor.b - m_StartColor.b) * fSpeed;
    m_Color.a += (m_EndColor.a - m_StartColor.a) * fSpeed;
    
    // If increases
    if (m_EndColor.r > m_StartColor.r && m_Color.r > m_EndColor.r)
    {
        m_Color.r = m_EndColor.r;
    }
    
    if (m_EndColor.g > m_StartColor.g && m_Color.g > m_EndColor.g)
    {
        m_Color.g = m_EndColor.g;
    }
    
    if (m_EndColor.b > m_StartColor.b && m_Color.b > m_EndColor.b)
    {
        m_Color.b = m_EndColor.b;
    }
    
    if (m_EndColor.a > m_StartColor.a && m_Color.a > m_EndColor.a)
    {
        m_Color.a = m_EndColor.a;
    }
    
    // If decreases
    if (m_EndColor.r < m_StartColor.r && m_Color.r < m_EndColor.r)
    {
        m_Color.r = m_EndColor.r;
    }
    
    if (m_EndColor.g < m_StartColor.g && m_Color.g < m_EndColor.g)
    {
        m_Color.g = m_EndColor.g;
    }
     
    if (m_EndColor.b < m_StartColor.b && m_Color.b < m_EndColor.b)
    {
        m_Color.b = m_EndColor.b;
    }
    
    if (m_EndColor.a < m_StartColor.a && m_Color.a < m_EndColor.a)
    {
        m_Color.a = m_EndColor.a;
    }
    
    if (m_EndColor == m_Color)
    {
        if (m_bLoop)
        {
            PK_Color saveColor = m_EndColor;
            m_EndColor = m_StartColor;
            m_StartColor = saveColor;
            m_Color = m_StartColor;
        }
        else
        {
            SetEnded(true);
            m_Color = m_finalColor;
        }
    }
}
    
//
void PK_ColorEffect::InternalReset()
{
    m_Color = m_StartColor;
    PK_Effect::InternalReset();
}

}