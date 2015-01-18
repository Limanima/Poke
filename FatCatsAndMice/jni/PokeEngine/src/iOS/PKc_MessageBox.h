#ifndef __PKC_MESSAGEBOX_H__
#define __PKC_MESSAGEBOX_H__

@interface PKc_MessageBox : NSObject
{
}
+ (PKc_MessageBox *)sharedInstance;
- (void)show:(NSString *)theTitle
     message:(NSString *)theMessage
     button1:(NSString *)button1Text
     button2:(NSString *)button2Text
     button3:(NSString *)button3Text;


@end


#endif
