#include "PK_iOSLeaderboard.h"
#include "PK_Exceptions.h"
#include "PK_Globals.h"
#include "PK_Player.h"
#include "iOS/PKc_CInterface.h"
#include "PK_Web.h"
#include "PK_MessageBox.h"

namespace PK {

//
PK_iOSLeaderboard::PK_iOSLeaderboard(const PK_String &sName, const PK_String &sId) :
    PK_Leaderboard(sName, sId)
{
	SetTypeName("PK_iOSLeaderboard");
}

//
bool PK_iOSLeaderboard::SubmitScore(int iScore)
{
    return PKc_Leaderboard_SubmitScore(GetId(), iScore);
}
    
//
bool PK_iOSLeaderboard::Show()
{
    if (PK_Web::WithInternetConnection() == false)
    {
        PK_MessageBox::Show(PK_CAPTION_NO_NET, PK_MESSAGE_NO_NET_LEADERBOARDS);
        return false;
    }
    if (!PokeEngine.GetPlayer().IsAuthenticated())
    {
        PokeEngine.GetPlayer().Authenticate(true);
    }
    return PKc_Leaderboard_ShowLeaderboard(GetId());
}
    
//
bool PK_iOSLeaderboard::CanSubmitScore()
{
    return PokeEngine.GetPlayer().IsAuthenticated();
}
    
//
bool PK_iOSLeaderboard::CanShow()
{
    return PokeEngine.GetPlayer().IsAuthenticated();
}

//
bool PK_iOSLeaderboard::IsSupported()
{
    return true;
}

} // namespace