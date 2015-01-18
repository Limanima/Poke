#include <PokeEngine.h>
#include "FC_Tutorial.h"     
#include "FC_Consts.h"
 
#define SHADOW_DEPTH  PK_Vector2(30.0f, -30.0f)

FC_Tutorial::FC_Tutorial() :
    PK::PK_2DSceneControl("fc_tutorial") 
{
 
    // Left hand
    m_pLeftHandSprite = new PK::PK_Sprite("fc_tutorialLeftHand");
    m_pLeftHandSprite->SetSpriteAssetName(FCAM_SPRITE_TUT_LEFT_HAND);
    m_pLeftHandSprite->SetShadow(true, SHADOW_DEPTH, FCAM_SHADOW_COLOR);
    AddControl(m_pLeftHandSprite);
    // Mice label
    m_pMiceLbl = new PK::PK_Label("fc_tutorial_catsLbl", "Mice");
    m_pMiceLbl->SetFont(FCAM_ASSET_FONT_DEFAULT);
    m_pMiceLbl->SetColor(PK_Color(PK_COLOR_RGBA_INT(110, 225, 240, 255)));
    m_pMiceLbl->SetScale(0.7f, 0.7f);
    m_pMiceLbl->SetPosition(45.0f, 130.0f);
    m_pMiceLbl->SetBackgroundColor(PK_Color(0.0f, 0.0f, 0.0f, 0.5f));
    m_pMiceLbl->SetBorder(10, 5, 10, 5);
    m_pLeftHandSprite->AddControl(m_pMiceLbl);
    // Mouse 
    m_pMouseSprite = new PK::PK_Sprite("fc_tutorialMouse");
    m_pMouseSprite->SetSpriteAssetName(FCAM_SPRITE_TUT_MOUSE);
    m_pMouseSprite->SetPosition(-200.0f, 250.0f);
    m_pMouseSprite->SetShadow(true, SHADOW_DEPTH, FCAM_SHADOW_COLOR);
    AddControl(m_pMouseSprite);

    // Right hand
    m_pRightHandSprite = new PK::PK_Sprite("fc_tutorialRightHand");
    m_pRightHandSprite->SetSpriteAssetName(FCAM_SPRITE_TUT_RIGHT_HAND);
    m_pRightHandSprite->SetShadow(true, SHADOW_DEPTH, FCAM_SHADOW_COLOR);
    AddControl(m_pRightHandSprite);
    // Cats label
    m_pCatsLbl = new PK::PK_Label("fc_tutorial_catsLbl", "Cats");
    m_pCatsLbl->SetFont(FCAM_ASSET_FONT_DEFAULT);
    m_pCatsLbl->SetColor(PK_Color(PK_COLOR_RGBA_INT(110, 225, 240, 255)));
    m_pCatsLbl->SetScale(0.7f, 0.7f);
    m_pCatsLbl->SetPosition(-50.0f, 130.0f);
    m_pCatsLbl->SetBackgroundColor(PK_Color(0.0f, 0.0f, 0.0f, 0.5f));
    m_pCatsLbl->SetBorder(10, 5, 10, 5);
    m_pRightHandSprite->AddControl(m_pCatsLbl);
    // Cat
    m_pCatSprite = new PK::PK_Sprite("fc_tutorialCat");
    m_pCatSprite->SetSpriteAssetName(FCAM_SPRITE_TUT_CAT);
    m_pCatSprite->SetPosition(200.0f, 250.0f);
    m_pCatSprite->SetShadow(true, SHADOW_DEPTH, FCAM_SHADOW_COLOR);
    AddControl(m_pCatSprite);

    // Script
    m_pScript = new PK::PK_Script(GetName() + "_rightHandScript");
    m_pScript->SetScriptAssetName(FCAM_SCRIPT_TUTORIAL);
    AddControl(m_pScript);
 
    // Tap to start label
    m_pContinueLbl = new PK::PK_Label("fc_tutorial_continueLbl", FCAM_TEXT_TAP_TO_START);
    m_pContinueLbl->SetFont(FCAM_ASSET_FONT_DEFAULT);
    m_pContinueLbl->SetColor(PK_Color(PK_COLOR_RGBA_INT(246, 255, 10, 255)));
    m_pContinueLbl->SetPosition(0.0f, 280.0f);
    m_pContinueLbl->SetBackgroundColor(PK_Color(0.0f, 0.0f, 0.0f, 0.5f));
    m_pContinueLbl->SetAutoSize(false);
    m_pContinueLbl->SetScale(0.7f, 0.7f);
    AddControl(m_pContinueLbl);

    SetDockStyle(PK::DockStyle_Fill);
    SetVisible(false);
}
 
//
void FC_Tutorial::Play()
{
    m_pContinueLbl->SetVisible(false);
    m_pRightHandSprite->SetVisible(false);
    m_pLeftHandSprite->SetVisible(false);
    m_pCatSprite->SetVisible(false);
    m_pMouseSprite->SetVisible(false);
    m_pScript->Execute();
    m_pContinueLbl->SetSize(PK::PokeEngine.GetRenderManager().GetFrame().size.w + 300.0f, 100.0f); // este + 300 e por causa so scale...
    
    SetVisible(true);
}

//
void FC_Tutorial::Stop()
{
    m_pScript->Break();
    SetVisible(false);
}

//
bool FC_Tutorial::CanEnd()
{
    return m_pContinueLbl->IsVisible();
}
