#include "PK_AssetContainer.h"
#include "PK_Exceptions.h"

namespace PK {

PK_AssetContainer::PK_AssetContainer(const PK_String &sName) 
{
    SetTypeName("PK_AssetContainer");
	SetName(sName);
	m_iContainerId = 0;
}

PK_AssetContainer::~PK_AssetContainer()
{
    Unload();
}

    
// Liberta todos os recursos
void PK_AssetContainer::Unload()
{
    for(PK_ListIterator(PK_Asset *) itor = m_Assets.Begin(); itor != m_Assets.End(); itor++)
    {
        PK_Asset *pAsset = (*itor);
        pAsset->Unload();
        pAsset->Release();
    }
    m_Assets.Clear();
}
    
// Adiciona um asset ao container. Se ja existir lanca excepcao
void PK_AssetContainer::AddAsset(PK_Asset * pAsset)
{
	if (pAsset == NULL)
	{
		throw PK_NullArgumentException("pAsset", __FILE__, __LINE__);
	}

	if (ContainsAsset(pAsset))
	{
		throw PK_SystemException("Asset named '%s' already exists in the cointainer '%s'.", __FILE__, __LINE__, pAsset->GetName().c_str(), GetName().c_str());
	}

	m_Assets.Add(pAsset);
	pAsset->Grab();
}

// Adiciona um asset do tipo textura, não é mais do que um overloading
void PK_AssetContainer::AddAsset(PK_TextureAsset * pAsset)
{
	AddAsset((PK_Asset *)pAsset);
}

// Devolve um asset atraves do nome
// Se o asset não existir devolve NULL
PK_Asset * PK_AssetContainer::GetAsset(const PK_String &sName, PK_eAssetType type)
{
	for(PK_ListIterator(PK_Asset *) itor = m_Assets.Begin(); itor != m_Assets.End(); itor++)
	{
        PK_Asset * pAsset =(*itor);
		if (pAsset->GetAssetName() == sName &&
            pAsset->GetAssetType() == type)
		{
			return pAsset;
		}
	}
	return NULL;
}
    

// Devolve true se o container contem um asset com o nome sName
bool PK_AssetContainer::ContainsAsset(const PK_String &sName, PK_eAssetType type)
{
	return ((GetAsset(sName, type) != NULL));
}

//
bool PK_AssetContainer::ContainsAsset(PK_Asset * pAsset)
{
    for(PK_ListIterator(PK_Asset *) itor = m_Assets.Begin(); itor != m_Assets.End(); itor++)
	{
		if ((*itor) == pAsset)
        {
            return true;
        }
    }
    return false;
}


// Liberta todos os assets de um determinado tipo
// Se outros objectos tiverem referencias, elas sao mantidas
void PK_AssetContainer::UnloadAssetsOfType(PK_eAssetType type)
{
    for(PK_ListIterator(PK_Asset *) itor = m_Assets.Begin(); itor != m_Assets.End(); )
	{
        PK_Asset *pAsset = (*itor);
		if (pAsset->GetAssetType() == type)
        {
            if (pAsset->GetRefCount() == 1)
            {
                pAsset->Unload();
            }
            pAsset->Release();
            m_Assets.Erase(itor++);
        }
        else
        {
            itor++;
        }

    }
}
    
} // namespace
