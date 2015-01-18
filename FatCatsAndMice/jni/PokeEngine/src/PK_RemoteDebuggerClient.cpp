#include <time.h>
#include "PK_Sleep.h"
#include "PK_RemoteDebuggerClient.h"
#include "PK_SystemException.h"
#include "PK_Mutex.h"
#include "PK_MemoryBuffer.h"
#include "PK_ObjectCallback.h"
#include "PK_Globals.h"

namespace PK {

//
PK_RemoteDebuggerClient::PK_RemoteDebuggerClient() :
    PK_Object(PK_REMOTE_DEBUGGER_NAME)
{
	SetTypeName("PK_RemoteDebuggerClient");
    m_MessageListMutex.SetName(GetName() + "_msgListMutex");
    m_bRunning = false;
    m_SendMessagesTimer.SetAlarmTime(0);
    m_SendMessagesTimer.SetWithSnooze(true);
    m_SendMessagesTimer.OnTimer.Set(new PK_ObjectCallback<PK_RemoteDebuggerClient>(*this, &PK_RemoteDebuggerClient::OnSendMessagesTimer));
    m_MessageToSend.SetSize(4096);
    m_iPort = 0;
}

//
PK_RemoteDebuggerClient::~PK_RemoteDebuggerClient()
{
}

//
bool PK_RemoteDebuggerClient::Launch(const PK_String &sHostname, int iPort)
{
    if (m_Client.IsActive())
    {
        throw PK_SystemException("Cannot launch Remote Debugger Client because it's already running.", __FILE__, __LINE__);
    }
    m_sHostname = sHostname;
    m_iPort = iPort;

    m_ProcessingThread.StartThread(PK_RemoteDebuggerClient::ProcessingThread, this);

    return true;
}

//
void PK_RemoteDebuggerClient::Stop()
{
  if (!m_Client.IsActive())
  {
    throw PK_SystemException("Cannot stop the Remote Debugger Client because it's already stopped.", __FILE__, __LINE__);
  }
  m_bRunning = false;
  m_ProcessingThread.WaitExit();
  m_Client.Disconnect();
}

//
void PK_RemoteDebuggerClient::SendFPSMessage(int iFPS)
{
  PK_tDebuggerMessage msg;
  msg.msgType = DebuggerMessageType_FPS;
  msg.sBody.Format("%d", iFPS);

  AddMessage(msg);
}

//
void PK_RemoteDebuggerClient::SendLogMessage(const PK_String &sMessage)
{
  PK_tDebuggerMessage msg;
  msg.msgType = DebuggerMessageType_LogMessage;
  msg.sBody = sMessage;

  AddMessage(msg);
}

//
void PK_RemoteDebuggerClient::AddFPSMessage(int iFPS)
{
  PK_tDebuggerMessage msg;
  msg.msgType = DebuggerMessageType_FPS;
  msg.sBody.Format("%d", iFPS);
  AddMessage(msg);  
}

//
void PK_RemoteDebuggerClient::AddLogMessage(const char * szTag, PK_eLogLevel level, char * szMsg)
{
  PK_tDebuggerMessage msg;
  msg.msgType = DebuggerMessageType_LogMessage;
  msg.sBody.Format("%s|%d|%s", szTag, level, szMsg);
  AddMessage(msg);  
}

//
void PK_RemoteDebuggerClient::AddObjectCreated(unsigned long uiUniqueId, const PK_String &sTypeName, const PK_String &sName)
{
  PK_tDebuggerMessage msg;
  msg.msgType = DebuggerMessageType_ObjectCreated;
  msg.sBody.Format("%d|%s|%s", uiUniqueId, sTypeName.c_str(), sName.c_str());
  AddMessage(msg);  
}

// 
void PK_RemoteDebuggerClient::AddObjectDestroyed(unsigned long uiUniqueId)
{
  PK_tDebuggerMessage msg;
  msg.msgType = DebuggerMessageType_ObjectDestroyed;
  msg.sBody.Format("%d", uiUniqueId);
  AddMessage(msg);  
}

//
void PK_RemoteDebuggerClient::AddGetObjInfoMsg(unsigned long uiUniqueId, const PK_String &sTypeName, const PK_String &sName, unsigned int uiSize)
{
  PK_tDebuggerMessage msg;
  msg.msgType = DebuggerMessageType_GetObjectInfo;
  msg.sBody.Format("%d|%s|%s|%d", uiUniqueId, sTypeName.c_str(), sName.c_str(), uiSize);
  AddMessage(msg);  
}

//
void PK_RemoteDebuggerClient::AddMessage(PK_tDebuggerMessage &msg)
{
      if (IsRunning() == false)
      {
          return;
      }
      m_MessageListMutex.Lock();
      m_messagesToDispath.Add(msg);
      m_MessageListMutex.Unlock();
}

//
void PK_RemoteDebuggerClient::FormatMessage(PK_tDebuggerMessage &msg, PK_MemoryBuffer &retBuffer)
{
    PK_tDebuggerSentMsgHeader msgHeader;
    msgHeader.type = msg.msgType;
    msgHeader.timestamp = msg.timestamp;
    msgHeader.contentSize = (unsigned int)msg.sBody.length();
    retBuffer.Clear();
    retBuffer.Append((void *) &msgHeader, sizeof(msgHeader));
    retBuffer.Append(msg.sBody);
}

//
void PK_RemoteDebuggerClient::OnSendMessagesTimer(PK_Object &sender)
{
    if (m_messagesToDispath.GetCount() > 0)
    {
      for(; ; )
      {
        m_MessageListMutex.Lock();
        if (m_messagesToDispath.GetCount() == 0)
        {
          m_MessageListMutex.Unlock();
          break;
        }
        PK_tDebuggerMessage *pMsg = &(*m_messagesToDispath.Begin());
        m_MessageListMutex.Unlock();

        // Enviar a mensagem de connect
        PK_tDebuggerResponse resp;
        SendRequest(*pMsg, resp);
        m_MessageListMutex.Lock();
        m_messagesToDispath.Erase(m_messagesToDispath.Begin());
        m_MessageListMutex.Unlock();
      }
      m_SendMessagesTimer.Reset();
    }
}

//
int PK_RemoteDebuggerClient::ProcessingThread(void * param)
{
    PK_RemoteDebuggerClient *pDebuggerClient = (PK_RemoteDebuggerClient *)param;
  
    try
    {
        pDebuggerClient->m_Client.Connect(pDebuggerClient->m_sHostname, pDebuggerClient->m_iPort);
    }
    catch(PK_Exception &ex)
    {
        PK_Log::WriteError(PK_LOG_TAG, "Error launching remote debugger. Remote debugger will be inactive for this session. Error was %s", ex.GetMsg().c_str());
        return -1;
    }

    // Enviar a mensagem de connect
    PK_tDebuggerMessage msg;
    msg.msgType = DebuggerMessageType_Connect;
    msg.sBody = PokeEngine.GetGame().GetName();
    PK_tDebuggerResponse resp;
    pDebuggerClient->SendRequest(msg, resp);
    if (resp.status != DebuggerResponseStatus_Ok)
    {
        PK_Log::WriteError(PK_LOG_TAG, "Remote debugger responded with error, could not connect the server. Remote debugger will be inactive for this session.");
        pDebuggerClient->m_Client.Disconnect();
        return -1;
    }
    pDebuggerClient->m_MessageListMutex.Initialize();

  pDebuggerClient->m_bRunning = true;
  pDebuggerClient->m_SendMessagesTimer.SetEnabled(true);
  do
  {
    pDebuggerClient->m_SendMessagesTimer.Update();
  }
  while(pDebuggerClient->IsRunning());

  return 0;
}

//
void PK_RemoteDebuggerClient::SendRequest(PK_tDebuggerMessage &msg, PK_tDebuggerResponse &response)
{
    FormatMessage(msg, m_MessageToSend);
    PK_MemoryBuffer retBuffer;
    m_Client.SendMsgWithResponse(m_MessageToSend, retBuffer);
    PK_tDebuggerRecvMsgHeader respHeader;
    // 
    if (retBuffer.GetLength() < sizeof(PK_tDebuggerRecvMsgHeader))
    {
        response.status = DebuggerResponseStatus_ResponseError;
        response.detail = "";
        return;
    }
    memcpy(&respHeader, retBuffer.GetData(), sizeof(respHeader));
    if (retBuffer.GetLength() != sizeof(PK_tDebuggerRecvMsgHeader) + respHeader.contentSize)
    {
        response.status = DebuggerResponseStatus_ResponseError;
        response.detail = "";
        return;
    }
    response.content = retBuffer.GetAsStr(sizeof(PK_tDebuggerRecvMsgHeader));
    switch(respHeader.status)
    {
      case DebuggerResponseStatus_Ok:
          switch(respHeader.command)
          {
                case DebuggerServerCommand_None:
                    break;

                default:
                    ProcessServerCommand(respHeader.command, response.content);
                    break;
          }
          break;

      default:
          break;
    }
    
    response.status = respHeader.status;
}

//
void PK_RemoteDebuggerClient::ProcessServerCommand(PK_eDebuggerServerCommand command, const PK_String &commandString)
{
    switch(command)
    {
        case DebuggerServerCommand_GetObjectInfo:
            {
                PK_Object *pObj = PK_Profiler::GetObjectX(atol(commandString.c_str()));
                if (pObj != NULL)
                {
                    AddGetObjInfoMsg((unsigned long long)pObj, pObj->GetTypeName(), pObj->GetName(), 0);
                }
            }
            break;
            
        default:
            break;
    }
}

} // namespace
