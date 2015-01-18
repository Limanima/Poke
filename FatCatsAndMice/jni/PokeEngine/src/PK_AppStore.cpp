#include "PK_AppStore.h"
#include "PK_Exceptions.h"

#if defined(POKE_IOS)
  #include "iOS/PKc_CInterface.h"
#elif defined(POKE_ANDROID)
  #include "PK_AndroidAppStore.h"
#endif

namespace PK {

// static 
void PK_AppStore::OpenAppPage(const PK_String &sAppId)
{
	#if defined(POKE_ANDROID)
	PK_AndroidAppStore::OpenAppPage(sAppId);
	#elif defined(POKE_IOS)
	PKc_OpenAppPageOnStore(sAppId);
    #else
    throw PK_NotImplementedException("PK_AppStore::OpenAppPage()", __FILE__, __LINE__);
	#endif
}


}

// namespace
