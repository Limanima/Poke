#include "PK_Consts.h"
#include "PK_Globals.h"
#include "PK_InputManager.h"
#include "PK_PointerInfoProfilerItem.h"
#include "PK_Label.h"

namespace PK {

PK_PointerInfoProfilerItem::PK_PointerInfoProfilerItem(const PK_String &sName, PK_Profiler & owner) :
    PK_ProfilerItem(sName, owner)
{
	SetTypeName("PK_PointerInfoProfilerItem");

    m_vPreviousPosition = PK_Vector2(0, 0);
    // UI - apenas uma label
    m_pLabel = new PK_Label(sName + "_label");
    m_pLabel->SetFont(PK_FONT_NAME);
    m_pLabel->SetBackgroundColor(PK_Color(1.0f, 1.0f, 1.0f, 1.0f));
    m_pLabel->SetParentAlignment(ParentAlignment_Left | ParentAlignment_Bottom);
    SetUI(m_pLabel);
}
    
//
void PK_PointerInfoProfilerItem::OnUpdate(const PK_GameTimer &time)
{
    PK_Vector2 vPos = PokeEngine.GetInputManager().GetPointerPosition();

    if (m_vPreviousPosition != vPos)
    {
        PK_String sText;
        sText.Format("x:%4.1f y:%4.1f", vPos.x, vPos.y);
        m_pLabel->SetText(sText);
        m_vPreviousPosition = vPos;
    }
}

//
void PK_PointerInfoProfilerItem::OnDraw()
{

}

} // namespace
