#ifndef _FCAM_BASESCENE_H_
#define _FCAM_BASESCENE_H_

#include <PokeEngine.h>
#include "FC_Button.h"
#include "FC_Game.h"
#include "FC_Sign.h"

class FC_BaseScene : public PK::PK_Scene
{ 
private:
    FC_Game *m_pGame;

protected:
    FC_Sign *m_pLeftSign;
    FC_Sign *m_pRightSign;

public:
    FC_BaseScene(const PK::PK_String &sName);
    FC_GameSession & GetSession() { return GetGame().GetSession(); }
    FC_GameSettings & GetSettings() { return GetGame().GetSettings(); }
    FC_Game & GetGame() { return FC_Game::GetInstance();}
private:
};

#endif
