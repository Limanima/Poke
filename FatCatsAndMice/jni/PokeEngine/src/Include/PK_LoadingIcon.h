#ifndef _PK_LODINGICON_H_
#define _PK_LODINGICON_H_

#include "PK_SceneControl.h"

namespace PK {
    
class PK_LoadingIcon : public PK_SceneControl
{
public:
    PK_LoadingIcon(const PK_String &sName):
      PK_SceneControl(sName) { }
};
    
} // namespace

#endif
