#ifndef _PK_WEB_H_
#define _PK_WEB_H_

#include "PK_Thread.h"

namespace PK {    

//
class PK_Web
{
    static bool m_bWithInternet;
    static bool m_bTestingConnection;

public:
    static void TestInternetConnectionAsync();
    static bool WithInternetConnection();
    static void OpenURL(const PK_String &sURL);

private:
    static int TestConnectionThread(void * param);
};

} // namespace

#endif