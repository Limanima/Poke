#ifndef _PK_ENVIRONMENT_H_
#define _PK_ENVIRONMENT_H_

#include "PK_String.h"
#include "PK_Types.h"

namespace PK {    

// 
class PK_Environment
{
public:
    static PK_String GetGameStoragePath();
    static PK_eBuildType GetBuildType();
    static PK_eGamerServicesProvider GetGamerServiceProvider();
    static PK_ePlatformType GetPlatform();
    static PK_String GetGameServicesName();

    inline static bool IsAndroid() { return GetPlatform() == Platform_Android; }
    inline static bool IsWindows() { return GetPlatform() == Platform_Windows; }
    inline static bool IsiOS() { return GetPlatform() == Platform_iOS; }
    inline static bool IsWindowsPhone() { return GetPlatform() == Platform_WindowsPhone; }

};

} // namespace

#endif
