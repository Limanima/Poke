// Refª:  https://developer.apple.com/library/ios/documentation/NetworkingInternet/Conceptual/GameKit_Guide/LeaderBoards/LeaderBoards.html#//apple_ref/doc/uid/TP40008304-CH6-SW20
#import "PKc_Leaderboard.h"
#import <GameKit/GameKit.h>
#include "PKc_Consts.h"
#import <sdl.h>
#import <sdl/include/SDL_syswm.h>
#include "PK_Log.h"
#include "PK_Globals.h"
#include "PK_SDLRenderManager.h"
#include "PKc_Consts.h"
#include "PKc_SDLInterface.h"

@implementation PKc_Leaderboard

static PKc_Leaderboard *sharedHelper = nil;

// Static - Devolve a instancia
+ (PKc_Leaderboard *) sharedInstance
{
    if (!sharedHelper)
    {
        sharedHelper = [[PKc_Leaderboard alloc] init];
    }
    return sharedHelper;
}

//
- (Boolean) submitScore: (int64_t) score forLeaderboardID: (NSString*) category
{
    __block bool bOk = true;
    
    PK::PK_Log::WriteInfo(PK_LOG_TAG, "Submiting score to Game Center.");
    GKScore *scoreReporter = [[GKScore alloc] initWithCategory:category];
    scoreReporter.value = score;
    [scoreReporter reportScoreWithCompletionHandler:^(NSError *error)
    {
    
     if (error != nil)
     {
        // Tratar erros
        PK::PK_String msg = std::string([error.description UTF8String]);
        PK::PK_Log::WriteError(PK_LOG_TAG, "Error submiting score to Game Center." + msg);
        bOk = false;
     }
     else
     {
         PK::PK_Log::WriteInfo(PK_LOG_TAG, "Score submited with success to Game Center.");
     }
    }];
    
    return bOk;
}

//
- (Boolean) showLeaderboard: (NSString*) leaderboardID
{
    GKGameCenterViewController *gameCenterController = [[GKGameCenterViewController alloc] init];
    
    if (gameCenterController == nil)
    {
        PK::PK_Log::WriteError(PK_LOG_TAG, "Error creating GKGameCenterViewController!");
        return false;
    }
    
    // Obter a SDL_Window do PokeEngine (ou seja, do SDL)
  //  PK::PK_SDLRenderManager *pManager = (PK::PK_SDLRenderManager *)PK::PokeEngine.RenderManager;
  //  SDL_Window *pWnd = pManager->GetWindow();
    // Sacar o view controller da janela
  //  UIViewController * pViewController = GetSDLViewController(pWnd);
    
    UIViewController * pViewController = GetSDLViewController();

    gameCenterController.gameCenterDelegate = self;
    gameCenterController.viewState = GKGameCenterViewControllerStateLeaderboards;
    gameCenterController.leaderboardTimeScope = GKLeaderboardTimeScopeAllTime;
    gameCenterController.leaderboardCategory = leaderboardID;
    [pViewController presentViewController: gameCenterController animated: YES completion:nil];
    return true;
}

//
- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController
{
    [gameCenterViewController dismissViewControllerAnimated:YES completion:^
    {
        
    }];
}

@end

