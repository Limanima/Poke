#ifndef _PK_PROFILERITEM_H_
#define _PK_PROFILERITEM_H_

#include "PK_SceneControl.h"
#include "PK_String.h"
#include "PK_GameTimer.h"

namespace PK {

class PK_Profiler;

class PK_ProfilerItem : public PK_Object
{
private:
    PK_Profiler *m_pProfiler;
    PK_SceneControl * m_pUIControl; // SceneControl utilizado na UI do item (nao e obrigatorio ter UI)
    bool    m_bVisible;
    bool    m_bActive;

public:
    PK_ProfilerItem(const PK_String &sName, PK_Profiler & owner);
    ~PK_ProfilerItem();
    void InternalUnload();
    virtual void OnInitialize() {}
    virtual void OnUpdate(const PK_GameTimer &time) {}
    virtual void OnDraw() {}
    void SetUI(PK_SceneControl * pUIControl); // Passar pointer porque aceita NULL para fazer remover a UI
    inline PK_SceneControl * GetUI() { return m_pUIControl; }
    inline bool WithUI() { return (m_pUIControl != NULL); }
    // Visible
    inline bool IsVisible() { return m_bVisible; }
    void SetVisible(bool bVisible);
    inline PK_Profiler & GetProfiler() { return *m_pProfiler; }
};
    
} // namespace

#endif
