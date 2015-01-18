#include "PK_Globals.h"
#include "PK_ProfilerItem.h"
#include "PK_Profiler.h"

namespace PK {

//
PK_ProfilerItem::PK_ProfilerItem(const PK_String &sName, PK_Profiler &owner) :
  PK_Object(sName)
{
    m_pProfiler = &owner;
    m_pUIControl = NULL;
    m_bVisible = false;
    m_bActive = false;
}

//
PK_ProfilerItem::~PK_ProfilerItem()
{
    InternalUnload();
}

//
void PK_ProfilerItem::InternalUnload()
{
    if (m_pUIControl != NULL)
    {
        m_pUIControl->InternalUnload();
    }
    SetUI(NULL);
}


//
void PK_ProfilerItem::SetUI(PK_SceneControl * pUIControl)
{
    if (m_pUIControl != NULL)
    {
        m_pUIControl->Release();
        m_pUIControl = NULL;
    }
    m_pUIControl = pUIControl;
    if (m_pUIControl != NULL)
    {
        m_pUIControl = pUIControl;
        m_pUIControl->Grab();
    }
}
//    
void PK_ProfilerItem::SetVisible(bool bVisible)
{
    m_bVisible = bVisible;
    if (m_pUIControl != NULL)
    {
        m_pUIControl->SetVisible(bVisible);
    }
}

} // namespace