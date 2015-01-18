#import <GameKit/GameKit.h>
#import "PKc_MessageBox.h"
#import "PKc_SDLInterface.h"
#import "PKc_CInterface.h"
#include "PK_Globals.h"
#include "PK_Types.h"

@implementation PKc_MessageBox

static PKc_MessageBox *sharedHelper = nil;

// Static - Devolve a instancia
+ (PKc_MessageBox *) sharedInstance
{
    if (!sharedHelper)
    {
        sharedHelper = [[PKc_MessageBox alloc] init];
    }
    return sharedHelper;
}

// Static
- (void)show:(NSString *)theTitle
     message:(NSString *)theMessage
     button1:(NSString *)button1Text
     button2:(NSString *)button2Text
     button3:(NSString *)button3Text;
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:theTitle
                                                    message:theMessage
                                                   delegate:(id<UIAlertViewDelegate>)self
                                          cancelButtonTitle:button1Text
                                          otherButtonTitles:nil];
    
    if ([button2Text length] != 0)
    {
        [alert addButtonWithTitle:button2Text];
    }
    if ([button3Text length] != 0)
    {
        [alert addButtonWithTitle:button3Text];
    }
    [alert show];
 }

//
- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex
{
    PK::PK_eMsgBoxResult result = PK::MsgBoxResult_Button1;
    switch(buttonIndex)
    {
        case 0:
            result = PK::MsgBoxResult_Button1;
            break;
        case 1:
            result = PK::MsgBoxResult_Button2;
            break;
        case 3:
            result = PK::MsgBoxResult_Button3;
            break;
            
        default:
            break;
    }
    PKc_MessageBox_OnDialogClosed(result);
    
}

@end