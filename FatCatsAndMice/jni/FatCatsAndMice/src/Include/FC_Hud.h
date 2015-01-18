#ifndef _FCAM_HUD_H_
#define _FCAM_HUD_H_

#include <PokeEngine.h>
#include "FC_Game.h"

class FC_Hud: public PK::PK_Panel
{ 
private:
    FC_Game *m_pGame;
    PK::PK_Label           *m_pScoreLabel;
  
public:
    FC_Hud(const PK::PK_String &sName);
    void SetScore(int iScore);
    void Refresh();
    void Show();
  
};

#endif
