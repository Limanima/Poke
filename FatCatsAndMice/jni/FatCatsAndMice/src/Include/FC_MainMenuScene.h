#ifndef _FCAM_FC_MAINMENUSCENE_H_
#define _FCAM_FC_MAINMENUSCENE_H_

#include <PokeEngine.h>
#include "FC_BaseScene.h"
#include "FC_Button.h"
#include "FC_Title.h"
#include "FC_Types.h"

class FC_ScoreBoard;


class FC_MainMenuScene : public FC_BaseScene
{ 
private:
    FC_Title            *m_pTitle;
    PK::PK_TimerControl *m_pTimer;
    PK::PK_TimerControl *m_pHideBoardsTimer;
    FC_ScoreBoard       *m_pScoreBoard;
    FC_eMainMenuType     m_Type;
    PK::PK_TimerControl *m_pAskLoginTimer;

public:
    FC_MainMenuScene();
    void OnInitialize();
    void OnOpen();
    void BtnPlay_Click(PK::PK_Object &sender);
    void BtnLeaderboards_Click(PK::PK_Object &sender);
    void ShowTimer_Timer(PK::PK_Object &sender);
    void HideBoardsTimer_Timer(PK::PK_Object &sender);
    void AskLoginTimer_Timer(PK::PK_Object &sender);
  
    inline void SetMenuType(FC_eMainMenuType type) { m_Type = type; }
    void OnUpdate(const PK::PK_GameTimer &time) ;

};

#endif
