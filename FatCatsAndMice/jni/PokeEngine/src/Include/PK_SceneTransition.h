#ifndef _PK_SCENETRANSITION_H_
#define _PK_SCENETRANSITION_H_

#include "PK_Component.h"
#include "PK_GameTimer.h"

namespace PK {

class PK_SceneTransition : public PK_Component
{
public:
    virtual void OnInitialize() {}
    virtual void OnStart() {}
    virtual void OnUpdate(const PK_GameTimer &time) {}
    virtual void OnDraw() {}
    
    bool HasEnded() { return true; } // FIXME
};

}

#endif
