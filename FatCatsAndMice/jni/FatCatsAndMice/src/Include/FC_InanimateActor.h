#ifndef _FCAM_INANIMATEACTOR_H_
#define _FCAM_INANIMATEACTOR_H_

#include <PokeEngine.h>
#include "FC_Actor.h"
#include "FC_Types.h"
#include "FC_Consts.h"

class FC_InanimateActor : public FC_Actor
{ 
private:
    PK::PK_Array<PK::PK_SpriteAsset *> m_SpriteAssets;
    
public:
    FC_InanimateActor();
    void OnLoad();
    void SetInanimteType(int iType);
    void Copy(PK::PK_SceneControl &copyFrom);
};

#endif
