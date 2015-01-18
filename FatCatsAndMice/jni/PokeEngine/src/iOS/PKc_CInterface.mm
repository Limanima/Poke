#import <Foundation/Foundation.h>
#import <sdl/src/video/uikit/SDL_uikitappdelegate.h>
#import <sdl.h>
#import <sdl/include/SDL_syswm.h>
#include "PKc_CInterface.h"
#include "PKc_PlayerAuthentication.h"
#include "PKc_Leaderboard.h"
#include "PKc_AdBanner.h"
#include "PKc_MessageBox.h"
#include "PKc_Facebook.h"
#include "PK_Rate.h"
#include "PK_AdBanner.h"
#include "PK_iOSAdBanner.h"
#include "PK_Exceptions.h"
#include "PK_Log.h"
#include "PK_MessageBox.h"
#include "PK_Globals.h"
#import "Reachability.h"
#include "PK_Web.h"

namespace PK
{
 
//
void PKc_PlayerAuthentication_AuthenticateUser()
{
    [[PKc_PlayerAuthentication sharedInstance] authenticateLocalPlayer];
}

//
bool PKc_PlayerAuthentication_IsAuthenticated()
{
    return [[PKc_PlayerAuthentication sharedInstance] userAuthenticated];
}
    
//
void PKc_PlayerAuthentication_OnGameCenterLogin(bool success)
{
    PokeEngine.GetPlayer().GamerServicesLogin(success);
}
    
//
void PKc_PlayerAuthentication_OnGameCenterLogout()
{
    PokeEngine.GetPlayer().GamerServicesLogout();
}

//
bool PKc_Leaderboard_SubmitScore(const PK::PK_String &sLeaderboardId, int iScore)
{
    NSString *sId = [NSString stringWithCString:sLeaderboardId.c_str()
                                       encoding:[NSString defaultCStringEncoding]];
    return [[PKc_Leaderboard sharedInstance] submitScore: iScore
                                        forLeaderboardID: sId];
}

//
bool PKc_Leaderboard_ShowLeaderboard(const PK::PK_String &sLeaderboardId)
{
    NSString *sId = [NSString stringWithCString:sLeaderboardId.c_str() encoding:[NSString defaultCStringEncoding]];
    return [[PKc_Leaderboard sharedInstance] showLeaderboard: sId];
}

//
void * PKc_AdBanner_Create(PK_iOSAdBanner &banner)
{
    NSString *sId = [NSString stringWithCString:banner.GetAdId().c_str() encoding:[NSString defaultCStringEncoding]];
    PKc_AdBanner *pBanner = [[PKc_AdBanner alloc] initWithId:sId
                                                  adDockStyle:banner.GetDockStyle()
                                                  pkAd:&banner];
    if (!pBanner)
    {
        throw PK_SystemException("Could not create Obj-C object of type PKc_AdBanner.", __FILE__, __LINE__);
    }
    return pBanner;
}

//
void PKc_AdBanner_Show(void * pocBannerObj)
{
    PKc_AdBanner *pBanner = (PKc_AdBanner *)pocBannerObj;
    [pBanner show];
}

//
void PKc_AdBanner_Hide(void * pocBannerObj)
{
    PKc_AdBanner *pBanner = (PKc_AdBanner *)pocBannerObj;
    [pBanner hide];
}
    
//
void PKc_Facebook_ShowLikeButton()
{
    [[PKc_Facebook sharedInstance] showLikeButton];
}
    
// Message box
void PKc_ShowMessageBox(const PK_String &sCaption, const PK_String &sText,
                        const PK_String &sButton1Text,
                        const PK_String &sButton2Text,
                        const PK_String &sButton3Text)
{
    NSString *title = [NSString stringWithCString:sCaption.c_str() encoding:[NSString defaultCStringEncoding]];
    NSString *msg = [NSString stringWithCString:sText.c_str() encoding:[NSString defaultCStringEncoding]];
    NSString *btn1 = [NSString stringWithCString:sButton1Text.c_str() encoding:[NSString defaultCStringEncoding]];
    NSString *btn2 = [NSString stringWithCString:sButton2Text.c_str() encoding:[NSString defaultCStringEncoding]];
    NSString *btn3 = [NSString stringWithCString:sButton3Text.c_str() encoding:[NSString defaultCStringEncoding]];
 
    
    [[PKc_MessageBox sharedInstance]   show:title
                                    message:msg
                                    button1:btn1
                                    button2:btn2
                                    button3:btn3];

}

//
void PKc_MessageBox_OnDialogClosed(PK::PK_eMsgBoxResult result)
{
    PK_MessageBox::InternalDialogClosed(result);
}
    
//
bool PKc_TestInternetConnection()
{
 /*   Reachability * reachability = [Reachability reachabilityWithHostName:@"www.apple.com"];
    NetworkStatus remoteHostStatus = [reachability currentReachabilityStatus];
    
    return (remoteHostStatus != NotReachable);*/
    
    Reachability *networkReachability = [Reachability reachabilityForInternetConnection];
    NetworkStatus networkStatus = [networkReachability currentReachabilityStatus];
    return (networkStatus != NotReachable);
}
    
//
PK_String GetAppDocumentsFolder()
{
    NSString *sFolder =  [NSHomeDirectory() stringByAppendingString:@"/Documents"];
    PK::PK_String str([sFolder cStringUsingEncoding:NSASCIIStringEncoding]);
    return str;
}

//
void PKc_OpenURL(const PK_String &sURL)
{
    NSString *csURL = [NSString stringWithCString:sURL.c_str() encoding:[NSString defaultCStringEncoding]];
    NSURL * nsURL = [NSURL URLWithString:csURL];
    if ([[UIApplication sharedApplication] canOpenURL:nsURL])
    {
        
        [[UIApplication sharedApplication] openURL:nsURL];
    }
    else
    {
        PK::PK_Log::WriteWarning(PK_LOG_TAG, "Cannot open URL %s", sURL.c_str());
    }
}

//
void PKc_OpenAppPageOnStore(const PK_String &sAppId)
{
    PK::PK_String sUrl = PK_cMakeAppStoreLink(sAppId);
    PK_Web::OpenURL(sUrl);
}

//
PK_String PK_cMakeAppStoreLink(const PK_String &sAppId)
{
    NSString *nsAppId = [NSString stringWithCString:sAppId.c_str() encoding:[NSString defaultCStringEncoding]];

    NSString *nsUrl = @"https://itunes.apple.com/us/app/apple-store/id%%APP_ID%%";
    nsUrl = [nsUrl stringByReplacingOccurrencesOfString: @"%%APP_ID%%"
                                             withString: nsAppId];
 
    PK::PK_String sUrl([nsUrl cStringUsingEncoding:NSASCIIStringEncoding]);
    return sUrl;
}
    
} // namespace PK

