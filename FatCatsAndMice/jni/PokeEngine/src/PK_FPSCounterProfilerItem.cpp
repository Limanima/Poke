#include "PK_Consts.h"
#include "PK_Globals.h"
#include "PK_FPSCounterProfilerItem.h"
#include "PK_Label.h"

namespace PK {

PK_FPSCounterProfilerItem::PK_FPSCounterProfilerItem(const PK_String &sName, PK_Profiler & owner) :
    PK_ProfilerItem(sName, owner)
{
	SetTypeName("PK_FPSCounterProfilerItem");
    m_uiFPSCount = 0;
    m_uiEllapsedTime = 0; 

    // UI - apenas uma label
    m_pLabel = new PK_Label(sName + "_label");
    m_pLabel->SetFont(PK_FONT_NAME);
   // m_pLabel->SetBackgroundColor(PK_Color(1.0f, 1.0f, 1.0f, 1.0f));
    m_pLabel->SetColor(PK_COLOR_WHITE);
    m_pLabel->SetParentAlignment(ParentAlignment_Bottom);
    SetUI(m_pLabel);
}
    
//
void PK_FPSCounterProfilerItem::OnUpdate(const PK_GameTimer &time)
{
    m_uiEllapsedTime += time.GetEllapsedTime();
    if (m_uiEllapsedTime > 1000)
    {
        PK_String sText;
        sText.Format("%d", m_uiFPSCount);
        m_pLabel->SetText(sText);
        PK_Profiler::m_RemoteDebugger.AddFPSMessage(m_uiFPSCount);
        m_uiFPSCount = 0;
        m_uiEllapsedTime = m_uiEllapsedTime - 1000;
    }
}

//
void PK_FPSCounterProfilerItem::OnDraw()
{
    m_uiFPSCount++;
}

} // namespace
