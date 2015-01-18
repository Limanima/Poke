#ifndef _PK_COMPONENT_H_
#define _PK_COMPONENT_H_

#include "PK_Object.h"
#include "PK_GameTimer.h"

namespace PK {

// Base de todas as classes do engine
// 
class PK_Component : public PK_Object
{
private:
    bool m_bActive;
    bool m_bVisible;
    PK_Object * m_pParent;
 
public:
    PK_Component(const PK_String &sName = "");
    virtual ~PK_Component();
    void SetParent(PK_Object * pObject);

    virtual void OnLoad() { }
    virtual void OnInitialize() { }
    virtual void OnUpdate(const PK_GameTimer &timer) { }
    virtual void OnUnInitialize() { }
    virtual void OnUnload() { }
    virtual void OnDraw() { }
    virtual void OnEnterBackground() {}
    virtual void OnEnterForeground() {}

    void InternalOnEnterBackground();
    void InternalOnEnterForeground();

    virtual inline void SetVisible(bool bVisible) { m_bVisible = bVisible; }
    inline bool IsVisible() { return m_bVisible; }
    inline void SetActive(const bool bActive) { m_bActive = bActive; }
    inline bool IsActive() { return m_bActive; }
    inline PK_Object * GetParent() { return m_pParent; }
};

}

#endif