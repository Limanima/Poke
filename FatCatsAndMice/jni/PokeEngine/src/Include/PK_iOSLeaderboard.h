#ifndef _PK_IOSLEADERBOARD_H_
#define _PK_IOSLEADERBOARD_H_

#include "PK_Leaderboard.h"

namespace PK {
    
   
// Classe base para um asset: textura, sprite, font, etc
class PK_iOSLeaderboard : public PK_Leaderboard
{


public:
	PK_iOSLeaderboard(const PK_String &sName, const PK_String &sId);
	bool SubmitScore(int iScore);
    bool Show();
    bool CanSubmitScore();
    bool CanShow();
    bool IsSupported();
};

} // namespace

#endif