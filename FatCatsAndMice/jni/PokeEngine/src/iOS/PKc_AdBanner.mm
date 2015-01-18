#import "PKc_AdBanner.h"
#import "PKc_SDLInterface.h"
#import "PK_Log.h"
#import "PK_Globals.h"

@implementation PKc_AdBanner
 
@synthesize adId;

- (id)initWithId:(NSString *)bannerId
     adDockStyle:(PK::PK_tpAdDock) dockStyle
     pkAd:(PK::PK_iOSAdBanner *) pPKAdBanner
{
    self = [super init];
    if (self)
    {       
        adId = bannerId;
        m_pPKAdBanner = pPKAdBanner;
        m_bVisible = false;
        // Create the GADBannerView
        CGPoint pt;
        pt.x = 0.0;
        switch(dockStyle)
        {
            case PK::AdDock_Top:
                pt.y = 0.0;
                break;
                
            case PK::AdDock_Bottom:
                pt.y = PK::PokeEngine.GetRenderManager().GetSafeFrame().size.h - CGSizeFromGADAdSize(kGADAdSizeSmartBannerPortrait).height;
                break;
        }
        m_bannerView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeSmartBannerPortrait
                                                      origin:pt];
        m_bannerView.hidden = TRUE;
        m_bannerView.adUnitID = bannerId;
        [m_bannerView setDelegate:self];
        m_bannerView.rootViewController = GetSDLViewController();
        UIWindow* window = GetSDLUIWindow();
        UIView* view = [window.subviews objectAtIndex:0];
        [view addSubview:m_bannerView];
    }
    return self;
}


//
- (void)show
{
    if (m_bVisible)
    {
        return;
    }
    GADRequest *request = [GADRequest request];

#if defined DEBUG
    PK::PK_List<PK::PK_String> deviceUUIds = PK::PokeEngine.GetSettings().GetAdTestDeviceUUIDs();
    if (deviceUUIds.GetCount() > 0)
    {
        NSMutableArray *stringArray = [[NSMutableArray alloc] init];
        for(PK_ListIterator(PK::PK_String) itor = deviceUUIds.Begin(); itor != deviceUUIds.End(); itor++)
        {
            NSString *uuid = [NSString stringWithCString:(*itor).c_str() encoding:[NSString defaultCStringEncoding]];
            [stringArray addObject:uuid];
        }
        request.testDevices = stringArray;
    }
#endif
    // Initiate a generic request to load it with an ad.
    [m_bannerView loadRequest:request];
    m_bVisible = true;
}

//
- (void)hide
{
    if (!m_bVisible)
    {
        return;
    }
    m_bVisible = false;
    m_bannerView.hidden = true;
}

// Anuncio recebido
- (void)adViewDidReceiveAd:(GADBannerView *)adView
{
    m_bannerView.hidden = !m_bVisible;
    m_pPKAdBanner->InvokeOnRequestSuccess();
}

// Anuncio com erro
- (void)adView:(GADBannerView *)view didFailToReceiveAdWithError:(GADRequestError *)error
{
    NSString * sErr= [error localizedDescription];
    
    PK::PK_Log::WriteError("Error loading ad. Error was: %s", [sErr UTF8String]);
    m_bannerView.hidden = TRUE;
    m_pPKAdBanner->InvokeOnRequestError();
}
@end
