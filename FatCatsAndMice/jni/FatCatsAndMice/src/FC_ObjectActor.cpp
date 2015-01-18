#include <PokeEngine.h>
#include "FC_ObjectActor.h"              
#include "FC_Consts.h"         

//
FC_ObjectActor::FC_ObjectActor() :
    FC_Actor(ActorType_Object)
{
	m_ObjectType = ObjectActorType_None;
}

//
void FC_ObjectActor::OnLoad()
{

}

//
void FC_ObjectActor::SetObjectType(FC_eObjectActorType type)
{
	m_ObjectType = type;
	switch(m_ObjectType)
	{
		case ObjectActorType_Fridge:
			break;
		case ObjectActorType_Microwave:
			break;
		case ObjectActorType_Pizza:
			break;
		default:
			break;
	}
}


//
FC_ObjectActor & FC_ObjectActor::CreateRandomObject()
{
    return PK::PokeEngine.GetLibrary().GetControlInstance<FC_ObjectActor>(FCAM_LIB_ITEM_OBJECT_IDX);
}

