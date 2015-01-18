#include "PK_Consts.h"
#include "PK_Globals.h"
#include "PK_LoadedObjsProfilerItem.h"

namespace PK {

PK_LoadedObjsProfilerItem::PK_LoadedObjsProfilerItem(const PK_String &sName, PK_Profiler & owner) :
    PK_ProfilerItem(sName, owner)
{
}

} // namespace
