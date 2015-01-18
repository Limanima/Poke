#ifndef _PK_TCPSERVER_H_
#define _PK_TCPSERVER_H_

#include "PK_Object.h"
#include "PK_TCPClient.h"

namespace PK {

class PK_TCPServer;
class PK_TCPSocket;
class PK_Thread;

struct PK_tServerTCPClient
{
  PK_TCPServer *m_pTCPServer;
  PK_TCPClient *m_pTCPClient;
  PK_Thread    *m_pThread;
};

// Classe abstracta que define um socket TCP
class PK_TCPServer : public PK_Object
{
private:
    PK_TCPSocket *m_pSocket;
    PK_Thread    *m_pListenerThread;
    PK_List<PK_tServerTCPClient *> m_Clients;
    bool m_bStarted;

public:
    PK_TCPServer(const PK_String &sName);
    ~PK_TCPServer();
    void Start(int iPort);
    void Stop();

    inline bool IsStarted() { return m_bStarted; }
    inline bool IsRunning() { return m_bStarted; }

private:
    void AddClient(PK_TCPClient &client);
    void RemoveClient(PK_tServerTCPClient &client);
    PK_MemoryBuffer WaitForMessage(PK_tServerTCPClient &client);
    PK_TCPClient * WaitForConnection();
    virtual void MessageReceived(const PK_TCPClient &client, const PK_MemoryBuffer &msg) = 0;
    static int ListenerThread(void * param);
    static int ClientManagerThread(void * param);
};

} // namespace

#endif