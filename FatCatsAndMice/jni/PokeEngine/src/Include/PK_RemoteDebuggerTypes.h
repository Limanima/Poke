#ifndef _PK_REMOTEDEBUGGERTYPES_H_
#define _PK_REMOTEDEBUGGERTYPES_H_

#include "PK_Types.h"
namespace PK {
    
// 
enum PK_eDebuggerMessageType
{
  DebuggerMessageType_Connect = 1,
  DebuggerMessageType_FPS = 2,
  DebuggerMessageType_LogMessage = 3,
  DebuggerMessageType_ObjectCreated = 4,
  DebuggerMessageType_ObjectDestroyed = 5,
  DebuggerMessageType_GetObjectInfo = 6
};

// 
enum PK_eDebuggerServerCommand
{
  DebuggerServerCommand_None = 0,
  DebuggerServerCommand_GetObjectInfo = 2
};
    
enum PK_eDebuggerResponseStatus
{
    DebuggerResponseStatus_Ok = 0,
    DebuggerResponseStatus_ResponseError = 1,
    DebuggerResponseStatus_Error = 2,
};

struct PK_tDebuggerMessage
{
    PK_tTimestamp           timestamp;  
    PK_eDebuggerMessageType msgType;
    PK_String               sBody;
};


struct PK_tDebuggerResponse
{
    PK_eDebuggerResponseStatus status;
    PK_String content;
    PK_String detail;
};

struct PK_tDebuggerSentMsgHeader
{
    PK_eDebuggerMessageType type;
    PK_tTimestamp timestamp;
    unsigned int contentSize;
};
struct PK_tDebuggerRecvMsgHeader
{
    PK_eDebuggerResponseStatus status;
    PK_eDebuggerServerCommand command;
    unsigned int contentSize;
};

}
#endif