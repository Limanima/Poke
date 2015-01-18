#ifndef _FCAM_SCOREPOINT_H_
#define _FCAM_SCOREPOINT_H_

#include <PokeEngine.h>

class FC_ScorePoint : public PK::PK_Label
{ 
private:
	int m_iScore;
 
public:
    FC_ScorePoint();
	void OnUpdate(const PK::PK_GameTimer &time);
	void SetScore(int iScore);
    void OnMessageReceived(PK::PK_tMessage1 &msg);
};

#endif
