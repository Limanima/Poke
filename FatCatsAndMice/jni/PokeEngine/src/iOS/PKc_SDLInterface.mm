#import <sdl/include/SDL_syswm.h>
#include "PKc_SDLInterface.h"
#include "PK_Globals.h"
#include "PK_SDLRenderManager.h"
//
UIViewController * GetSDLViewController()
{
  /*  SDL_SysWMinfo systemWindowInfo;
    SDL_VERSION(&systemWindowInfo.version);
    if ( ! SDL_GetWindowWMInfo(sdlWindow, &systemWindowInfo))
    {
        // consider doing some kind of error handling here
        NSLog(@"GetSDLViewController error");
        return nil;
    }
    UIWindow * appWindow = systemWindowInfo.info.uikit.window;
    */
    UIWindow * appWindow = GetSDLUIWindow();
    UIViewController * rootViewController = appWindow.rootViewController;
    return rootViewController;
}

//
UIWindow * GetSDLUIWindow()
{
    PK::PK_SDLRenderManager *pManager = (PK::PK_SDLRenderManager *)&PK::PokeEngine.GetRenderManager();
    SDL_Window *sdlWindow = pManager->GetWindow();
   
    SDL_SysWMinfo systemWindowInfo;
    SDL_VERSION(&systemWindowInfo.version);
    if ( ! SDL_GetWindowWMInfo(sdlWindow, &systemWindowInfo))
    {
        // consider doing some kind of error handling here
        NSLog(@"GetSDLViewController error");
        return nil;
    }
    
    return systemWindowInfo.info.uikit.window;
}
