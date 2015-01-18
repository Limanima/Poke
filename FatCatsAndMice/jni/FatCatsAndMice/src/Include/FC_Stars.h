#ifndef _FCAM_STARS_H_
#define _FCAM_STARS_H_

#include <PokeEngine.h>
#include "FC_Types.h"
#include "FC_Consts.h"

class FC_Stars: public PK::PK_Panel
{ 
    PK::PK_TimerControl *m_pStarsTimer;
    PK::PK_Panel        *m_pStarsContainer;
    PK::PK_SpriteAsset  *m_pStarCatSpriteAsset;
    PK::PK_SpriteAsset  *m_pMouseCatSpriteAsset;
    int m_iStarsSpawned;
public:
    FC_Stars();
    void OnLoad();
    void OnUpdate(const PK::PK_GameTimer &time);
    void Show();
    void StarsTimer_Timer(PK::PK_Object &sender);
    inline bool AreAllStarsOut() { return (m_pStarsContainer->GetControls().GetCount() == 0); }
};

#endif
