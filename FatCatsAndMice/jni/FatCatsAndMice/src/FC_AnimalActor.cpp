#include <PokeEngine.h>
#include "FC_AnimalActor.h"     
#include "FC_Consts.h"            

//
FC_AnimalActor::FC_AnimalActor(FC_eActorType type) :
    FC_Actor(type)
{  
    m_pSadHeadSpriteAsset = NULL;
    m_pHappyHeadSpriteAsset = NULL;
    m_pShirtSpriteAsset = NULL;

    // Head sprite
    m_pHeadSprite = new PK::PK_Sprite(GetName() + "_head");
    AddControl(m_pHeadSprite);
     
    // Shirt sprite
    m_pShirtSprite = new PK::PK_Sprite(GetName() + "_shirt");
    AddControl(m_pShirtSprite);
}

// 
void FC_AnimalActor::OnInitialize()
{
	FC_Actor::OnInitialize();
    SetHappyFace();
    m_pHeadSprite->SetPosition(GetSpriteAsset()->GetCollisionBox(0).GetCenter());

    if (m_pShirtSpriteAsset != NULL)
    {
        m_pShirtSprite->SetSprite(m_pShirtSpriteAsset);
        m_pShirtSprite->SetPosition(GetSpriteAsset()->GetCollisionBox(1).GetCenter());
        m_pShirtSprite->SetVisible(false);
    }
}

//
void FC_AnimalActor::OnLoad()
{
	FC_Actor::OnLoad();

    m_pHappyHeadSpriteAsset = PK::PokeEngine.GetAssetManager().LoadSprite(m_sHappyHeadSpriteAssetName, GetAssetContainerName());
    m_pSadHeadSpriteAsset = PK::PokeEngine.GetAssetManager().LoadSprite(m_sSadHeadSpriteAssetName, GetAssetContainerName());

    if (m_sShirtSpriteAssetName != "")
    {
        m_pShirtSpriteAsset = PK::PokeEngine.GetAssetManager().LoadSprite(m_sShirtSpriteAssetName, GetAssetContainerName());
    }
}


//
void FC_AnimalActor::Copy(PK::PK_SceneControl &copyFrom)
{
	FC_Actor::Copy(copyFrom);
    FC_AnimalActor *pActor = (FC_AnimalActor *)&copyFrom;

    m_sHappyHeadSpriteAssetName = pActor->m_sHappyHeadSpriteAssetName;
    m_sSadHeadSpriteAssetName = pActor->m_sSadHeadSpriteAssetName;
    m_sShirtSpriteAssetName = pActor->m_sShirtSpriteAssetName;

    m_pSadHeadSpriteAsset = pActor->m_pSadHeadSpriteAsset;

    m_pHappyHeadSpriteAsset = pActor->m_pHappyHeadSpriteAsset;

    m_pHappyHeadSpriteAsset = pActor->m_pHappyHeadSpriteAsset;

    m_pShirtSpriteAsset = pActor->m_pShirtSpriteAsset;

}
 
//
void FC_AnimalActor::SetWithShirt(bool bWithShirt)
{
    if (m_pShirtSpriteAsset == NULL && bWithShirt)
    {
        throw PK::PK_GameException("Actor cannot have a shirt.", __FILE__, __LINE__);
    }
    m_pShirtSprite->SetVisible(bWithShirt);
}

//
void FC_AnimalActor::SetHappyFace()
{
    m_pHeadSprite->SetSprite(m_pHappyHeadSpriteAsset);
}

//
void FC_AnimalActor::SetSadFace()
{
    m_pHeadSprite->SetSprite(m_pSadHeadSpriteAsset);
}

//
void FC_AnimalActor::OnKill()
{ 
    SetFps(30);
    m_pShirtSprite->SetFps(30);
    SetSadFace();
}