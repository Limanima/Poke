#ifndef _FCAM_FIRE_H_
#define _FCAM_FIRE_H_

#include <PokeEngine.h>

class FC_Fire: public PK::PK_Sprite
{ 
    PK::PK_Panel *m_pCollidingZone;

public:
    FC_Fire(const PK::PK_String &sName);
    void ActorCollided(PK::PK_Body &body);
};

#endif
