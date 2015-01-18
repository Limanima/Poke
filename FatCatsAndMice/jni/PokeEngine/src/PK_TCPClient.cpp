#include "PK_TCPClient.h"
#include "PK_ClassFactory.h"

namespace PK {

PK_TCPClient::PK_TCPClient(const PK_String &sName) :
  PK_Object(sName)
{
  SetTypeName("PK_TCPClient");
  m_pSocket = NULL;
}

PK_TCPClient::PK_TCPClient(const PK_String &sName, PK_TCPSocket &socket) :
  PK_Object(sName)
{
  SetTypeName("PK_TCPClient");
  m_pSocket = &socket;
  m_pSocket->Grab();
}

//
PK_TCPClient::~PK_TCPClient()
{
    if(m_pSocket !=NULL)
    {
        m_pSocket->Release();
    }
}

//
void PK_TCPClient::Disconnect()
{
  m_pSocket->Close();
}

//
void PK_TCPClient::Connect(const PK_tIPAddress &ip, int iPort)
{
    if (m_pSocket != NULL)
    {
        throw PK_SystemException("TCP Client is already connected.", __FILE__, __LINE__);
    }
    m_pSocket = PK_ClassFactory::CreateTCPSocket(GetName() + "_socket");
    m_pSocket->Open(ip, iPort);
}

//
void PK_TCPClient::Connect(const PK_String &sHostname, int iPort)
{
    if (m_pSocket != NULL)
    {
        throw PK_SystemException("TCP Client is already connected.", __FILE__, __LINE__);
    }
    m_pSocket = PK_ClassFactory::CreateTCPSocket(GetName() + "_socket");
    m_pSocket->Open(sHostname, iPort);
}

//
void PK_TCPClient::SendMsg(const PK_MemoryBuffer &sMessage)
{
    if (m_pSocket == NULL)
    {
        throw PK_SystemException("Cannot send message because TCP Client is not connected.", __FILE__, __LINE__);
    }
    m_pSocket->Send(sMessage);
}

//
void PK_TCPClient::SendMsg(const PK_String &sMessage)
{
    if (m_pSocket == NULL)
    {
        throw PK_SystemException("Cannot send message because TCP Client is not connected.", __FILE__, __LINE__);
    }
    m_pSocket->Send(sMessage);
}

//
void PK_TCPClient::SendMsgWithResponse(const PK_MemoryBuffer &message, PK_MemoryBuffer &retMessage)
{
    SendMsg(message);
    m_pSocket->WaitForMessage(retMessage);
}

//
PK_String PK_TCPClient::SendMsgWithResponse(const PK_String &sMessage)
{
    SendMsg(sMessage);
    PK_MemoryBuffer buffer;
    m_pSocket->WaitForMessage(buffer);

    PK_String sMsg = buffer.GetAsStr();
    return sMsg;
}
} // namespace