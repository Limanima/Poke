#ifndef _PK_CLASSFACTORY_H_
#define _PK_CLASSFACTORY_H_

#include "PK_Object.h"
#include "PK_Types.h"

namespace PK {

class PK_RenderManager;
class PK_Asset;
class PK_InputManager;
class PK_EventManager;
class PK_SceneManager;
class PK_AdManager;
class PK_AudioManager;
class PK_AssetContainer;
class PK_PhysicsManager;
class PK_AssetManager;
class PK_SceneControl;
class PK_Scene;
class PK_Player;
class PK_AdBanner;
class PK_TCPSocket;

class PK_ClassFactory : PK_Object
{
public:
    static PK_RenderManager * CreateRenderManager(const PK_String &sName);
    static PK_Asset * CreateAsset(PK_eAssetType type, PK_AssetContainer &container);
    static PK_InputManager * CreateInputManager(const PK_String &sName);
    static PK_EventManager * CreateEventManager(const PK_String &sName);
    static PK_SceneManager * CreateSceneManager(const PK_String &sName);
    static PK_AdManager * CreateAdManager(const PK_String &sName);
    static PK_AudioManager * CreateAudioManager(const PK_String &sName);
    static PK_AssetManager * CreateAssetManager(const PK_String &sName);
    static PK_PhysicsManager * CreatePhysicsManager(PK_Scene &scene, const PK_String &sName);
    static PK_Scene * CreateScene(const PK_String &sTypeName, const PK_String &sName);
    static PK_SceneControl * CreateSceneControl(const PK_String &sTypeName, const PK_String &sName);
    static PK_Player * CreatePlayer();
    static PK_AdBanner * CreateAdBanner(const PK_String &sName, const PK_String &sAdId, PK_AdDock dockStyle);
    static PK_TCPSocket * CreateTCPSocket(const PK_String &sName);
};
    
}// namespace

#endif
