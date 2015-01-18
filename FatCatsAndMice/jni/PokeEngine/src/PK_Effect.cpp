#include "PK_Effect.h"
#include "PK_EffectsBlender.h"
#include "PK_Exceptions.h"

namespace PK {

PK_Effect::PK_Effect(const PK_String &sName):
	PK_Object(sName)
{
    SetTypeName("PK_Effect");
    m_pBlender = NULL;
    m_bActive = true;
    m_bPersistent = false;
    m_vPositionDelta = PK_Vector3(0.0f, 0.0f, 0.0f);
    m_vRotationDelta = PK_Vector3(0.0f, 0.0f, 0.0f);
    m_vScale = PK_Vector3(1.0f, 1.0f, 1.0f);
    m_Color = PK_COLOR_WHITE;
    m_bEnded = false;
}

//
PK_Effect::~PK_Effect()
{
    FreeResources();
}

//
void PK_Effect::FreeResources()
{
  /*  if (m_pBlender != NULL)
    {
        m_pBlender->Release();
        m_pBlender = NULL;
    }*/
}

//
void PK_Effect::OnUnload()
{
    FreeResources();
}

//
void PK_Effect::InternalReset()
{
    m_bEnded = false;
    Reset();
}
    
//
void PK_Effect::SetBlender(PK_EffectsBlender &blender)
{
    if (m_pBlender != NULL)
    {
        throw PK_SystemException("Cannot add effect named '%s' to blender because it is already added to a blender.", __FILE__, __LINE__, GetName().c_str());
    }
    m_pBlender = &blender;
    // Nao guardar referencias para o pai por causa das referencias circulares
  //  m_pBlender->Grab();
}
    
//
void PK_Effect::RemoveFromBlender()
{
    if (m_pBlender == NULL)
    {
        throw PK_SystemException("Cannot remove effect named '%s' from blender because it is not added to a blender.", __FILE__, __LINE__, GetName().c_str());
    }
    
    m_pBlender->RemoveEffect(*this);
  //  m_pBlender->Release();
    m_pBlender = NULL;
}
    
}