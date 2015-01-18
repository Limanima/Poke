#include "PK_TCPServer.h"
#include "PK_Exceptions.h"
#include "PK_Thread.h"
#include "PK_TCPSocket.h"
#include "PK_TCPClient.h"
#include "PK_ClassFactory.h"
#include "PK_Log.h"

namespace PK {

//
PK_TCPServer::PK_TCPServer(const PK_String &sName) :
  PK_Object(sName)
{
  SetTypeName("PK_TCPServer");
  m_pSocket = NULL;
  m_pListenerThread = NULL;
  m_bStarted = false;
}

//
PK_TCPServer::~PK_TCPServer()
{

}

//
void PK_TCPServer::Start(int iPort)
{
  if (IsStarted())
  {
    throw PK_SystemException("TCP Server named '%s' is already started.", __FILE__, __LINE__, GetName().c_str());
  }

  // Criar o socket e ficar em listen
  if (m_pSocket == NULL)
  {
    m_pSocket = PK_ClassFactory::CreateTCPSocket(GetName() + "_socket");
  }
  m_pSocket->Listen(iPort);
  m_bStarted = true;

  // Criar a thread que aceita as conexões
  if (m_pListenerThread == NULL)
  {
    m_pListenerThread = new PK_Thread();
    m_pListenerThread->Grab();
  }
  m_pListenerThread->StartThread(PK_TCPServer::ListenerThread, this);

}

//
void PK_TCPServer::Stop()
{
  if (!IsStarted())
  {
    throw PK_SystemException("TCP Server named '%s' cannot be stopped because it's not started.", __FILE__, __LINE__, GetName().c_str());
  }
  
  for(PK_ListIterator(PK_tServerTCPClient *) itor = m_Clients.Begin(); itor != m_Clients.End(); )
  {
    RemoveClient(*(*itor));
    itor = m_Clients.Begin();
  }

  m_bStarted = false;
  m_pListenerThread->WaitExit();
  m_pSocket->Close();
}

//
void PK_TCPServer::AddClient(PK_TCPClient &client)
{
  PK_tServerTCPClient *pClient = new PK_tServerTCPClient();
  pClient->m_pTCPServer = this;
  pClient->m_pTCPServer->Grab();
  pClient->m_pTCPClient = &client;
  pClient->m_pTCPClient->Grab();
  pClient->m_pThread = new PK_Thread();
  pClient->m_pThread->Grab();
  pClient->m_pThread->StartThread(PK_TCPServer::ClientManagerThread, pClient);
  m_Clients.Add(pClient);
}

//
void PK_TCPServer::RemoveClient(PK_tServerTCPClient &client)
{
    if (client.m_pTCPClient->IsActive())
    {
        client.m_pTCPClient->Disconnect();
        client.m_pTCPClient->Release();
        client.m_pThread->WaitExit();
        client.m_pThread->Release();
        client.m_pTCPServer->Release();
    }
    m_Clients.Remove(&client);
}

//
PK_MemoryBuffer PK_TCPServer::WaitForMessage(PK_tServerTCPClient &client)
{
  if (!IsStarted())
  {
    throw PK_SystemException("TCP Server named '%s' cannot wait for messages because it is not started.", __FILE__, __LINE__, GetName().c_str());
  }
  PK_MemoryBuffer ms;
  try
  {
      m_pSocket->WaitForMessage(ms);
  }
  catch(PK_SystemException &ex)
  {
      PK_Log::WriteError(PK_LOG_TAG, "Error in TCPServer->WaitForMessage(), message is '%s', client disconnected? Remove it from server.",
          ex.GetMsg().c_str());
      RemoveClient(client);
  }
}

//
PK_TCPClient * PK_TCPServer::WaitForConnection()
{
    do
    {
        PK_TCPSocket * pClientSocket = m_pSocket->AcceptConnection();
        if (pClientSocket != NULL)
        {
          PK_TCPClient *pClient = new PK_TCPClient(GetName() +"_client", *pClientSocket);
          return pClient;
        }
    }
    while(IsRunning());
    return NULL;
}

//
int PK_TCPServer::ListenerThread(void * param)
{
  PK_TCPServer *pServer = (PK_TCPServer *)param;
  do
  {
    PK_TCPClient *pClient = pServer->WaitForConnection();
    if (pClient != NULL)
    {
      pServer->AddClient(*pClient);
    }
  }
  while(pServer->IsRunning());
  return 0;
}

//
int PK_TCPServer::ClientManagerThread(void * param)
{
  PK_tServerTCPClient *pClient = (PK_tServerTCPClient *)param;
  PK_MemoryBuffer recvMessage;
  do
  {
    recvMessage = pClient->m_pTCPServer->WaitForMessage(*pClient); 
    if (pClient->m_pTCPClient->IsActive())
    {
      pClient->m_pTCPServer->MessageReceived(*pClient->m_pTCPClient, recvMessage);
    }
  }
  while(pClient->m_pTCPClient->IsActive());
  return 0;
}

} // namespace