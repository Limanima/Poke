#ifndef _PK_ASSETMANAGER_H_
#define _PK_ASSETMANAGER_H_

#include "PK_Component.h"
#include "PK_Types.h"
#include "PK_List.h"
#include "PK_String.h"
#include "PK_AssetContainer.h"

namespace PK {

class PK_TextureAsset;
class PK_SpriteSetAsset;
class PK_SpriteAsset;
class PK_SoundAsset;
class PK_MusicAsset;
class PK_FontAsset;
class PK_ObjectPropertiesAsset;
class PK_SettingsAsset;
class PK_ScriptAsset;
class PK_FileAsset;
class PK_StringAsset;

class PK_AssetManager : public PK_Component
{
private:
	PK_List<PK_AssetContainer *> m_AssetContainers;
   

public:
	PK_AssetManager(const PK_String &sName);
	
    void OnInitialize();
    void OnUnInitialize();
	void CreateAssetContainer(const PK_String &sName);
	PK_AssetContainer * GetContainer(const PK_String &sName);
	bool ContainsContainer(const PK_String &sName);
	void UnloadTemporaryContainers();
    void UnloadAssetsOfType(PK_eAssetType type);
    PK_TextureAsset * LoadTexture(const PK_String &sName, const PK_String &sContainerName);
    PK_SpriteSetAsset * LoadSpriteSet(const PK_String &sName, const PK_String &sContainerName);
    PK_SpriteAsset * LoadSprite(const PK_String &sName, const PK_String &sContainerName);
    PK_SoundAsset * LoadSoundEffect(const PK_String &sName, const PK_String &sContainerName);
    PK_MusicAsset * LoadMusic(const PK_String &sName, const PK_String &sContainerName);
    PK_FontAsset * LoadFont(const PK_String &sName, const PK_String &sContainerName);
    PK_ObjectPropertiesAsset * LoadTypeProperties(const PK_String &sName, const PK_String &sContainerName);
    PK_SettingsAsset * LoadSettings(const PK_String &sName, const PK_String &sContainerName);
    PK_ScriptAsset & LoadScript(const PK_String &sName, const PK_String &sContainerName);
    PK_FileAsset & LoadFile(const PK_String &sName, const PK_String &sContainerName = "");
    PK_StringAsset & LoadStrings(const PK_String &sName, const PK_String &sContainerName = "");
    inline PK_List<PK_AssetContainer *> * GetContainers() { return &m_AssetContainers; }

private:
	PK_Asset * LoadAsset(const PK_String &sName, PK_String sContainerName, PK_eAssetType type);
};

} // namespace

#endif