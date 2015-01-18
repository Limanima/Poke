#ifndef _PK_REMOTEDEBUGGERCLIENT_H_
#define _PK_REMOTEDEBUGGERCLIENT_H_

#include "PK_TCPClient.h"
#include "PK_List.h"
#include "PK_Timer.h"
#include "PK_Thread.h"
#include "PK_Mutex.h"
#include "PK_RemoteDebuggerTypes.h"
#include "PK_Log.h"

namespace PK {

// 
class PK_RemoteDebuggerClient : public PK_Object
{
private:
  PK_List<PK_tDebuggerMessage> m_messagesToDispath;
  PK_TCPClient m_Client;
  PK_Thread    m_ProcessingThread;
  PK_Mutex     m_MessageListMutex;
  bool         m_bRunning;
  PK_Timer     m_SendMessagesTimer;
  PK_MemoryBuffer m_MessageToSend;
  PK_String    m_sHostname;
  int          m_iPort;

public:
	PK_RemoteDebuggerClient();
	~PK_RemoteDebuggerClient();

  /// Inicia a conexao com o debugger remoto por nome
  bool Launch(const PK_String &sHostname, int iPort);
  /// Termina o cliente
  void Stop();
  /// Adiciona uma mensagem do tipo "FPS" a queue de mensagens a enviar para o debugger remoto
  void AddFPSMessage(int iFPS);
  void AddLogMessage(const char * szTag, PK_eLogLevel level, char * szMsg);
  void AddObjectCreated(unsigned long uiUniqueId, const PK_String &sTypeName, const PK_String &sName);
  void AddObjectDestroyed(unsigned long uiUniqueId);
  void AddGetObjInfoMsg(unsigned long uiUniqueId, const PK_String &sTypeName, const PK_String &sName, unsigned int uiSize);

  /// Devolve TRUE se o cliente esta a correr
  inline bool IsRunning() { return m_bRunning; } 
  inline PK_Thread & GetThread() { return m_ProcessingThread; }

private:
  void FormatMessage(PK_tDebuggerMessage &msg, PK_MemoryBuffer &retBuffer);
  void AddMessage(PK_tDebuggerMessage &msg);
  void OnSendMessagesTimer(PK_Object &sender);
  void SendFPSMessage(int iFPS);
  void SendLogMessage(const PK_String &sMessage);
  void SendRequest(PK_tDebuggerMessage &msg, PK_tDebuggerResponse &response);
  void ProcessServerCommand(PK_eDebuggerServerCommand command, const PK_String &commandString);


  static int ProcessingThread(void * param);
};

} // namespace

#endif