#ifndef _FCAM_CATACTOR_H_
#define _FCAM_CATACTOR_H_

#include <PokeEngine.h>
#include "FC_AnimalActor.h"
class FC_GameSession;
class FC_GameSettings;

class FC_CatActor : public FC_AnimalActor
{ 

public:
    FC_CatActor();
    FC_CatActor(int iCatNumber);
    static FC_CatActor & CreateRandomCat(FC_GameSession & session);
};

#endif
