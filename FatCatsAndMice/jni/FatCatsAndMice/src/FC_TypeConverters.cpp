#include <PokeEngine.h>
#include "FC_TypeConverters.h"

// Static
PK::PK_String FC_TypeConverters::ActorTypeToStr(FC_eActorType actorType)
{
  switch(actorType)
  {
    case ActorType_Cat:
        return "Cat";
 
    case ActorType_Mouse:
        return "Mouse";

    case ActorType_Dog:
        return "Dog";

    case ActorType_Object:
        return "InanimateObject";

    default:
      throw PK::PK_GameException("Type conversion error. Could not convert ActorType '%d' to a string.", __FILE__, __LINE__, actorType);
  }
}
// Static
FC_eTimmingLevel FC_TypeConverters::StrToTimmingLevel(const PK::PK_String &sTime)
{
    if (sTime == "Mouse2")
        return TimmingLevel_Mouse2;
    if (sTime == "Mouse3")
        return TimmingLevel_Mouse3;
    if (sTime == "Cat2")
        return TimmingLevel_Cat2;
    if (sTime == "Cat3")
        return TimmingLevel_Cat3;
    if (sTime == "Dog")
        return TimmingLevel_Dog;
    if (sTime == "Inanimate")
        return TimmingLevel_Inanimate;
    if (sTime == "Shirts")
        return TimmingLevel_Shirts;

    throw PK::PK_GameException("Type conversion error. Could not convert string '%s' to FC_eTimmingLevel.", __FILE__, __LINE__, sTime.c_str());
}


