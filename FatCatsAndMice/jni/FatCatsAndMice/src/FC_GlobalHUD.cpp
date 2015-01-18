#include "FC_GlobalHUD.h" 
#include "FC_Consts.h" 
#include "FC_GlobalHUD.h"
#include "FC_Game.h"

#define FRAME_IDX_SOUNDBTN_ON   0
#define FRAME_IDX_SOUNDBTN_OFF  1
 
#define FRAME_IDX_LOGINBTN_ON   0
#define FRAME_IDX_LOGINBTN_OFF  1

//  
FC_GlobalHUD::FC_GlobalHUD() :
    PK::PK_DrawableComponent("_fc_global_hud_")
{  
	// Botao para controlar o som
	m_pSoundBtn = new PK::PK_Sprite(GetName() + "_soundBtn");
	m_pSoundBtn->OnClick.Set(new PK::PK_ObjectCallback<FC_GlobalHUD>(*this, &FC_GlobalHUD::SoundBtn_Click));
	m_pSoundBtn->SetSpriteAssetName(FCAM_SPRITE_SOUNDBTN);
	m_pSoundBtn->SetWithAnimation(false);
  	m_pSoundBtn->SetParentAlignment(PK::ParentAlignment_Right | PK::ParentAlignment_Bottom);
    m_pSoundBtn->SetPadding(5.0f);
	GetScene().AddControl(m_pSoundBtn);

	// Botao para login/logout
	m_pLoginBtn = new PK::PK_Sprite(GetName() + "_loginBtn");
    m_pLoginBtn->OnClick.Set(new PK::PK_ObjectCallback<FC_GlobalHUD>(*this, &FC_GlobalHUD::LoginBtn_Click));
	m_pLoginBtn->SetSpriteAssetName(FCAM_SPRITE_LOGINBTN);
	m_pLoginBtn->SetWithAnimation(false);
  	m_pLoginBtn->SetParentAlignment(PK::ParentAlignment_Left | PK::ParentAlignment_Bottom);
    m_pLoginBtn->SetPadding(5.0f);
    GetScene().AddControl(m_pLoginBtn);
}

//
FC_GlobalHUD::~FC_GlobalHUD()
{
			
}

//
void FC_GlobalHUD::OnInitialize()
{
    PK::PK_DrawableComponent::OnInitialize();
    m_pLoginBtn->SetVisible(PK::PK_Environment::IsAndroid());
	Refresh();
}

//  
void FC_GlobalHUD::SoundBtn_Click(PK::PK_Object &sender)
{
	if (PK::PokeEngine.GetAudioManager().IsMuted())
	{
		PK::PokeEngine.GetAudioManager().UnMute();
        FC_Game::GetInstance().GetSession().SetAudioOn(true);
	}
	else
	{
		PK::PokeEngine.GetAudioManager().Mute();
        FC_Game::GetInstance().GetSession().SetAudioOn(false);
	}
    Refresh();
    FC_Game::GetInstance().GetSession().Save();
}

//
void FC_GlobalHUD::LoginBtn_Click(PK::PK_Object &sender)
{
	if (PK::PokeEngine.GetPlayer().IsAuthenticated())
	{
        PK::PokeEngine.GetPlayer().SignOut();
	}
	else
	{
        PK::PokeEngine.GetPlayer().Authenticate(true);
	}
}
 
//
void FC_GlobalHUD::OnPlayerLoginStatusChanged()  
{
	Refresh();
}

//
void FC_GlobalHUD::Refresh()
{
    // Login button
 	if (PK::PokeEngine.GetPlayer().IsAuthenticated())
	{
		m_pLoginBtn->SetCurrentFrame(FRAME_IDX_LOGINBTN_OFF);
	}
	else
	{
		m_pLoginBtn->SetCurrentFrame(FRAME_IDX_LOGINBTN_ON);
	}

    // Sound button
    if (PK::PokeEngine.GetAudioManager().IsMuted())
	{
		m_pSoundBtn->SetCurrentFrame(FRAME_IDX_SOUNDBTN_OFF);
	}
	else
	{
		m_pSoundBtn->SetCurrentFrame(FRAME_IDX_SOUNDBTN_ON);
	}
}

