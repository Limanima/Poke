#include "PK_AudioManager.h"

namespace PK {

//
PK_AudioManager::PK_AudioManager(const PK_String &sName) :
    PK_Component(sName)
{
	SetTypeName("PK_AudioManager");
	m_musicFadeStatus = FadeType_None;
	m_fFadeSpeed = 0.0f;
}

//
void PK_AudioManager::OnUpdate(const PK_GameTimer &time)
{
	if (m_musicFadeStatus == FadeType_None)
	{
		return;
	}
	switch(m_musicFadeStatus)
	{
		case FadeType_In:
			ProcessMusicFadeIn(time);
			break;
		case FadeType_Out:
			ProcessMusicFadeOut(time);
			break;
		default:
			break;
	}
}

//
void PK_AudioManager::ProcessMusicFadeIn(const PK_GameTimer &time)
{
	float fVolume = GetMusicVolume();
	fVolume += m_fFadeSpeed * time.GetEllapsedTime();
	SetMusicVolume(fVolume);
	if (GetMusicVolume() >= PK_MAX_VOLUME)
	{
		m_musicFadeStatus = FadeType_None;
	}
}

//
void PK_AudioManager::ProcessMusicFadeOut(const PK_GameTimer &time)
{
	float fVolume = GetMusicVolume();
	fVolume -= m_fFadeSpeed * (float)time.GetEllapsedTime() / 10.0f;
	SetMusicVolume(fVolume);
	if (GetMusicVolume() <= PK_MIN_VOLUME)
	{
		m_musicFadeStatus = FadeType_None;
        StopMusic();
        SetMusicVolume(PK_MAX_VOLUME);
	}
}

//
void PK_AudioManager::SetMuted(bool bMuted)
{
    if (bMuted)
    {
        UnMute();
    }
    else
    {
        Mute();
    }
}

//
void PK_AudioManager::FadeOutMusic(float fSpeed)
{
	if (IsMuted())
	{
		return;
	}
	m_musicFadeStatus = FadeType_Out;
	m_fFadeSpeed = fSpeed;
}

//
void PK_AudioManager::FadeInMusic(float fSpeed)
{
	if (IsMuted())
	{
		UnMute();
	}
	m_musicFadeStatus = FadeType_In;
	m_fFadeSpeed = fSpeed;
}

} // namespace
