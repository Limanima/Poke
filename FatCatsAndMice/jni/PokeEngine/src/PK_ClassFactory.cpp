#include "PK_Config.h"
#include "PK_Types.h"
#include "PK_ClassFactory.h"
#include "PK_TextureAsset.h"
#include "PK_SpriteSetAsset.h"
#include "PK_SpriteAsset.h"
#include "PK_SoundAsset.h"
#include "PK_MusicAsset.h"
#include "PK_FontAsset.h"
#include "PK_ObjectPropertiesAsset.h"
#include "PK_ScriptAsset.h"
#include "PK_SettingsAsset.h"
#include "PK_FileAsset.h"
#include "PK_StringAsset.h"
#include "PK_Exceptions.h"
#include "PK_RenderManager.h"
#include "PK_InputManager.h"
#include "PK_Box2DPhysicsManager.h"
#include "PK_AssetManager.h"
#include "PK_SceneManager.h"
#include "PK_SceneControl.h"
#include "PK_AdManager.h"
#include "PK_Scene.h"
#include "PK_Globals.h"
#include "PK_Button.h"
#include "PK_Panel.h"
#include "PK_Label.h"
#include "PK_Sprite.h"
#include "PK_Player.h"

// Nao queremos estes includes fora do cpp. Isto porque dependem da existencia ou nao de SDL
#ifdef POKE_SDL
	#include "PK_SDLMusicAsset.h"
	#include "PK_SDLSoundAsset.h"
	#include "PK_SDLInputManager.h"
	#include "PK_SDLAudioManager.h"
#ifdef PK_SDL_NET
	#include "PK_SDLTCPSocket.h"
#endif
	#define PK_SOUND_ASSET_CLASS PK_SDLSoundAsset
	#define PK_MUSIC_ASSET_CLASS PK_SDLMusicAsset
	#define PK_INPUT_MANAGER_CLASS PK_SDLInputManager
	#define PK_TCPSOCKET_CLASS PK_SDLTCPSocket
	#define PK_SOUND_MANAGER_CLASS PK_SDLAudioManager

#if !defined(POKE_DX)
    #define PK_TEXTURE_ASSET_CLASS PK_SDLTextureAsset
	#include "PK_SDLTextureAsset.h"
#else
    #define PK_TEXTURE_ASSET_CLASS PK_SDLDXTextureAsset
	#include "PK_SDLDXTextureAsset.h"
#endif
#endif // POKE_SDL


// Nao queremos estes includes fora do cpp. Isto porque o render depende de gl ou gles
#if defined POKE_GLES
  #include "PK_GLESRenderManager.h"
  #define PK_RENDER_MANAGER_CLASS PK_GLESRenderManager
#elif defined POKE_GL
  #include "PK_GLRenderManager.h"
  #define PK_RENDER_MANAGER_CLASS PK_GLRenderManager
#elif defined POKE_DX
  #include "PK_DXRenderManager.h"
  #define PK_RENDER_MANAGER_CLASS PK_DXRenderManager
#endif

#if defined POKE_IOS
  #define PK_PLAYER_CLASS PK_iOSPlayer
  #include "PK_iOSPlayer.h"

  #define PK_ADBANNER_CLASS PK_iOSAdBanner
  #include "PK_iOSAdBanner.h"

#elif defined POKE_ANDROID
  #define PK_PLAYER_CLASS PK_AndroidPlayer
  #include "PK_AndroidPlayer.h"

  #define PK_ADBANNER_CLASS PK_AndroidAdBanner
  #include "PK_AndroidAdBanner.h"

#elif defined POKE_WINDOWS
  #define PK_PLAYER_CLASS PK_Player
  #include "PK_Player.h"

  #define PK_ADBANNER_CLASS PK_AdBanner
  #include "PK_AdBanner.h"


#elif defined POKE_WINPHONE
  #define PK_PLAYER_CLASS PK_Player
  #include "PK_Player.h"

  #define PK_ADBANNER_CLASS PK_AdBanner
  #include "PK_AdBanner.h"

#endif


namespace PK {
    
// Cria uma instancia de um FileReader. Porque o reader pode depender da plataforma, objectos
// deste tipo devem ser criados via factory
PK_RenderManager * PK_ClassFactory::CreateRenderManager(const PK_String &sName)
{
    PK_RenderManager *pManager = new PK_RENDER_MANAGER_CLASS(sName);
    PK_CHECK_OBJECT_ALLOC(PK_RenderManager, pManager);
    return pManager;
}

// Cria um objecto do tipo asset
PK_Asset * PK_ClassFactory::CreateAsset(PK_eAssetType type, PK_AssetContainer &container)
{
	PK_Asset * pAsset = NULL;

    switch(type)
	{
		case AssetType_Texture:
			pAsset = (PK_Asset *) new PK_TEXTURE_ASSET_CLASS(container); 
			break;

		case AssetType_SpriteSet:
			pAsset = (PK_Asset *) new PK_SpriteSetAsset(container);
			break;

		case AssetType_SoundEffect:
            pAsset = (PK_Asset *) new  PK_SOUND_ASSET_CLASS(container);
			break;

		case AssetType_Music:
			pAsset = (PK_Asset *) new PK_MUSIC_ASSET_CLASS(container);
			break;

		case AssetType_Font:
			pAsset = (PK_Asset *) new PK_FontAsset(container);
			break;
            
		case AssetType_ObjectProperties:
			pAsset = (PK_Asset *) new PK_ObjectPropertiesAsset(container);
			break;
            
		case AssetType_Settings:
			pAsset = (PK_Asset *) new PK_SettingsAsset(container);
			break;

		case AssetType_Script:
			pAsset = (PK_Asset *) new PK_ScriptAsset(container);
			break;

		case AssetType_File:
			pAsset = (PK_Asset *) new PK_FileAsset(container);
			break;
        
        case AssetType_String:
			pAsset = (PK_Asset *) new PK_StringAsset(container);
			break;

		default:
            throw PK_SystemException("Cannot create asset of type '%d'.", __FILE__, __LINE__, type);
	}

    PK_CHECK_OBJECT_ALLOC(PK_Asset, pAsset);

	return pAsset;
}

PK_InputManager * PK_ClassFactory::CreateInputManager(const PK_String &sName)
{
   PK_InputManager *pManager = new PK_INPUT_MANAGER_CLASS(sName);
   PK_CHECK_OBJECT_ALLOC(PK_InputManager, pManager);
   return pManager;
}


PK_SceneManager * PK_ClassFactory::CreateSceneManager(const PK_String &sName)
{
   PK_SceneManager  *pManager = new PK_SceneManager(sName);
   PK_CHECK_OBJECT_ALLOC(PK_SceneManager, pManager);
   return pManager;
}

PK_AdManager * PK_ClassFactory::CreateAdManager(const PK_String &sName)
{
   PK_AdManager  *pManager = new PK_AdManager(sName);
   PK_CHECK_OBJECT_ALLOC(PK_AdManager, pManager);
   return pManager;
}
     
//
PK_AudioManager * PK_ClassFactory::CreateAudioManager(const PK_String &sName)
{
   PK_AudioManager  *pManager = new PK_SOUND_MANAGER_CLASS(sName);
   PK_CHECK_OBJECT_ALLOC(PK_AudioManager, pManager);
   return pManager;
}

//
PK_AssetManager * PK_ClassFactory::CreateAssetManager(const PK_String &sName)
{
   PK_AssetManager  *pManager = new PK_AssetManager(sName);
   PK_CHECK_OBJECT_ALLOC(PK_AssetManager, pManager);
   return pManager;
}

//
PK_PhysicsManager * PK_ClassFactory::CreatePhysicsManager(PK_Scene &scene, const PK_String &sName)
{
   PK_PhysicsManager  *pManager = new PK_Box2DPhysicsManager(scene, sName);
   PK_CHECK_OBJECT_ALLOC(PK_Box2DPhysicsManager, pManager);
   return pManager;
}

//
PK_Scene * PK_ClassFactory::CreateScene(const PK_String &sTypeName, const PK_String &sName)
{
    return NULL;
}

//
PK_SceneControl * PK_ClassFactory::CreateSceneControl(const PK_String &sTypeName, const PK_String &sName)
{
    // Controlos do PK engine comecam por "PK_"
    if (sTypeName.substr(0, strlen(PK_TYPE_PREFIX)) == PK_TYPE_PREFIX)
    {
        if (sTypeName == "PK_Button")
        {
            return new PK_Button(sName);
        }
        if (sTypeName == "PK_Label")
        {
            return new PK_Label(sName);
        }
        if (sTypeName == "PK_Panel")
        {
            return new PK_Panel(sName);
        }
        if (sTypeName == "PK_Sprite")
        {
            return new PK_Sprite(sName);
        }
        
        throw PK_SystemException("Scene control of type '%s' cannot be created because it doesn't exist.", __FILE__, __LINE__, sTypeName.c_str());
    }
    
    // Nao e do engine? Entao e especifico do jogo
    return PokeEngine.GetGame().CreateControl(sTypeName, sName);
}

//
PK_Player * PK_ClassFactory::CreatePlayer()
{
    PK_Player  *pPlayer = new PK_PLAYER_CLASS();
    PK_CHECK_OBJECT_ALLOC(PK_PLAYER_CLASS, pPlayer);
    return pPlayer;
}

//
PK_AdBanner * PK_ClassFactory::CreateAdBanner(const PK_String &sName, const PK_String &sAdId, PK_AdDock dockStyle)
{
    PK_AdBanner  *pBanner = new PK_ADBANNER_CLASS(sName, sAdId, dockStyle);
    PK_CHECK_OBJECT_ALLOC(PK_ADBANNER_CLASS, pBanner);
    return pBanner;
}
//
PK_TCPSocket * PK_ClassFactory::CreateTCPSocket(const PK_String &sName)
{
	// FIXME e se for outro tipo de sockets sem ser SDL?
	#ifdef PK_SDL_NET
    PK_TCPSocket *pSocket = new PK_TCPSOCKET_CLASS(sName);
    PK_CHECK_OBJECT_ALLOC(PK_TCPSOCKET_CLASS, pSocket);
    return pSocket; 
    #else
	throw PK_SystemException("TCP sockets are not supported by the platform.", __FILE__, __LINE__);
    #endif
}


} // namespace
