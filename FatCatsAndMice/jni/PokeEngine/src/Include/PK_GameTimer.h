#ifndef _PK_GAMETIMER_H_
#define _PK_GAMETIMER_H_

#include "PK_Timer.h"

namespace PK {
    
class PK_GameTimer : public PK_Timer
{

public:
  PK_GameTimer() :
      PK_Timer("gameTimer")
    {
        SetTypeName("PK_GameTimer");
     }
};
    
} // namespace

#endif
