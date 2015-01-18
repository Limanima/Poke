#ifndef _PK_TCPCLIENT_H_
#define _PK_TCPCLIENT_H_

#include "PK_Object.h"
#include "PK_TCPSocket.h"

namespace PK {


// Classe abstracta que define um cliente TCP
class PK_TCPClient : public PK_Object
{
private:
  PK_TCPSocket *m_pSocket;

public:
  PK_TCPClient(const PK_String &sName = "");
  PK_TCPClient(const PK_String &sName, PK_TCPSocket &socket);
  ~PK_TCPClient();
  void Connect(const PK_tIPAddress &ip, int iPort);
  void Connect(const PK_String &sHostname, int iPort);
  void Disconnect();
  void SendMsg(const PK_MemoryBuffer &message);
  void SendMsg(const PK_String &sMessage);
  void SendMsgWithResponse(const PK_MemoryBuffer &message, PK_MemoryBuffer &retMessage);
  PK_String SendMsgWithResponse(const PK_String &sMessage);
  inline bool IsActive() { return (m_pSocket != NULL && m_pSocket->IsOpen()); }
  inline PK_TCPSocket * GetSocket() { return m_pSocket; }
};

} // namespace

#endif