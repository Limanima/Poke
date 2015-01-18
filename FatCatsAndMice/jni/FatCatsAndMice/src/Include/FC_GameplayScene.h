#ifndef _FCAM_FC_GAMEPLAYSCENE_H_
#define _FCAM_FC_GAMEPLAYSCENE_H_

#include <PokeEngine.h>
#include "FC_BaseScene.h"
#include "FC_Button.h"
#include "FC_Actor.h"
#include "FC_Player.h"
#include "FC_Fire.h"
#include "FC_Hud.h"
#include "FC_ActorExit.h"
#include "FC_DogActor.h"
#include "FC_Sign.h"

class FC_Background;
class FC_Tutorial;

class FC_GameplayScene : public FC_BaseScene
{ 
private:

    int     m_iScore;
    float   m_fReleaseTime;
    float   m_fReleaseDecreaseTime;
    float   m_fAirResistance;
    float   m_fAirResistanceDecrease;
    float   m_fAirResistanceDecay;
    float   m_fMaxFallSpeed;
    FC_eGameplayState       m_State;
    PK::PK_TimerControl    *m_pLauchTimer;
    FC_Player              *m_pPlayer;
    FC_Fire                *m_pFire;
    FC_Hud                 *m_pHud;
    PK::PK_Panel           *m_pActorsContainer;
    FC_ActorExit           *m_pLeftExit;
    FC_ActorExit           *m_pRightExit;
    bool                    m_bCanControlActor;
    FC_Tutorial            *m_pTutorial;


public:
    FC_GameplayScene();
    void OnLoad();
    void OnInitialize();
    void OnUpdate(const PK::PK_GameTimer &time); 
    void OnOpen(); 
    void StartNewGame();
    void ShowTutorial();

private:
    FC_Actor * GetControllableActor();
    void SetToGameOver();
    void ActorDeliveredWithSuccess(FC_Actor &actor);
   
    // Eventos dos actores
    void Actor_Died(PK::PK_Object &sender);
    
    // Eventos das saidas
    void LeftExit_ActorExited(PK::PK_Object &sender);
    void RightExit_ActorExited(PK::PK_Object &sender);
 
    // Eventos do jogador
    void Player_FlickedLeft(PK::PK_Object &sender);
    void Player_FlickedRight(PK::PK_Object &sender);
    void Player_FlickEnded(PK::PK_Object &sender);
    
      // Eventos do timer 
    void LauchTimer_Timer(PK::PK_Object &sender);

    void LaunchActor();
    void ComputeMaxLevelSpeed();

    void SpamDeadActor(FC_eActorType actorType, const PK_Vector2 &vPosition, int iJumpDirection, bool playSound);
    void DogEnteredExit(FC_DogActor &dog, FC_ActorExit &exit);
    
    void EndTutorial();
public:
    float GetTopDogHouseBound();
    void Tutorial_Click(PK::PK_Object &sender);
    void OnEnterForeground();
};

#endif
