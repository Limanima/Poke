#ifndef _PK_AUDIOMANAGERSETTINGS_H_
#define _PK_AUDIOMANAGERSETTINGS_H_

#include "PK_Settings.h"

namespace PK {

class PK_DataFileRecord;

// Estes settings sao um tanto ou quanto especificos de SDL, talvez um SDLAudioManagerSettings fosse
// mais apropriedado
class PK_AudioManagerSettings : public PK_Settings
{
private:
    int             m_iAudioRate;
    unsigned short  m_usAudioFormat;
    int             m_iAudioChannels;
    int             m_iAudioBuffers;

public:
	PK_AudioManagerSettings();
    void OnLoad();
   
	inline int GetAudioRate() { return m_iAudioRate; }
	inline unsigned short GetAudioFormat() { return m_usAudioFormat; }
	inline int GetAudioChannels() { return m_iAudioChannels; }
	inline int GetAudioBuffers() { return m_iAudioBuffers; }

};

}
#endif
