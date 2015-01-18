#include <PokeEngine.h>
#include "FC_CatActor.h"              
#include "FC_Consts.h"         
#include "FC_GameSession.h"  
#include "FC_GameSettings.h"  
//
FC_CatActor::FC_CatActor() :
    FC_AnimalActor(ActorType_Cat)
{
}

//
FC_CatActor::FC_CatActor(int iCatNumber) :
    FC_AnimalActor(ActorType_Cat)
{  
    PK::PK_String spriteRes;
    spriteRes.Format(FCAM_SPRITESET_CAT_FALLING, iCatNumber);
    SetBodySpriteAssetName(spriteRes);

    spriteRes.Format(FCAM_SPRITESET_CAT_HAPPY_HEAD, iCatNumber);
    SetHappyHeadSpriteAssetName(spriteRes);

    spriteRes.Format(FCAM_SPRITESET_CAT_SAD_HEAD, iCatNumber);
    SetSadHeadSpriteAssetName(spriteRes);

    SetShirtSpriteAssetName(FCAM_SPRITE_MOUSE_SHIRT);
//	SetBackgroundColor(PK_COLOR_ORANGE);
}

//
FC_CatActor & FC_CatActor::CreateRandomCat(FC_GameSession & session)
{
    int nrCatsToRandomize = 1; // depende dos settings, gatos do tipo 2 e 3 estao configurados por tempo
    if (session.IsLevelValid(TimmingLevel_Cat2))
    {
        nrCatsToRandomize++;
    }
    if (session.IsLevelValid(TimmingLevel_Cat3))
    {
        nrCatsToRandomize++;
    }

    int iCatNr = PK::PK_RandomGenerator::GetRandNumber(nrCatsToRandomize);
    return PK::PokeEngine.GetLibrary().GetControlInstance<FC_CatActor>(FCAM_LIB_ITEM_CAT_IDX + iCatNr);
}

