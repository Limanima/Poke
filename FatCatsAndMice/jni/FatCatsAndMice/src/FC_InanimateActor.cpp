#include <PokeEngine.h>
#include "FC_InanimateActor.h"
#include "FC_Consts.h"            

//
FC_InanimateActor::FC_InanimateActor() :
    FC_Actor(ActorType_Object)
{  
    m_SpriteAssets.SetSize(FCAM_TOTAL_INANIMATE);
}

//
void FC_InanimateActor::SetInanimteType(int iType)
{
    SetSprite(m_SpriteAssets[iType]);
    // Aqui vai ah martelada, elefantes n teem rotacao
    if (iType != FCAM_ELEPHANT)
    {
        SetRotation(PK::PK_RandomGenerator::GetRandNumber(30) - 15.0f);
    }
}


//
void FC_InanimateActor::OnLoad()
{
    FC_Actor::OnLoad();
    m_SpriteAssets[FCAM_FRIDGE] = PK::PokeEngine.GetAssetManager().LoadSprite(FCAM_SPRITE_FRIDGE, GetAssetContainerName());
    m_SpriteAssets[FCAM_CHEESE] = PK::PokeEngine.GetAssetManager().LoadSprite(FCAM_SPRITE_CHEESE, GetAssetContainerName());
    m_SpriteAssets[FCAM_ELEPHANT] = PK::PokeEngine.GetAssetManager().LoadSprite(FCAM_SPRITE_ELEPHANT, GetAssetContainerName());
    m_SpriteAssets[FCAM_FISH] = PK::PokeEngine.GetAssetManager().LoadSprite(FCAM_SPRITE_FISH, GetAssetContainerName());
   
}

//
void FC_InanimateActor::Copy(PK::PK_SceneControl &copyFrom)
{
    FC_Actor::Copy(copyFrom);
    FC_InanimateActor *pActor = (FC_InanimateActor *)&copyFrom;
    for(unsigned int i = 0; i < pActor->m_SpriteAssets.GetCount(); i++)
    {
        m_SpriteAssets[i] = pActor->m_SpriteAssets[i];
    }
}