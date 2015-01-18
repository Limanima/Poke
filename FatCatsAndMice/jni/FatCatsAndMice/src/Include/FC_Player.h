#ifndef _FCAM_PLAYER_H_
#define _FCAM_PLAYER_H_

#include <PokeEngine.h>

class FC_Player: public PK::PK_SceneControl
{ 


public:
    PK::PK_Callback<PK::PK_IObjectCallback> OnFlickedLeft;
    PK::PK_Callback<PK::PK_IObjectCallback> OnFlickedRight;
    PK::PK_Callback<PK::PK_IObjectCallback> OnTapped;
    PK::PK_Callback<PK::PK_IObjectCallback> OnFlickEnded;


public:
    FC_Player(const PK::PK_String &sName);
    void OnInitialize();
    void OnUpdate(const PK::PK_GameTimer &time); 

};

#endif
