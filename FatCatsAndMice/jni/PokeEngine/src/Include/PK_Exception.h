#ifndef _PK_EXCEPTION_H_
#define _PK_EXCEPTION_H_

#include "PK_String.h"

namespace PK {

class PK_Exception
{
  private:
	PK_String   m_sMessage;
	PK_String	m_sSourceFile;
	int			m_iLineNumber;

  public:
    PK_Exception() { } 
	PK_Exception(const char * pszFormat, const char * pszSourceFile, int iLineNumber, ...);
	PK_Exception(const PK_String &sMessage, const char * pszSourceFile, int iLineNumber);
    
	inline PK_String GetMsg() { return m_sMessage; }
	inline void SetMessage(const PK_String &sMessage) { m_sMessage = sMessage; }
    
    inline PK_String GetFile() { return m_sSourceFile; }
    inline int GetLine() { return m_iLineNumber; }

protected:
    void Init(const PK_String &sMessage, const char * pszSourceFile, int iLineNumber);
    
};

}
#endif
