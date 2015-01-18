#ifndef _FCAM_SIGN_H_
#define _FCAM_SIGN_H_

#include <PokeEngine.h>
#include "FC_Types.h"

class FC_Sign: public PK::PK_Sprite
{ 
private:
     FC_eSignType        m_SignType;
     FC_eSide            m_Side;
     PK::PK_SpriteAsset *m_pCatSign;
     PK::PK_SpriteAsset *m_pMouseSign;
     PK::PK_SpriteAsset *m_pPlaySign;
     PK::PK_SpriteAsset *m_pLeaderboardsSign;
     PK::PK_Script      *m_pShowScript;
     PK::PK_Script      *m_pHideScript;
     PK::PK_Script      *m_pSwithScript;
     PK::PK_Sprite      *m_pSignSprite;
     PK::PK_Panel       *m_pClickZone;

public:
     PK::PK_Callback<PK::PK_IObjectCallback> OnSignClick;

public:
    FC_Sign(const PK::PK_String &sName, FC_eSide side, FC_eSignType signType);
    void OnLoad();
    void OnInitialize();
    void Show(FC_eSignType type, int initialDelay);
    void Hide();
    void Switch(FC_eSignType type);
    void SetSign(FC_eSignType signType);
	void SetCustomAttribute(const PK::PK_String &sName, PK::PK_tScriptValue1 &var);
    void ClickZone_Click(PK::PK_Object &sender);

    inline void SetClickEnabled(bool bEnabled) { m_pClickZone->SetEnabled(bEnabled); }
};

#endif
