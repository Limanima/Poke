#ifndef _PK_POINTERINFOFILERITEM_H_
#define _PK_POINTERINFOFILERITEM_H_

#include "PK_String.h"
#include "PK_ProfilerItem.h"
#include "PK_Label.h"

namespace PK {

// Dá informação sobre o dispositivo apontador (rato por exemplo)
class PK_PointerInfoProfilerItem : public PK_ProfilerItem
{

private:
    PK_Vector2          m_vPosition;
    PK_Vector2          m_vPreviousPosition;
    PK_Label           *m_pLabel;
    
public:
    PK_PointerInfoProfilerItem(const PK_String &sName, PK_Profiler & owner);
    void OnUpdate(const PK_GameTimer &time);
    void OnDraw();
};

}

#endif
