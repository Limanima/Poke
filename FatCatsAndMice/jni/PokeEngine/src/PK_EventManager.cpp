#include "PK_EventManager.h"
#include "PK_Globals.h"
#include "PK_SDLManager.h"
#include "PK_MessageBox.h"

namespace PK {
    
//
PK_EventManager::PK_EventManager(const PK_String &sName) :
   PK_Component(sName)
{
    SetTypeName("PK_EventManager");

}

//
PK_EventManager::~PK_EventManager()
{

}

//
void PK_EventManager::OnInitialize()
{
	m_queueMutex.Initialize();
}

//
void PK_EventManager::OnUpdate(const PK_GameTimer &time)
{
	if (m_eventQueue.GetCount() > 0)
	{
		while (m_eventQueue.GetCount() > 0)
		{
			m_queueMutex.Lock();
			PK_ListIterator(PK_tEvent) itor = m_eventQueue.Begin();
			PK_tEvent *pEvent = &(*itor);
			switch(pEvent->iEventCode)
			{
				case PK_EVENT_GAME_SERVICES_LOGIN:
					PokeEngine.OnGamerServicesLogin(true);
					break;

				case PK_EVENT_GAME_SERVICES_LOGIN_ERROR:
					PokeEngine.OnGamerServicesLogin(false);
					break;

				case PK_EVENT_GAME_SERVICES_LOGOUT:
					PokeEngine.OnGamerServicesLogout();
					break;

                    
                case PK_EVENT_APP_ENTERED_BACKGROUND:
              		PokeEngine.OnGameEnteredBackground();
					break;
                    
                case PK_EVENT_APP_ENTERED_FOREGROUND:
					PokeEngine.OnGameEnteredForeground();
					break;
                
                case PK_EVENT_MESSAGEBOX_CLOSED:
                {
					PK_tMsgBoxEvent *pMsgBoxEventData = (PK_tMsgBoxEvent *)pEvent->pEventData;
                    if (pMsgBoxEventData->pCallback != NULL)
                    {
                        PK_Callback<PK_IMessageBoxCallback> *pCallback = pMsgBoxEventData->pCallback;
                        (*pCallback)->Execute(pMsgBoxEventData->result);
                    }
                    delete pMsgBoxEventData;
                }
					break;

                    
   
			}
			m_eventQueue.Erase(itor);
			m_queueMutex.Unlock();
		}
	}
}

// Thread safe
void PK_EventManager::PostEvent(PK_tEvent &event)
{
	m_queueMutex.Lock();
	m_eventQueue.Add(event);
	m_queueMutex.Unlock();
}
    
// Thread safe
void PK_EventManager::PostEvent(int iEventCode)
{
    PK_tEvent event;
    event.iEventCode = iEventCode;
    event.pEventData = NULL;
    PostEvent(event);
}

// static 
PK_EventManager & PK_EventManager::CreateInstance(const PK_String &sName)
{
	PK_SDLManager *pManager = new PK_SDLManager(sName);
	return *pManager;
}

} // namespace
