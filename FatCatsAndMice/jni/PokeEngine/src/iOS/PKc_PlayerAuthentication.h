//
//  PK_PlayerAuthentication.h
//  PokeEngine.iOS
//
//  Created by Jorge Lima on 04/03/14.
//
//

#import <Foundation/Foundation.h>
#import "../include/PK_iOSPlayer.h"

@interface PKc_PlayerAuthentication : NSObject
{
    BOOL gameCenterAvailable;
    BOOL userAuthenticated;
}

@property (assign, readonly) BOOL gameCenterAvailable;
@property (assign, readonly) BOOL userAuthenticated;

+ (PKc_PlayerAuthentication *)sharedInstance;
- (void)authenticateLocalPlayer;

@end
