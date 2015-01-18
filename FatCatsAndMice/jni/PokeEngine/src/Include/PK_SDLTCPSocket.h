#ifndef _PK_SDLTCPSOCKET_H_
#define _PK_SDLTCPSOCKET_H_

#include "PK_TCPSocket.h"
#include <SDL_net.h>

namespace PK {
   
// Classe abstracta que define um servidor TCP
class PK_SDLTCPSocket : public PK_TCPSocket
{
private:
    TCPsocket m_tcpsock;

public:
    PK_SDLTCPSocket(const PK_String &sName);
    PK_SDLTCPSocket(const PK_String &sName, TCPsocket &tcpsock);
	  ~PK_SDLTCPSocket();

    // Servidores devem fazer listen
    void Listen(int iPort);
    // Clientes devem fazer open
    void Open(const PK_tIPAddress &address, int iPort);
    void Open(const PK_String &sHostname, int iPort);
    void Close();
    PK_TCPSocket * AcceptConnection();
    bool Send(const void *pData, int iLength);  	
    bool Send(const PK_MemoryBuffer &message);
    bool Send(const PK_String &sMessage);
    void WaitForMessage(PK_MemoryBuffer & retMessage);
    bool IsOpen() const { return (m_tcpsock != 0); }
   
    inline TCPsocket GetSDLSocket() { return m_tcpsock; }

};


} // namespace

#endif
