#ifndef _PK_EFFECT_H_
#define _PK_EFFECT_H_

#include "PK_Object.h"
#include "PK_GameTimer.h"
#include "PK_Vector3.h"
#include "PK_Color.h"


namespace PK {

class PK_EffectsBlender;
    
class PK_Effect : public PK_Object
{
protected:
    PK_EffectsBlender * m_pBlender;
    // Tudo V3 para suporte 3D
    PK_Vector3        m_vPositionDelta;
    PK_Vector3        m_vRotationDelta;
    PK_Vector3        m_vScale;
    PK_Color          m_Color;
    bool              m_bEnded;
    bool              m_bActive;
    bool              m_bPersistent; // If false, effect is removed on end

public:
    PK_Effect(const PK_String &sName);
    ~PK_Effect();
    void FreeResources();
    virtual void OnUpdate(const PK_GameTimer &time) = 0;
    void OnUnload();
    virtual void InternalReset();
    virtual void Reset() { }
    void RemoveFromBlender();

    void SetBlender(PK_EffectsBlender &blender);
    inline PK_EffectsBlender *GetBlender() { return m_pBlender; }
    inline PK_Vector3 GetPositionDelta() { return m_vPositionDelta; }
    inline PK_Vector3 GetRotationDelta() { return m_vRotationDelta; }
    inline PK_Vector3 GetScale() { return m_vScale; }
    inline PK_Color GetColor() { return m_Color; }
    inline bool HasEnded() { return m_bEnded; }
    inline void SetEnded(bool bEnded) { m_bEnded = bEnded; }
    inline bool BelongsToBlender(PK_EffectsBlender &blender) { return m_pBlender == &blender; }
    
    // Active
    inline bool IsActive() { return m_bActive; }
    inline void SetActive(bool bActive) { m_bActive = bActive; }
    
    // Persistent
    inline void SetPersistent(bool bPersistent) { m_bPersistent = bPersistent; }
    inline bool IsPersistent() { return m_bPersistent; }
    
};

}

#endif
