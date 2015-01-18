#ifndef _PK_EVENTMANAGER_H_
#define _PK_EVENTMANAGER_H_

#include "PK_Component.h"
#include "PK_List.h"
#include "PK_Mutex.h"

namespace PK 
{

#define PK_EVENT_GAME_SERVICES_LOGIN		1
#define PK_EVENT_GAME_SERVICES_LOGIN_ERROR  2
#define PK_EVENT_GAME_SERVICES_LOGOUT		3
#define PK_EVENT_MESSAGEBOX_CLOSED          4
#define PK_EVENT_APP_ENTERED_BACKGROUND     5
#define PK_EVENT_APP_ENTERED_FOREGROUND     6
   

struct PK_tEvent
{
	int iEventCode;
    void *pEventData;
};

//
class PK_EventManager : public PK_Component
{
private:
   PK_List<PK_tEvent> m_eventQueue;
 	PK_Mutex		   m_queueMutex;


public:
    PK_EventManager(const PK_String &sName);
    ~PK_EventManager();
	void OnInitialize();
	void OnUpdate(const PK_GameTimer &time);
	void PostEvent(PK_tEvent &event);
    void PostEvent(int iEventCode);
	static PK_EventManager & CreateInstance(const PK_String &sName);
};

}
#endif