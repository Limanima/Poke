#include "PK_Environment.h"
#include "ios/PKc_CInterface.h"

namespace PK {

// static
PK_String PK_Environment::GetGameStoragePath()
{
#if defined(POKE_IOS)
    return GetAppDocumentsFolder();
#elif defined(POKE_WINDOWS)
    return PK_String(".");
#elif defined (POKE_ANDROID)
    return PK_String(".");
#elif defined (POKE_WINPHONE)
    return PK_String(".");
#else
    IMPLEMENTAR
#endif
}

// static
PK_eBuildType PK_Environment::GetBuildType()
{
#ifdef POKE_DEBUG
    return BuildType_Debug;
#else
    return BuildType_Release;
#endif
}

// static
PK_eGamerServicesProvider PK_Environment::GetGamerServiceProvider()
{
#ifdef POKE_ANDROID
    return GamerServicesProvider_GooglePlay;
#elif defined POKE_IOS
    return GamerServicesProvider_AppleGameCenter;
#else
    return GamerServicesProvider_None;
#endif
}

// static 
PK_ePlatformType PK_Environment::GetPlatform()
{
#ifdef POKE_ANDROID
    return Platform_Android;
#elif defined POKE_IOS
    return Platform_iOS;
#elif defined POKE_WINDOWS
    return Platform_Windows;
#elif defined POKE_WINPHONE
    return Platform_WindowsPhone;
#else
    IMPLEMENTAR
#endif
}
    
//static
PK_String PK_Environment::GetGameServicesName()
{
#ifdef POKE_ANDROID
    return "Google Play";
#elif defined POKE_IOS
    return "Game Center";
#elif defined POKE_WINDOWS
    return "";
#elif defined POKE_WINPHONE
    return "";
#else
    IMPLEMENTAR
#endif
}

} // namespace
