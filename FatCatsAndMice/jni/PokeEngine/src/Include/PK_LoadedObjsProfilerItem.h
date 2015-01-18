#ifndef _PK_LOADEDOBJSPROFILERITEM_H_
#define _PK_LOADEDOBJSPROFILERITEM_H_

#include "PK_String.h"
#include "PK_ProfilerItem.h"

namespace PK {

    
class PK_LoadedObjsProfilerItem : public PK_ProfilerItem
{
private:
    
public:
    PK_LoadedObjsProfilerItem(const PK_String &sName, PK_Profiler & owner);
};

}

#endif
