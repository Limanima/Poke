#ifndef _PK_EFFECTSBLENDER_H_
#define _PK_EFFECTSBLENDER_H_

#include "PK_Object.h"
#include "PK_SceneControl.h"
#include "PK_List.h"
#include "PK_Effect.h"

namespace PK {

class PK_EffectsBlender : public PK_Object
{
private:
    PK_List<PK_Effect *> m_Effects;
    PK_SceneControl     *m_pParent;

    PK_Vector3        m_vPositionDelta;
    PK_Vector3        m_vRotationDelta;
    PK_Vector3        m_vScale;
    PK_Color          m_Color;

public:
    PK_EffectsBlender(PK_SceneControl &parent, const PK_String &sName);
    ~PK_EffectsBlender();
    void FreeResources();
    void OnUpdate(const PK_GameTimer &time);
    void OnUnload();
    void AddEffect(PK_Effect &effect);
    void RemoveEffect(PK_Effect &effect);
    void Reset();

    inline PK_Vector3 GetPositionDelta() { return m_vPositionDelta; }
    inline PK_Vector3 GetRotationDelta() { return m_vRotationDelta; }
    inline PK_Vector3 GetScale() { return m_vScale; }
    inline PK_Color GetColor() { return m_Color; }
    inline bool WithEffects() { return (m_Effects.GetCount() > 0); }

};

}

#endif
