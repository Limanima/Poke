#include <PokeEngine.h>
#include "FC_BaseScene.h"              
                                                                                                                                                                                                   
FC_BaseScene::FC_BaseScene(const PK::PK_String &sName) :
    PK::PK_Scene(sName)
{     
    m_pGame = (FC_Game*)&PK::PokeEngine.GetGame();

    // Sign da esquerda
    m_pLeftSign = new FC_Sign("fc_leftSign", Side_Left, SignType_Play);
    m_pLeftSign->SetPosition(-310.0f, -200.0f);
    m_pLeftSign->SetVisible(false);
    AddControl(m_pLeftSign); 
     
    // Sign da direita
    m_pRightSign = new FC_Sign("fc_rightSign", Side_Right, SignType_Leaderboards);
    m_pRightSign->SetPosition(310.0f, -200.0f);
    m_pRightSign->SetVisible(false);
    AddControl(m_pRightSign); 
} 
 
