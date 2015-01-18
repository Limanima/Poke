#ifndef __B2PK_SETTINGS__
#define __B2PK_SETTINGS__

#ifdef b2_velocityThreshold
    #undef b2_velocityThreshold
#endif

class b2pk_Settings
{
public:
    static float m_b2_velocityThreshold;
};

#define b2_velocityThreshold (b2pk_Settings::m_b2_velocityThreshold)

#endif