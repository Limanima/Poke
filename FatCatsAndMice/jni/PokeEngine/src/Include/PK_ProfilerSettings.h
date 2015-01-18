#ifndef _PK_PROFILERSETTINGS_H_
#define _PK_PROFILERSETTINGS_H_

#include "PK_Settings.h"

namespace PK {

class PK_DataFileRecord;

class PK_ProfilerSettings : public PK_Settings
{
private:
    bool m_bEnabled;
    bool m_bRemoteDebbugerEnabled;
    int m_iServerPort;
    PK_String m_sServerName;

public:
	PK_ProfilerSettings();
    void OnLoad();
   
	inline bool GetEnabled() { return m_bEnabled; }
	inline unsigned short GetRemoteDebbugerEnabled() { return m_bRemoteDebbugerEnabled; }
    inline int GetServerPort() { return m_iServerPort; }
    inline PK_String GetServerName() { return m_sServerName; }
};

}
#endif
