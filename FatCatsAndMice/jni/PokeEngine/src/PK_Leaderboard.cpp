#include "PK_Leaderboard.h"
#include "PK_Globals.h"
#include "PK_Player.h"
#include "PK_Exceptions.h"
#include "PK_Environment.h"

#if defined POKE_IOS
  #define PK_LEADERBOARD_CLASS PK_iOSLeaderboard
  #include "PK_iOSLeaderboard.h"
#elif defined POKE_ANDROID
  #define PK_LEADERBOARD_CLASS PK_AndroidLeaderboard
  #include "PK_AndroidLeaderboard.h"
#elif defined POKE_WINDOWS || defined POKE_WINPHONE
  #define PK_LEADERBOARD_CLASS PK_Leaderboard
  #include "PK_Leaderboard.h"
#else
  IMPLEMENTAR
#endif

// Implementacao default: sem leaderboards
namespace PK {

//
PK_Leaderboard::PK_Leaderboard(const PK_String &sName, const PK_String &sId) :
  PK_Object(sName)
{
	SetTypeName("PK_Leaderboard");

	m_sId = sId;
}

//
bool PK_Leaderboard::CanSubmitScore()
{
    return false;
}

//
bool PK_Leaderboard::CanShow()
{
    return false;
}

//
bool PK_Leaderboard::SubmitScore(int iScore)
{
    throw PK_SystemException("Cannot submit score, because Leaderboards are not supported by the platform.", __FILE__, __LINE__);
}

//
bool PK_Leaderboard::Show()
{
   throw PK_SystemException("Cannot show Leaderboards, because Leaderboards are not supported by the platform.", __FILE__, __LINE__);
}

//
bool PK_Leaderboard::IsSupported()
{
    return false;
}


// static
PK_Leaderboard * PK_Leaderboard::CreateInstance(const PK_String &sName, const PK_String &sIdGameCenter, const PK_String &sIdGooglePlay)
{
	PK_String sId;
	switch(PK_Environment::GetGamerServiceProvider())
	{
	  case GamerServicesProvider_GooglePlay:
		  sId = sIdGooglePlay;
		  break;

	  case GamerServicesProvider_AppleGameCenter:
		  sId = sIdGameCenter;
		  break;

	  default:
		  break;

	}
    PK_Leaderboard  *pLeaderboard = new PK_LEADERBOARD_CLASS(sName, sId);
    PK_CHECK_OBJECT_ALLOC(PK_LEADERBOARD_CLASS, pLeaderboard);
    return pLeaderboard;
}

} // namespace
