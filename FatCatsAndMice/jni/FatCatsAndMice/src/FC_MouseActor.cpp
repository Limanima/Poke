#include <PokeEngine.h>
#include "FC_MouseActor.h"              
#include "FC_GameSession.h"    

//
FC_MouseActor::FC_MouseActor() :
    FC_AnimalActor(ActorType_Mouse)
{

}

//
FC_MouseActor::FC_MouseActor(int iMouseNumber) :
    FC_AnimalActor(ActorType_Mouse)
{  
    PK::PK_String spriteRes; 
    spriteRes.Format(FCAM_SPRITESET_MOUSE_FALLING, iMouseNumber);
    SetBodySpriteAssetName(spriteRes);
     
    spriteRes.Format(FCAM_SPRITESET_MOUSE_HAPPY_HEAD, iMouseNumber);
    SetHappyHeadSpriteAssetName(spriteRes);

    spriteRes.Format(FCAM_SPRITESET_MOUSE_SAD_HEAD, iMouseNumber);
    SetSadHeadSpriteAssetName(spriteRes);

    SetShirtSpriteAssetName(FCAM_SPRITE_CAT_SHIRT);
	//		SetBackgroundColor(PK_COLOR_GRAY);

} 

//
FC_MouseActor & FC_MouseActor::CreateRandomMouse(FC_GameSession & session)
{
    int nrMiceToRandomize = 1; // depende dos settings, gatos do tipo 2 e 3 estao configurados por tempo
    if (session.IsLevelValid(TimmingLevel_Mouse2))
    {
        nrMiceToRandomize++;
    }
    if (session.IsLevelValid(TimmingLevel_Mouse3))
    {
        nrMiceToRandomize++;
    }

    int iMouseNr = PK::PK_RandomGenerator::GetRandNumber(nrMiceToRandomize);

    return PK::PokeEngine.GetLibrary().GetControlInstance<FC_MouseActor>(FCAM_LIB_ITEM_MOUSE_IDX + iMouseNr);
}
