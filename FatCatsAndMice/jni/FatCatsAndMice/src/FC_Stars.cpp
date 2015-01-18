#include <PokeEngine.h>
#include "FC_Stars.h"     

#define NUM_STARS 15

//  
FC_Stars::FC_Stars() :
  PK_Panel("FC_Stars")
{  
    m_iStarsSpawned = 0;
     //
    m_pStarsTimer = new PK::PK_TimerControl(GetName() + "_start_timer");
    m_pStarsTimer->SetAlarmTime(20);
    m_pStarsTimer->SetWithSnooze(true);
    m_pStarsTimer->SetEnabled(false);
    m_pStarsTimer->OnTimer.Set(new PK::PK_ObjectCallback<FC_Stars>(*this, &FC_Stars::StarsTimer_Timer));
    AddControl(m_pStarsTimer);

    // 
    m_pStarsContainer = new PK::PK_Panel(GetName() + "_starsContainer");
    AddControl(m_pStarsContainer);
}

//
void FC_Stars::OnLoad()
{
    m_pStarCatSpriteAsset = PK::PokeEngine.GetAssetManager().LoadSprite(FCAM_SPRITE_CAT_STAR, GetAssetContainerName());
    m_pMouseCatSpriteAsset = PK::PokeEngine.GetAssetManager().LoadSprite(FCAM_SPRITE_MOUSE_STAR, GetAssetContainerName());
}

//
void FC_Stars::OnUpdate(const PK::PK_GameTimer &time) 
{ 
    for(PK_ListIterator(PK_SceneControl *) itor = m_pStarsContainer->GetControls().Begin(); itor != m_pStarsContainer->GetControls().End(); itor++)
    {
        PK_2DSceneControl *pCtl = (PK_2DSceneControl *)(*itor);
        if (pCtl->GetTop() < -PK::PokeEngine.GetRenderManager().GetFrame().size.h / 2.0f)
        {
            pCtl->RemoveFromScene();
        }
    }

}

//
void FC_Stars::Show()
{
    SetVisible(true);
    m_iStarsSpawned = 0;
    m_pStarsTimer->SetEnabled(true);
}

//
void FC_Stars::StarsTimer_Timer(PK::PK_Object &sender)
{

    PK::PK_Sprite *pStar = new PK::PK_Sprite("fc_star");
    
    pStar->SetSprite((m_pStarsContainer->GetControls().GetCount() % 2 == 0? m_pStarCatSpriteAsset : m_pMouseCatSpriteAsset));

    int iJumpDirection = (PK::PK_RandomGenerator::GetRandNumber(2) == 0? -1: 1);
    // Randomizamos para a parabola n ser sempre igual 
    float forceX = (float)(5 + PK::PK_RandomGenerator::GetRandNumber(20));
    float forceY = (float)(30 + PK::PK_RandomGenerator::GetRandNumber(40));

    PK::PK_MotionEffect *m = new PK::PK_MotionEffect(GetName() + "_gravity", -10.0f, PK_Vector3(forceX * iJumpDirection, forceY, 0.0f));
    pStar->SetPosition(PK::PK_RandomGenerator::GetRandNumber(200) - 100.0f, 0.0f);
    pStar->AddEffect(*m);
    pStar->SetShadow(true, PK_Vector2(20.0f, 20.0f), FCAM_SHADOW_COLOR);
    m_pStarsContainer->AddControl(pStar);

    m_iStarsSpawned++;
    if (m_iStarsSpawned >= NUM_STARS)
    {
        m_pStarsTimer->SetEnabled(false);
    }
}