#ifndef _FCAM_TUTORIAL_H_
#define _FCAM_TUTORIAL_H_

#include <PokeEngine.h>

class FC_Tutorial: public PK::PK_2DSceneControl
{ 
private:
    PK::PK_Script *m_pScript;
    PK::PK_Sprite *m_pLeftHandSprite;
    PK::PK_Sprite *m_pRightHandSprite;
    PK::PK_Label  *m_pContinueLbl;
    PK::PK_Label  *m_pCatsLbl;
    PK::PK_Label  *m_pMiceLbl;
    PK::PK_Sprite *m_pCatSprite;
    PK::PK_Sprite *m_pMouseSprite;

public:
    FC_Tutorial();
    void Play();
    void Stop();
    void Tutorial_Click(PK::PK_Object &sender);
    bool CanEnd();
};

#endif
