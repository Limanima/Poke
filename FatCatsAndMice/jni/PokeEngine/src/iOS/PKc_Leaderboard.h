//

#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>

@interface PKc_Leaderboard : NSObject<GKGameCenterControllerDelegate>
{

}

+ (PKc_Leaderboard *)sharedInstance;
- (Boolean) submitScore: (int64_t) score forLeaderboardID: (NSString*) category;
- (Boolean) showLeaderboard: (NSString*) leaderboardID;
- (void) gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController;

@end
