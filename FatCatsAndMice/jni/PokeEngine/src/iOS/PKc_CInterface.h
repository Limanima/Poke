#ifndef __PKC_CINTERFACE_H__
#define __PKC_CINTERFACE_H__

#include "PK_String.h"
#include "PK_Types.h"
#include "PK_MessageBoxCallBack.h"
#include "PK_iOSPlayer.h"

namespace PK
{

    
class PK_iOSAdBanner;
    
// PKc_PlayerAuthentication - Wrapper
void PKc_PlayerAuthentication_AuthenticateUser();
bool PKc_PlayerAuthentication_IsAuthenticated();
void PKc_PlayerAuthentication_OnGameCenterLogin(bool success);
void PKc_PlayerAuthentication_OnGameCenterLogout();
    
// PKc_Leaderboard - Wrapper
bool PKc_Leaderboard_SubmitScore(const PK::PK_String &sLeaderboardId, int iScore);
bool PKc_Leaderboard_ShowLeaderboard(const PK::PK_String &sLeaderboardId);

// PKc_AdBanner
void * PKc_AdBanner_Create(PK_iOSAdBanner &banner);
void PKc_AdBanner_Show(void * ocBannerObj);
void PKc_AdBanner_Hide(void * ocBannerObj);
    
// PKc_Facebook
void PKc_Facebook_ShowLikeButton();

// Messagebox
void PKc_ShowMessageBox(const PK_String &sCaption, const PK_String &sText,
                        const PK_String &sButton1Text,
                        const PK_String &sButton2Text,
                        const PK_String &sButton3Text);
void PKc_MessageBox_OnDialogClosed(PK_eMsgBoxResult result);
    
// Misc
bool PKc_TestInternetConnection();
PK_String GetAppDocumentsFolder();
void PKc_OpenURL(const PK_String &sURL);
void PKc_OpenAppPageOnStore(const PK_String &sAppId);
PK_String PK_cMakeAppStoreLink(const PK_String &sAppId);
}
#endif
