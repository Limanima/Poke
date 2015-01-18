#ifndef _FCAM_TYPECONVERTERS_H_
#define _FCAM_TYPECONVERTERS_H_

#include "FC_Types.h"

class FC_TypeConverters 
{ 
public:
    static PK::PK_String ActorTypeToStr(FC_eActorType actorType);
    static PK::PK_String SignTypeToStr(FC_eActorType actorType);
    static FC_eTimmingLevel StrToTimmingLevel(const PK::PK_String &sTime);
};

#endif
