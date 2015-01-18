#ifndef _PK_AUDIOMANAGER_H_
#define _PK_AUDIOMANAGER_H_

#include "PK_Component.h"
#include "PK_AudioManagerSettings.h"

namespace PK {

#define PK_MIN_VOLUME 0.0f
#define PK_MAX_VOLUME 100.0f

class PK_SoundAsset;
class PK_MusicAsset;
    
enum PK_eFadeType
{  
	FadeType_None,
    FadeType_In,
    FadeType_Out
};

class PK_AudioManager : public PK_Component
{
protected:
    PK_AudioManagerSettings m_Settings;
	PK_eFadeType			m_musicFadeStatus;
	float					m_fFadeSpeed;

public:
    PK_AudioManager(const PK_String &sName);
	void OnUpdate(const PK_GameTimer &time);
	void SetMuted(bool bMuted);

private:
    void ProcessMusicFadeIn(const PK_GameTimer &time);
    void ProcessMusicFadeOut(const PK_GameTimer &time);

public:
    virtual void PlaySoundEffect(const PK_SoundAsset &sound) = 0;
	// Music Methods
    virtual void PlayMusic(const PK_MusicAsset &sound, bool bLoop) = 0;
	virtual void StopMusic() = 0;
	virtual void PauseMusic() = 0;
	virtual void ResumeMusic() = 0;
	void FadeOutMusic(float fSpeed);
	void FadeInMusic(float fSpeed);
	/// @brief Sets the music volume
	///
	/// @param fVolume - The new volume. The value ranges from 0 to 100. If a value smaller then 0 is supplied
	/// then 0 is used. If a value greater then 100 is supplied, 100 is used.
	virtual void SetMusicVolume(float fVolume) = 0;
	virtual float GetMusicVolume() = 0;
	virtual void Mute() = 0;
	virtual void UnMute() = 0;
	virtual bool IsMuted() = 0;

	virtual bool IsMusicFadingIn() { return m_musicFadeStatus == FadeType_In; }
	virtual bool IsMusicFadingOut() { return m_musicFadeStatus == FadeType_Out; }
};

}

#endif
