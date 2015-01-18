#ifndef _FCAM_OBJECTACTOR_H_
#define _FCAM_OBJECTACTOR_H_

#include <PokeEngine.h>
#include "FC_Actor.h"

// Representa um actor inanimado tal como um frigorifico, ou microondas
class FC_ObjectActor : public FC_Actor
{ 
	FC_eObjectActorType m_ObjectType;

public:
    FC_ObjectActor();
	void OnLoad();
	void SetObjectType(FC_eObjectActorType type);
    static FC_ObjectActor & CreateRandomObject();
};

#endif
