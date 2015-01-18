#ifndef _FCAM_SCOREBOARD_H_
#define _FCAM_SCOREBOARD_H_

#include <PokeEngine.h>
#include "FC_Stars.h"

class FC_ScoreBoard: public PK::PK_2DSceneControl
{ 
private:
    PK::PK_Panel           *m_pContainer;
    PK::PK_Label           *m_pScoreLabel;
    PK::PK_Label           *m_pScoreValLabel;
    PK::PK_Panel           *m_pFloorPnl;
    FC_Stars               *m_pStars;
    PK::PK_Label           *m_pHighScoreLbl;
    PK::PK_Label           *m_pHiScoreLabel;
    PK::PK_Label           *m_pHiScoreValLabel;
    bool                    m_bHighscoreBeaten;
    bool                    m_ScoreSoundPlayed;

public:
    FC_ScoreBoard(const PK::PK_String &sName);
    void Show(int iScore, int iHighsore, bool bHighscoreBeaten);
    void SetScore(int iScore);
    void SetHighScore(int iHighscore);
    void SetVisible(bool bVisible);
    void SetToFalling();
    void Dismiss();
    void ShowStars();
    void ScoreBoardCollided(PK::PK_Body &body);

    inline bool HasStarEffectEnded() { return m_pStars->AreAllStarsOut(); }
};

#endif
