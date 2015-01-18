#include "PK_Consts.h"
#include "PK_AssetManager.h"
#include "PK_Exceptions.h"
#include "PK_NullArgumentException.h"
#include "PK_TextureAsset.h"
#include "PK_SpriteSetAsset.h"
#include "PK_SoundAsset.h"
#include "PK_MusicAsset.h"
#include "PK_FileAsset.h"
#include "PK_StringAsset.h"
#include "PK_ClassFactory.h"
#include "PK_Path.h"
#include "PK_Log.h"
#include "PK_TypeConverters.h"

namespace PK {

PK_AssetManager::PK_AssetManager(const PK_String &sName) :
  PK_Component(sName)
{
	SetTypeName("PK_AssetManager");
}

void PK_AssetManager::OnInitialize()
{
    // Criar um container por defeito, convem ter pelo menos um, nao obrigamos o user a criar um
    // Os controlos do engine utilizam este por defeito
    CreateAssetContainer(PK_ASSET_CONTAINER_NAME);
}

//
void PK_AssetManager::OnUnInitialize()
{
	for(PK_ListIterator(PK_AssetContainer *) itor = m_AssetContainers.Begin(); itor != m_AssetContainers.End(); itor++)
	{
        PK_AssetContainer *pAssetContainer = (*itor);
        pAssetContainer->Unload();
		pAssetContainer->Release();
	}
    m_AssetContainers.Clear();
}

// Devolve um AssetContainer atraves do ID
// Se nao encontrar devolve NULL
PK_AssetContainer * PK_AssetManager::GetContainer(const PK_String &sName)
{
	for(PK_ListIterator(PK_AssetContainer *) itor = m_AssetContainers.Begin(); itor != m_AssetContainers.End(); itor++)
	{
		if ((*itor)->GetName() == sName)
		{
			return (*itor);
		}
	}

	return NULL;
}


// Devolve true se o AssetContainer com id iContainerId existir 
bool PK_AssetManager::ContainsContainer(const PK_String &sName)
{
	return (GetContainer(sName) != NULL);
}

//
void PK_AssetManager::UnloadTemporaryContainers()
{
}

// Liberta todos os assets de um determinado tipo
void PK_AssetManager::UnloadAssetsOfType(PK_eAssetType type)
{
	for(PK_ListIterator(PK_AssetContainer *) itor = m_AssetContainers.Begin(); itor != m_AssetContainers.End(); itor++)
	{
        (*itor)->UnloadAssetsOfType(type);
	}
}
    
// Adiciona um novo AssetContainer
// Se ja exitir um Container com o mesmo ID, lanca excepcao 
// Nome do container tem que estar preenchido
void PK_AssetManager::CreateAssetContainer(const PK_String &sName)
{
	if (sName.length() == 0)
	{
		throw PK_NullArgumentException("name", __FILE__, __LINE__);
	}

	if (ContainsContainer(sName))
	{
		throw PK_SystemException("Container with id %s already exists.", __FILE__, __LINE__, sName.c_str());
	}
	PK_AssetContainer * pContainer = new PK_AssetContainer(sName);
    if (pContainer == NULL)
    {
        throw PK_OutOfMemoryException("PK_AssetContainer", sizeof(PK_AssetContainer), __FILE__, __LINE__);
    }
	pContainer->Grab();
	m_AssetContainers.Add(pContainer);
}

// Carrega um asset do tipo textura
PK_TextureAsset * PK_AssetManager::LoadTexture(const PK_String &sName, const PK_String &sContainerName)
{
	return (PK_TextureAsset *) LoadAsset(sName, sContainerName, AssetType_Texture);
}

// Carrega um SpriteSet
PK_SpriteSetAsset * PK_AssetManager::LoadSpriteSet(const PK_String &sName, const PK_String &sContainerName)
{
	return (PK_SpriteSetAsset *) LoadAsset(sName, sContainerName, AssetType_SpriteSet);
}

// Carrega um sprite
PK_SpriteAsset * PK_AssetManager::LoadSprite(const PK_String &sName, const PK_String &sContainerName)
{
   	if (sName.length() == 0)
	{
		throw PK_NullArgumentException("name", __FILE__, __LINE__);
	}

    PK_String sSpriteSetName = PK_Path::GetPathName(sName);
    PK_String sSpriteName = PK_Path::GetFileName(sName);
    
    PK_SpriteSetAsset * pSpriteSetRes = LoadSpriteSet(sSpriteSetName, sContainerName);
    if (pSpriteSetRes == NULL)
	{
		throw PK_SystemException("Could not load SpriteSet named '%s'.", __FILE__, __LINE__, sSpriteSetName.c_str());
	}
    
    PK_SpriteAsset * pSpriteRes = pSpriteSetRes->GetSprite(sSpriteName);
    if (pSpriteRes == NULL)
	{
		throw PK_SystemException("Could not find Sprite named '%s' in SpriteSet '%s.'", __FILE__, __LINE__, sSpriteName.c_str(), sSpriteSetName.c_str());
	}

    return pSpriteRes;
}

//
PK_SoundAsset * PK_AssetManager::LoadSoundEffect(const PK_String &sName, const PK_String &sContainerName)
{
	return (PK_SoundAsset *) LoadAsset(sName, sContainerName, AssetType_SoundEffect);
}
    
//
PK_MusicAsset * PK_AssetManager::LoadMusic(const PK_String &sName, const PK_String &sContainerName)
{
	return (PK_MusicAsset *) LoadAsset(sName, sContainerName, AssetType_Music);
}
    
//
PK_FontAsset * PK_AssetManager::LoadFont(const PK_String &sName, const PK_String &sContainerName)
{
    return (PK_FontAsset *) LoadAsset(sName, sContainerName, AssetType_Font);
}

//
PK_ObjectPropertiesAsset * PK_AssetManager::LoadTypeProperties(const PK_String &sName, const PK_String &sContainerName)
{
    return (PK_ObjectPropertiesAsset *) LoadAsset(sName, sContainerName, AssetType_ObjectProperties);
}

//
PK_SettingsAsset * PK_AssetManager::LoadSettings(const PK_String &sName, const PK_String &sContainerName)
{
    return (PK_SettingsAsset *) LoadAsset(sName, sContainerName, AssetType_Settings);
}

//
PK_ScriptAsset & PK_AssetManager::LoadScript(const PK_String &sName, const PK_String &sContainerName)
{
    return *(PK_ScriptAsset *) LoadAsset(sName, sContainerName, AssetType_Script);
}

//
PK_FileAsset & PK_AssetManager::LoadFile(const PK_String &sName, const PK_String &sContainerName)
{
    return *(PK_FileAsset *) LoadAsset(sName, sContainerName, AssetType_File);
}

//
PK_StringAsset & PK_AssetManager::LoadStrings(const PK_String &sName, const PK_String &sContainerName)
{
    return *(PK_StringAsset *) LoadAsset(sName, sContainerName, AssetType_File);
}

//
PK_Asset * PK_AssetManager::LoadAsset(const PK_String &sName, PK_String sContainerName, PK_eAssetType type)
{
    if (sContainerName == "")
    {
        sContainerName = PK_ASSET_CONTAINER_NAME;
    }
    PK_Log::WriteInfo(PK_LOG_TAG, "Loading asset... Container[%s] Name[%s] Type[%s]", sContainerName.c_str(), sName.c_str(), PK_TypeConverters::AssetTypeToStr(type).c_str());


	PK_AssetContainer * pContainer = GetContainer(sContainerName);
    if (pContainer == NULL)
    {
        throw PK_SystemException("Asset container named %s could not be found.", __FILE__, __LINE__, sContainerName.c_str());
    }

	// Verificar se ja existe. Se ja existir apenas devolvemos a instancia
	PK_Asset * pAsset = pContainer->GetAsset(sName, type);
	if (pAsset != NULL)
	{
		return pAsset;
	}

	pAsset = PK_ClassFactory::CreateAsset(type, *pContainer);
	if (pAsset == NULL)
	{
		throw PK_SystemException("ClassFactory could not create Asset of type %d", __FILE__, __LINE__, type);
	}
    pAsset->SetAssetName(sName);
    pAsset->Load();
	pContainer->AddAsset(pAsset);

	return pAsset;
}

    
} // namespace
