#include "FC_Sign.h"     
#include "FC_Consts.h"
  
//
FC_Sign::FC_Sign(const PK::PK_String &sName, FC_eSide side, FC_eSignType signType) :
    PK::PK_Sprite(sName)
{      
    SetTypeName("FC_Sign");
    m_Side = side; 
    m_SignType = signType;
    SetShadow(true, PK_Vector2(20.0f, -20.0f), FCAM_SHADOW_COLOR);
     
    // Sign sprite
    m_pSignSprite = new PK::PK_Sprite(GetName() + "_signSprite"); 
    m_pSignSprite->SetShadow(true, PK_Vector2(20.0f, -20.0f), FCAM_SHADOW_COLOR);
    AddControl(m_pSignSprite);

    // Change script
    m_pSwithScript = new PK::PK_Script(GetName() + "_changeScript");
    m_pSwithScript->SetScriptAssetName(side == Side_Left? FCAM_SCRIPT_CHANGE_LEFT_SIGN : FCAM_SCRIPT_CHANGE_RIGHT_SIGN);
    AddControl(m_pSwithScript); 
       
    // Show script
    m_pShowScript = new PK::PK_Script(GetName() + "_showScript");
    m_pShowScript->SetScriptAssetName(side == Side_Left? FCAM_SCRIPT_SHOW_LEFT_SIGN : FCAM_SCRIPT_SHOW_RIGHT_SIGN);
    AddControl(m_pShowScript);

    // hide script 
    m_pHideScript = new PK::PK_Script(GetName() + "_hideScript");
    m_pHideScript->SetScriptAssetName(side == Side_Left? FCAM_SCRIPT_HIDE_LEFT_SIGN : FCAM_SCRIPT_HIDE_RIGHT_SIGN);
    AddControl(m_pHideScript);

    // 
    m_pClickZone = new PK::PK_Panel(GetName() + "_clickZone");
    m_pClickZone->OnClick.Set(new PK::PK_ObjectCallback<FC_Sign>(*this, &FC_Sign::ClickZone_Click));
   // m_pClickZone->SetBackgroundColor(PK_COLOR_RED);
    AddControl(m_pClickZone);
}
       
// 
void FC_Sign::OnLoad()
{
    m_pCatSign = PK::PokeEngine.GetAssetManager().LoadSprite(FCAM_SPRITESET_CAT_SIGN, GetAssetContainerName());
    m_pMouseSign = PK::PokeEngine.GetAssetManager().LoadSprite(FCAM_SPRITESET_MOUSE_SIGN, GetAssetContainerName());
    m_pPlaySign = PK::PokeEngine.GetAssetManager().LoadSprite(FCAM_SPRITESET_PLAY_SIGN, GetAssetContainerName());
    m_pLeaderboardsSign = PK::PokeEngine.GetAssetManager().LoadSprite(FCAM_SPRITESET_BOARDS_SIGN, GetAssetContainerName());
                        
    if (m_Side == Side_Left)
    {
        SetSprite(PK::PokeEngine.GetAssetManager().LoadSprite(FCAM_SPRITESET_LEFT_HAND, GetAssetContainerName()));
    }
    else 
    {
        SetSprite(PK::PokeEngine.GetAssetManager().LoadSprite(FCAM_SPRITESET_RIGHT_HAND, GetAssetContainerName()));
    }
    SetSign(m_SignType);
    m_pSignSprite->SetPosition(GetSpriteAsset()->GetCollisionBox(0).GetCenter() - GetPivot());
}

//
void FC_Sign::OnInitialize()
{
    
} 
   
//
void FC_Sign::Show(FC_eSignType type, int initialDelay)
{
    m_pShowScript->Break();
    m_pShowScript->SetVariable("SIGN_TYPE", (int)type);
    float fPos;
    switch(type)
    {   
        case SignType_Cat:
        case SignType_Mouse:
            fPos = (PK::PokeEngine.GetRenderManager().GetSafeFrame().size.w / 2) - 40.0f;
            break; 
        case SignType_Play:
        case SignType_Leaderboards:
            fPos = (PK::PokeEngine.GetRenderManager().GetSafeFrame().size.w / 2) - 80.0f;
            break;
    }

    if (m_Side == Side_Left) 
        fPos *=-1;

    m_pShowScript->SetVariable("POSITION", PK_Vector2(fPos, -360.0f));
    m_pShowScript->SetVariable("INITIAL_DELAY", initialDelay);
    m_pShowScript->Execute();
}

//
void FC_Sign::Hide()
{
    m_pHideScript->Break();
    m_pHideScript->Execute();
}

//
void FC_Sign::Switch(FC_eSignType type)
{
    m_pSwithScript->Break();
    m_pSwithScript->SetVariable("SIGN_TYPE", (int)type);
    m_pSwithScript->Execute();
}   
//     
void FC_Sign::SetSign(FC_eSignType signType)   
{ 
    m_SignType = signType;
    switch(signType)
    {
        case SignType_Cat:
            m_pSignSprite->SetSprite(m_pCatSign);
            break;
        case SignType_Mouse:
            m_pSignSprite->SetSprite(m_pMouseSign);
            break;
        case SignType_Play:
            m_pSignSprite->SetSprite(m_pPlaySign);
            break;
        case SignType_Leaderboards:
            m_pSignSprite->SetSprite(m_pLeaderboardsSign);
            break; 
        default:  
            break;
    }
    m_pClickZone->SetPosition(m_pSignSprite->GetPosition());
    m_pClickZone->SetSize(m_pSignSprite->GetSize());
}
 
//
void FC_Sign::SetCustomAttribute(const PK::PK_String &sName, PK::PK_tScriptValue1 &var)
{
	if (sName == "signType")
	{
        SetSign((FC_eSignType)var.GetValue_Int());
	}
}

//
void FC_Sign::ClickZone_Click(PK::PK_Object &sender)
{
    if (OnSignClick.HasCallback())
    {
        OnSignClick->Execute(*this);
    }
}