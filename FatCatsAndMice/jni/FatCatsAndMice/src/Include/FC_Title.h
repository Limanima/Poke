#ifndef _FCAM_TITLE_H_
#define _FCAM_TITLE_H_

#include <PokeEngine.h>

class FC_Title : public PK::PK_Panel
{ 
private:
	PK::PK_Panel * m_pLetteringPnl;
	PK::PK_Panel * m_pFloorPnl;
    bool m_ScoreSoundPlayed;

public:
    FC_Title(const PK::PK_String &sName);
    void OnInitialize();
    void Dismiss();
    void Show();
    void Collided(PK::PK_Body &body);
};

#endif
