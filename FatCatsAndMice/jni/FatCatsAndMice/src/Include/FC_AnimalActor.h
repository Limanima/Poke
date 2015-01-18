#ifndef _FCAM_ANIMALACTOR_H_
#define _FCAM_ANIMALACTOR_H_

#include <PokeEngine.h>
#include "FC_Actor.h"
#include "FC_Types.h"
#include "FC_Consts.h"

class FC_AnimalActor: public FC_Actor
{ 
private:
    PK::PK_String   m_sHappyHeadSpriteAssetName;
    PK::PK_String   m_sSadHeadSpriteAssetName;
    PK::PK_String   m_sShirtSpriteAssetName;

    PK::PK_Sprite * m_pHeadSprite;
    PK::PK_Sprite * m_pShirtSprite;

    PK::PK_SpriteAsset * m_pSadHeadSpriteAsset;
    PK::PK_SpriteAsset * m_pHappyHeadSpriteAsset;
    PK::PK_SpriteAsset * m_pShirtSpriteAsset;
 
public:
    FC_AnimalActor(FC_eActorType type);
    void Copy(PK::PK_SceneControl &copyFrom);
    void OnInitialize();
    void OnLoad();
    void SetHappyFace();
    void SetSadFace();
    void OnKill();
    void SetWithShirt(bool bWithShirt);

public:
    inline bool CanWearShirt() { return m_pShirtSpriteAsset != NULL; }
    inline void SetHappyHeadSpriteAssetName(const PK::PK_String &sName) { m_sHappyHeadSpriteAssetName = sName; }
    inline void SetSadHeadSpriteAssetName(const PK::PK_String &sName) { m_sSadHeadSpriteAssetName = sName; }
    inline void SetShirtSpriteAssetName(const PK::PK_String &sName) { m_sShirtSpriteAssetName = sName; }

};

#endif
