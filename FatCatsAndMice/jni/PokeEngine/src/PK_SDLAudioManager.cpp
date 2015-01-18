#include <assert.h>
#include "PK_Globals.h"
#include "PK_SDLAudioManager.h"
#include "PK_SDLSoundAsset.h"
#include "PK_SDLMusicAsset.h"
#include "PK_Exceptions.h"
#include "PK_AudioManagerSettings.h"
#include "PK_Log.h"
#include <sdl.h>
#include <sdl_mixer.h>

namespace PK {

PK_SDLAudioManager::PK_SDLAudioManager(const PK_String &sName) :
    PK_AudioManager(sName)
{
    SetTypeName("PK_SDLAudioManager");
    m_bInitialized = false;
	m_bIsMuted = false;
}
    
//
PK_SDLAudioManager::~PK_SDLAudioManager()
{
    FreeResources();
}
    
//
void PK_SDLAudioManager::FreeResources()
{
    Mix_CloseAudio();
}
    
//
void PK_SDLAudioManager::OnInitialize()
{
    if (m_bInitialized)
    {
        throw PK_SystemException("Audio manager was already initialized.", __FILE__, __LINE__);
    }
    
    m_Settings.Load(PK_AUDIOMANAGER_SETTINGS_FILE);
  
    if(Mix_OpenAudio(m_Settings.GetAudioRate(), m_Settings.GetAudioFormat(), m_Settings.GetAudioChannels(), m_Settings.GetAudioBuffers()) != 0)
    {
        Mix_GetError();
        throw PK_SDLException(SDLLib_SDL_Mixer, __FILE__, __LINE__);
    }
    m_bInitialized = true;
}

//
void PK_SDLAudioManager::PlaySoundEffect(const PK_SoundAsset &sound)
{

    if (!m_bInitialized)
    {
        throw PK_SystemException("Cannot play sound effect. SDLAudioManager was not initialized.", __FILE__, __LINE__);
    }
    
    if (sound.IsLoaded() == false)
    {
        throw PK_SystemException("Cannot play sound effect. Sound asset was not loaded.", __FILE__, __LINE__);
    }
    

    PK_Log::WriteInfo("PKS", "Play sound effect");
    int channel;
    PK_SDLSoundAsset *pAsset = (PK_SDLSoundAsset *) &sound;
    
    channel = Mix_PlayChannel(-1, pAsset->GetChunk(), 0);
    PK_Log::WriteInfo("PKS", "Play sound effect channel is %d", channel);

}

//
void PK_SDLAudioManager::PlayMusic(const PK_MusicAsset &music, bool bLoop)
{
    if (!m_bInitialized)
    {
        throw PK_SystemException("Cannot play music. SDLAudioManager was not initialized.", __FILE__, __LINE__);
    }
    
    if (music.IsLoaded() == false)
    {
        throw PK_SystemException("Cannot play music. Music asset was not loaded.", __FILE__, __LINE__);
    }
    PK_SDLMusicAsset *pAsset = (PK_SDLMusicAsset *) &music;
    
    Mix_PlayMusic(pAsset->GetChunk(), (bLoop? -1 : 1));
}

//
void PK_SDLAudioManager::StopMusic()
{
	Mix_HaltMusic();
}

//
void PK_SDLAudioManager::PauseMusic()
{
	Mix_PauseMusic();
}

//
void PK_SDLAudioManager::ResumeMusic()
{
	Mix_ResumeMusic();
}

// Converte uma string no DEFINE do audio format do SDL_Mixer
int PK_SDLAudioManager::AudioFormatStrToInt(const PK_String &formatStr)
{
    if (formatStr == "AUDIO_U8")
    {
        return AUDIO_U8;
    }
    if (formatStr == "AUDIO_S8")
    {
        return AUDIO_S8;
    }
    if (formatStr == "AUDIO_U16LSB")
    {
        return AUDIO_U16LSB;
    }
    if (formatStr == "AUDIO_S16LSB")
    {
        return AUDIO_S16LSB;
    }
    if (formatStr == "AUDIO_U16MSB")
    {
        return AUDIO_U16MSB;
    }
    if (formatStr == "AUDIO_S16MSB")
    {
        return AUDIO_S16MSB;
    }
    if (formatStr == "AUDIO_U16")
    {
        return AUDIO_U16;
    }
    if (formatStr == "AUDIO_S16")
    {
        return AUDIO_S16;
    }
    if (formatStr == "AUDIO_U16SYS")
    {
        return AUDIO_U16SYS;
    }
    if (formatStr == "AUDIO_S16SYS")
    {
        return AUDIO_S16SYS;
    }
    
    throw PK_SystemException("SDL Mixer audio format '%s' is invalid.", __FILE__, __LINE__, formatStr.c_str());
}

//
void PK_SDLAudioManager::Mute()
{
    if (!m_bInitialized)
    {
        PK_Log::WriteWarning(PK_LOG_TAG, "Cannot mute sound because the Audio Manager is not initialized.");
        return;
    }

    if (m_bIsMuted)
    {
        return;
    }
    
	m_bIsMuted = true;
    Mix_Volume(-1, 0);
}

//
void PK_SDLAudioManager::UnMute()
{
    if (!m_bInitialized)
    {
        PK_Log::WriteWarning(PK_LOG_TAG, "Cannot unmute sound because the Audio Manager is not initialized.");
        return;
    }

    if (!m_bIsMuted)
    {
        return;
    }
    
    Mix_Volume(-1, MIX_MAX_VOLUME);
	m_bIsMuted = false;
}

//
void PK_SDLAudioManager::SetMusicVolume(float fVolume)
{
	if (fVolume < PK_MIN_VOLUME) 
	{
		fVolume = PK_MIN_VOLUME;
	}
	if (fVolume > PK_MAX_VOLUME) 
	{
		fVolume = PK_MAX_VOLUME;
	}
	// Converter de escala 0-100 (Poke) para escala SDL
	float fSDLVol = fVolume * (float)MIX_MAX_VOLUME / (float)PK_MAX_VOLUME;
	Mix_VolumeMusic(fSDLVol);
}

//
float PK_SDLAudioManager::GetMusicVolume()
{
	// Converter de escala SLD para escala 0-100 (Poke)
	return (Mix_VolumeMusic(-1) * PK_MAX_VOLUME / MIX_MAX_VOLUME);
}

} // namespace

