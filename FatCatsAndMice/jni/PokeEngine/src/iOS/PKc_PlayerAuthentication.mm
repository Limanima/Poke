//
// retirado daqui:
// http://www.raywenderlich.com/3276/game-center-tutorial-for-ios-how-to-make-a-simple-multiplayer-game-part-12

#import "PKc_PlayerAuthentication.h"
#import <GameKit/GameKit.h>
#import <sdl/src/video/uikit/SDL_uikitappdelegate.h>
#import <sdl.h>
#import <sdl/include/SDL_syswm.h>
#include "PKc_Consts.h"
#include "PKc_SDLInterface.h"
#include "PKc_CInterface.h"
#include "PK_Log.h"

@implementation PKc_PlayerAuthentication

@synthesize gameCenterAvailable;
@synthesize userAuthenticated;

static PKc_PlayerAuthentication *sharedHelper = nil;

+ (PKc_PlayerAuthentication *) sharedInstance {
    if (!sharedHelper) {
        sharedHelper = [[PKc_PlayerAuthentication alloc] init];
    }
    return sharedHelper;
}

- (BOOL)isGameCenterAvailable
{
    // check for presence of GKLocalPlayer API
    Class gcClass = (NSClassFromString(@"GKLocalPlayer"));
    
    // check if the device is running iOS 4.1 or later
    NSString *reqSysVer = @"4.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    BOOL osVersionSupported = ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending);
    
    return (gcClass && osVersionSupported);
}

- (id)init
{
    if ((self = [super init]))
    {
        gameCenterAvailable = [self isGameCenterAvailable];
        if (gameCenterAvailable)
        {
            NSNotificationCenter *nc =
            [NSNotificationCenter defaultCenter];
            [nc addObserver:self
                   selector:@selector(authenticationChanged)
                       name:GKPlayerAuthenticationDidChangeNotificationName
                     object:nil];
        }
    }
    return self;
}

- (void)authenticationChanged
{
    
    if ([GKLocalPlayer localPlayer].isAuthenticated && !userAuthenticated)
    {
        PK::PK_Log::WriteInfo(PK_LOG_TAG, "Authentication changed: player authenticated.");
        userAuthenticated = TRUE;
        PK::PKc_PlayerAuthentication_OnGameCenterLogin(true);
    }
    else
    if (![GKLocalPlayer localPlayer].isAuthenticated && userAuthenticated)
    {
        PK::PK_Log::WriteInfo(PK_LOG_TAG, "Authentication changed: player not authenticated");
        userAuthenticated = FALSE;
        PK::PKc_PlayerAuthentication_OnGameCenterLogout();
    }
}


- (void)authenticateLocalPlayer
{
    if (!gameCenterAvailable)
    {
        PK::PK_Log::WriteInfo(PK_LOG_TAG, "Game Center not available on device, can't authenticate user.");
        return;
    }
    
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    
    if (localPlayer.authenticated != NO)
    {
        PK::PK_Log::WriteInfo(PK_LOG_TAG, "Player already authenticated.");
        return;
    }
    
    if (SYSTEM_VERSION_LESS_THAN(PKc_IOS_VERSION_6_0))
    {
        PK::PK_Log::WriteInfo(PK_LOG_TAG, "Going to authenticate to Game Center (iOS < 6.0).");
        // ios 5.x and below
        [localPlayer authenticateWithCompletionHandler:nil];
    }
    else
    {
      PK::PK_Log::WriteInfo(PK_LOG_TAG, "Going to authenticate to Game Center.");
      // ios 6.0 and above
      [localPlayer setAuthenticateHandler:(^(UIViewController* viewcontroller, NSError *error)
      {
        if (!error)
        {
            if (viewcontroller)
            {
               // Sacar o view controller da janela
              UIViewController * pViewController = GetSDLViewController();
              // Mostrar o pop up do Game Center
              [pViewController presentViewController:viewcontroller animated:YES completion:nil];
            }
        }
        else
        {
            PK::PK_Log::WriteInfo(PK_LOG_TAG, "Error login in to Game Center.");
            PK::PKc_PlayerAuthentication_OnGameCenterLogin(false);
        }
      })];
    }
}

@end

