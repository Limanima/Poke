#ifndef _PK_TCPSOCKET_H_
#define _PK_TCPSOCKET_H_

#include "PK_Object.h"
#include "PK_Types.h"
#include "PK_MemoryBuffer.h"

namespace PK {


// Classe abstracta que define um servidor TCP
class PK_TCPSocket : public PK_Object
{
private:
 
public:
    PK_TCPSocket(const PK_String &sName) :
      PK_Object(sName) {
    }

    virtual void Open(const PK_tIPAddress &address, int iPort) = 0;
    virtual void Open(const PK_String &sHostname, int iPort) = 0;
    virtual void Listen(int iPort) = 0;
    virtual void Close() = 0;
    virtual PK_TCPSocket * AcceptConnection() = 0;
    virtual bool Send(const void *pData, int iLength) = 0;  	
    virtual bool Send(const PK_MemoryBuffer &sMessage) = 0;
    virtual bool Send(const PK_String &sMessage) = 0;
    virtual void WaitForMessage(PK_MemoryBuffer & retMessage) = 0; 	
    virtual bool IsOpen() const = 0;
};


} // namespace

#endif