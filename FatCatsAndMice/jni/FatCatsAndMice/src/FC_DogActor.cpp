#include <PokeEngine.h>
#include "FC_DogActor.h"      


FC_DogActor::FC_DogActor() :
    FC_AnimalActor(ActorType_Dog)
{   
    SetHappyHeadSpriteAssetName(FCAM_SPRITESET_DOG_HAPPY_HEAD);
    SetSadHeadSpriteAssetName(FCAM_SPRITESET_DOG_SAD_HEAD);
    SetBodySpriteAssetName(FCAM_SPRITESET_DOG_BODY);
} 
