#ifndef __PKC_ADBANNER_H__
#define __PKC_ADBANNER_H__

// Instrucoes para incorporar ads aqui:
//  https://developers.google.com/mobile-ads-sdk/docs/admob/fundamentals?hl=pt#ios
// Import GADBannerView's definition from the SDK
extern "C"
{
#import "GADBannerView.h"
#import "GADBannerViewDelegate.h"
}
#import "PK_Types.h"
#import "PK_iOSAdBanner.h"

@class GADBannerView;
@class GADRequest;

@interface PKc_AdBanner : UIViewController<GADBannerViewDelegate>
{
    GADBannerView      *m_bannerView;
    bool                m_bVisible;
    bool                m_buseTestAds;
    PK::PK_iOSAdBanner *m_pPKAdBanner;
}

@property (assign) NSString * adId;
@property (readwrite) bool useTestAds;
- (id)initWithId:(NSString *)id
     adDockStyle:(PK::PK_tpAdDock) dockStyle
     pkAd:(PK::PK_iOSAdBanner *) pPKAdBanner;
- (void)show;
- (void)hide;

@end


#endif
