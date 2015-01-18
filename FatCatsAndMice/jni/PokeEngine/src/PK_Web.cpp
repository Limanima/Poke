#include "PK_Web.h"
#include "PK_Globals.h"
#include "PK_Thread.h"

#ifdef POKE_IOS
  #include "iOS/PKc_CInterface.h"
#elif defined POKE_WINDOWS
  #include <windows.h>
  #include <Wininet.h>
#elif defined POKE_ANDROID
  #include "PK_AndroidWeb.h"
  #include "android/PK_JNIInterface.h"
#endif

namespace PK {
    
bool PK_Web::m_bWithInternet = false;
bool PK_Web::m_bTestingConnection = false;

// static
void PK_Web::TestInternetConnectionAsync()
{
    if (m_bTestingConnection)
    {
        return;
    }
    PK_Thread testConnectionThread;
    testConnectionThread.StartThread(PK_Web::TestConnectionThread);
}

// static
bool PK_Web::WithInternetConnection()
{
	PK_Web::TestInternetConnectionAsync();
    return (m_bWithInternet);
}

// static 
void PK_Web::OpenURL(const PK_String &sURL)
{
	PK_Log::WriteInfo(PK_LOG_TAG, "Opening url '%s' in platform browser.", sURL.c_str());
	#if defined(POKE_ANDROID)
 	PK_AndroidWeb::OpenURL(sURL);
	#elif defined(POKE_IOS)
 	PKc_OpenURL(sURL);
	#endif
}

// static
int PK_Web::TestConnectionThread(void * param)
{
    try
    {
     m_bTestingConnection= true;
     PK_Log::WriteInfo(PK_LOG_TAG, "Testing internet connection...");
    #if defined(POKE_IOS)
        m_bWithInternet = PKc_TestInternetConnection();
    #elif defined(POKE_WINDOWS)
        DWORD dwFlags;
        m_bWithInternet = (InternetGetConnectedState(&dwFlags, 0) == TRUE? true : false);
    #elif defined(POKE_ANDROID)
 		m_bWithInternet = PK_AndroidWeb::TestInternetConnectionThread();
    #elif defined(POKE_WINPHONE)
 		throw PK_NotImplementedException("PK_Web::TestConnectionThread()", __FILE__, __LINE__);
 	#else
			 IMPLEMENTAR!!
    #endif
		PK_Log::WriteInfo(PK_LOG_TAG, "Internet connection status is %s.", (m_bWithInternet? "Connected": "Disconnected"));
    }
    catch(PK_Exception &ex)
    {
        PK_Log::WriteError(PK_LOG_TAG, "Error testing internet connection. %s", __FILE__, __LINE__, ex.GetMsg().c_str());
    }

    m_bTestingConnection = false;
    return 0;
}

}

// namespace
