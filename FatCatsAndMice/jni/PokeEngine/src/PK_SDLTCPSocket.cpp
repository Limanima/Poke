#include "PK_SDLTCPSocket.h"
#include "PK_Exceptions.h"
#include "PK_Log.h"

namespace PK {

//
PK_SDLTCPSocket::PK_SDLTCPSocket(const PK_String &sName) :
     PK_TCPSocket(sName)
{
    SetTypeName("PK_SDLTCPSocket");
    m_tcpsock = 0;
}

PK_SDLTCPSocket::PK_SDLTCPSocket(const PK_String &sName, TCPsocket &tcpsock) :
     PK_TCPSocket(sName)
{
    SetTypeName("PK_SDLTCPSocket");
    m_tcpsock = tcpsock;
}

//
PK_SDLTCPSocket::~PK_SDLTCPSocket()
{
    if (IsOpen())
    {
        Close();
    }
}

//
void PK_SDLTCPSocket::Listen(int iPort)
{
  if (IsOpen())
  {
      throw PK_SystemException("Cannot listen TCP socket because it is already open or in listen state.", __FILE__, __LINE__);
  }

  IPaddress sdlIp;
  if (SDLNet_ResolveHost(&sdlIp, NULL, iPort) < 0)
  {
      throw PK_SystemException("Error in SDLNet_ResolveHost(), error was '%s'.", __FILE__, __LINE__, SDLNet_GetError());
  }
 
  m_tcpsock = SDLNet_TCP_Open(&sdlIp);
  if (m_tcpsock == 0) 
  {
    throw PK_SystemException("Could not open TCP port %d, error was '%s'.", __FILE__, __LINE__, iPort, SDLNet_GetError());
  }
}
    
//
void PK_SDLTCPSocket::Open(const PK_tIPAddress &address, int iPort)
{
    if (IsOpen())
    {
        throw PK_SystemException("Cannot connect a TCP socket because it is already connected.", __FILE__, __LINE__);
    }

    IPaddress sdlIp;
    sdlIp.host = address.ipv4;
    sdlIp.port = iPort;
    m_tcpsock = SDLNet_TCP_Open(&sdlIp);
    if (m_tcpsock == 0) 
    {
        throw PK_SDLException(SDLLib_SDL_Net, __FILE__, __LINE__);
    }
}

//
void PK_SDLTCPSocket::Open(const PK_String &sHostname, int iPort)
{
    IPaddress ip;
    // FIXME: Inicializar o SDL_NET, retirar isto daqui de alguma forma
    if (SDLNet_Init() < 0)
    {
        throw PK_SDLException(SDLLib_SDL_Net, __FILE__, __LINE__);
    }

    if (SDLNet_ResolveHost(&ip, sHostname.c_str(), iPort) < 0)
    {
        throw PK_SDLException(SDLLib_SDL_Net, __FILE__, __LINE__);
    }

    PK_tIPAddress addr;
    addr.ipv4 = ip.host;
    Open(addr, ip.port);
}

//
void PK_SDLTCPSocket::Close()
{
    if (!IsOpen())
    {
        throw PK_SystemException("Cannot close the TCP socket because it is already closed.", __FILE__, __LINE__);
    }
    
    SDLNet_TCP_Close(m_tcpsock);
    m_tcpsock = 0;
}

//
PK_TCPSocket * PK_SDLTCPSocket::AcceptConnection()
{
    if (!IsOpen())
    {
        throw PK_SystemException("Cannot accept connections on a closed TCP socket.", __FILE__, __LINE__);
    }

    TCPsocket sdltcpsock;
    sdltcpsock = SDLNet_TCP_Accept(m_tcpsock);
    if(!sdltcpsock) 
    {
       return NULL; 
    }

    PK_SDLTCPSocket * newSocket = new PK_SDLTCPSocket(GetName() + "_client", sdltcpsock);
    return newSocket;
}

//
bool PK_SDLTCPSocket::Send(const void *pData, int iLength)
{
    if (!IsOpen())
    {
        throw PK_SystemException("Cannot send a message to a closed socket.", __FILE__, __LINE__);
    }

    int rc = SDLNet_TCP_Send(m_tcpsock, pData, iLength);
    if (rc < iLength) 
    {
        PK_Log::WriteError(PK_LOG_TAG, "Could not send message to socket. Error was:%s", SDLNet_GetError());
        return false;
    }
    return true;
}

//
bool PK_SDLTCPSocket::Send(const PK_MemoryBuffer &message)
{
    return Send(message.GetData(), message.GetLength());
}

//
bool PK_SDLTCPSocket::Send(const PK_String &sMessage)
{
    return Send(sMessage.c_str(), (int)sMessage.length());
}  

//
void PK_SDLTCPSocket::WaitForMessage(PK_MemoryBuffer & retMessage)
{
    if (!IsOpen())
    {
        throw PK_SystemException("Cannot send a message to a closed socket.", __FILE__, __LINE__);
    }

    char msg[1024];
    int sizeRead = SDLNet_TCP_Recv (m_tcpsock, msg, sizeof(msg));
    if (sizeRead <= 0) 
    {
        PK_Log::WriteError(PK_LOG_TAG, "Could not send message to socket. Error was:%s", SDLNet_GetError());
        // FIXME: se der erro deve lancar erro para fora
        Close();
        retMessage.Empty();
        return;
    }
    retMessage.SetData(msg, sizeRead);

}

} // namespace
