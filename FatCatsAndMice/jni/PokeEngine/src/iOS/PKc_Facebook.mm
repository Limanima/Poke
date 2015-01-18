#import <UIKit/UIKit.h>
//#import <FacebookSDK/FacebookSDK.h>
#import "PKc_Facebook.h"
#import "PKc_SDLInterface.h"

@implementation PKc_Facebook

static PKc_Facebook *sharedHelper = nil;

// Static - Devolve a instancia
+ (PKc_Facebook *) sharedInstance
{
    if (!sharedHelper)
    {
        sharedHelper = [[PKc_Facebook alloc] init];
    }
    return sharedHelper;
}

//
- (void)showLikeButton
{
 /*   UIWindow* window = GetSDLUIWindow();
    UIView* view = [window.subviews objectAtIndex:0];
    
    [FBSettings enableBetaFeature:FBBetaFeaturesLikeButton];
    [FBSettings enablePlatformCompatibility:NO];
    FBLikeControl *like = [[FBLikeControl alloc] init];
    like.objectID = @"https://www.facebook.com/limanima.teste";
    like.likeControlHorizontalAlignment=FBLikeControlHorizontalAlignmentRight;
    like.likeControlAuxiliaryPosition = FBLikeControlAuxiliaryPositionBottom;
    like.likeControlStyle=FBLikeControlStyleBoxCount;
    like.center = CGPointMake(300, 300);
    like.bounds = CGRectMake(0, 0, 200, 200);
    //like.transform = CGAffineTransformScale(CGAffineTransformIdentity, 2, 2);
    like.likeControlStyle = FBLikeControlStyleButton;
    [view addSubview:like];*/
 
}
@end
