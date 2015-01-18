#ifndef _FCAM_MOUSEACTOR_H_
#define _FCAM_MOUSEACTOR_H_

#include <PokeEngine.h>
#include "FC_AnimalActor.h"

class FC_GameSession;

class FC_MouseActor : public FC_AnimalActor
{ 
private:

public:
    FC_MouseActor();
    FC_MouseActor(int iCatNumber);
    static FC_MouseActor & CreateRandomMouse(FC_GameSession & session);
};

#endif
