#include "PK_SplashScene.h"
#include "PK_Sprite.h"
#include "PK_TimerControl.h"
#include "PK_Globals.h"
#include "PK_SceneManager.h"

namespace PK {
    // FIXME! ISto de splash devia era ser uma scene transition
    // porque assim podemos mostrar o splash quando esta a carregar o grupo
    // Como esta tambem funciona mas esta martelado
    // Se splash enabled, cria uma splash scene e mostra
PK_SplashScene::PK_SplashScene(const PK_String &sName) :
    PK_Scene(sName)
{
	SetTypeName("PK_SplashScene");
    
    // Timer
   /* m_pTimer = new PK_TimerControl(GetName() + "_timer", 1500, false, true);
    m_pTimer->OnTimer.Set(new PK_ObjectCallback<PK_SplashScene>(*this, &PK_SplashScene::EndTimer_Timer));
    AddControl(m_pTimer);
    */
    // Sprite
    m_pSprite = new PK_Sprite(GetName() + "_sprite");
    AddControl(m_pSprite);
}

//
void PK_SplashScene::EndTimer_Timer(PK_Object &sender)
{
  //  PokeEngine.GetSceneManager().OnSplashClosed();
}

//
void PK_SplashScene::SetSprite(const PK_String &sSpriteResourceName)
{
    m_pSprite->SetSpriteAssetName(sSpriteResourceName);
}

} // namespace
