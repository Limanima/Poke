#ifndef _FCAM_FC_Button_H
#define _FCAM_FC_Button_H

#include <PokeEngine.h>
#include "FC_Types.h"   

class FC_Button : public PK::PK_Panel
{ 

public:
    FC_Button(const PK::PK_String &sName, FC_eButtonType buttonType);
    void OnInitialize();
};

#endif
