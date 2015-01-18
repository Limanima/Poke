#ifndef _FCAM_GLOBALHUD_H_
#define _FCAM_GLOBALHUD_H_

#include <PokeEngine.h>

class FC_GlobalHUD: public PK::PK_DrawableComponent
{ 
private:
	PK::PK_Sprite *m_pSoundBtn;
	PK::PK_Sprite *m_pLoginBtn;

public:
    FC_GlobalHUD();
	~FC_GlobalHUD();
	void OnInitialize();

	void SoundBtn_Click(PK::PK_Object &sender);
	void LoginBtn_Click(PK::PK_Object &sender);
	void OnPlayerLoginStatusChanged();
    void Refresh();
};

#endif
