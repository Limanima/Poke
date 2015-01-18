#include "PK_EffectsBlender.h"
#include "PK_Exceptions.h"
#include "PK_Assert.h"

namespace PK {

PK_EffectsBlender::PK_EffectsBlender(PK_SceneControl &parent, const PK_String &sName):
	PK_Object(sName)
{
    SetTypeName("PK_EffectsBlender");
    m_pParent = &parent;
    // Nao contar a referencia par ao pa( por causa das referencias circulares)
  //  m_pParent->Grab();
}

//
PK_EffectsBlender::~PK_EffectsBlender()
{
    FreeResources();
}

//
void PK_EffectsBlender::FreeResources()
{
    for(PK_ListIterator(PK_Effect *) itor = m_Effects.Begin(); itor != m_Effects.End(); itor++)
    {
        (*itor)->OnUnload();
        (*itor)->Release();
    }

    m_Effects.Clear();
    m_pParent = NULL;
}

//
void PK_EffectsBlender::OnUpdate(const PK_GameTimer &time)
{
    if (m_Effects.GetCount() == 0)      
    {
        return;
    }

    Reset();
    bool bApply = false;
    for(PK_ListIterator(PK_Effect *) itor = m_Effects.Begin(); itor != m_Effects.End(); )
    {
        PK_Effect *pEffect = (*itor);
        itor++;
        if (pEffect->IsActive())
        {
            pEffect->OnUpdate(time);
            m_vPositionDelta += pEffect->GetPositionDelta();
            m_vRotationDelta += pEffect->GetRotationDelta();
            m_vScale *= pEffect->GetScale();
            m_Color = pEffect->GetColor();
            bApply = true;
            
            if (pEffect->HasEnded())
            {
                pEffect->SetActive(false);
                if (pEffect->IsPersistent() == false)
                {
                    RemoveEffect(*pEffect);
                }
            }
        }
    }

    if (bApply)
    {
        m_pParent->ApplyEffects();
    }
}

//
void PK_EffectsBlender::OnUnload()
{
    FreeResources();
}

//
void PK_EffectsBlender::AddEffect(PK_Effect &effect)
{
    if (effect.GetBlender() != NULL)
    {
        throw PK_SystemException("Effect named '%s' cannot be added to the blender because it is already added to another blended.",
            __FILE__, __LINE__, effect.GetName().c_str());
    }
    m_Effects.Add(&effect);

    effect.Grab();
    effect.SetBlender(*this);
}
    
//
void PK_EffectsBlender::RemoveEffect(PK_Effect &effect)
{
    if (!effect.BelongsToBlender(*this))
    {
        throw PK_SystemException("Effect named '%s' cannot be removed because it doesn't belong to the blender.",
                                 __FILE__, __LINE__, effect.GetName().c_str());       
    }
    m_Effects.Remove(&effect);
    effect.Release();
}

//
void PK_EffectsBlender::Reset()
{
    m_vPositionDelta = PK_Vector3(0.0f, 0.0f, 0.0f);
    m_vRotationDelta = PK_Vector3(0.0f, 0.0f, 0.0f);
    m_vScale = PK_Vector3(1.0f, 1.0f, 1.0f);
    m_Color = PK_COLOR_WHITE;
}

}