#ifndef _PK_FPSCOUNTERPROFILERITEM_H_
#define _PK_FPSCOUNTERPROFILERITEM_H_

#include "PK_String.h"
#include "PK_ProfilerItem.h"
#include "PK_Label.h"

namespace PK {

    
class PK_FPSCounterProfilerItem : public PK_ProfilerItem
{

private:
    unsigned int        m_uiFPSCount;
    unsigned int        m_uiEllapsedTime;
    PK_Label           *m_pLabel;
    
public:
    PK_FPSCounterProfilerItem(const PK_String &sName, PK_Profiler & owner);
    void OnUpdate(const PK_GameTimer &time);
    void OnDraw();
};

}

#endif
