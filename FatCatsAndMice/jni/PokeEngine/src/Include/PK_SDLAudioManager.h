#ifndef _PK_SDLAUDIOMANAGER_H_
#define _PK_SDLAUDIOMANAGER_H_

#include "PK_AudioManager.h"
#include "PK_String.h"

namespace PK {

class PK_SDLAudioManager : public PK_AudioManager
{
private:
    bool    m_bInitialized;
	bool	m_bIsMuted;
    
public:
    PK_SDLAudioManager(const PK_String &sName);
    ~PK_SDLAudioManager();
    void FreeResources();
    void OnInitialize();
    void PlaySoundEffect(const PK_SoundAsset &sound);
    void PlayMusic(const PK_MusicAsset &music, bool bLoop);
    void StopMusic();
	void PauseMusic();
	void ResumeMusic();
	void Mute();
	void UnMute();
	bool IsMuted() { return m_bIsMuted; }
	void SetMusicVolume(float fVolume);
	float GetMusicVolume();

private:
    int AudioFormatStrToInt(const PK_String &formatStr);
};

}

#endif
