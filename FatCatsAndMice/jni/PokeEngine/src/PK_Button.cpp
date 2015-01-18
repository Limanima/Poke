#include "PK_Consts.h"
#include "PK_Globals.h"
#include "PK_Button.h"
#include "PK_Effect.h"

namespace PK {

PK_Button::PK_Button(const PK_String &sName) :
    PK_2DSceneControl(sName)
{
	SetTypeName("PK_Button");
    m_pLabel = new PK_Label(sName + "_label");
    m_pLabel->SetParentAlignment(ParentAlignment_Center);
    m_pLabel->SetText("label");
    AddControl(m_pLabel);
    m_pPressEffect = NULL;
    m_ButtonPressed = false;
}

//
PK_Button::~PK_Button()
{
    FreeResources();
}

//
void PK_Button::FreeResources()
{
    SetClickEffect(NULL);
}
    
//
void PK_Button::InitFromDataFileRecord(PK_DataFileRecord &record)
{
    
}
    
//
void PK_Button::InternalUnload()
{
    FreeResources();    
}

// Chama o Update do proprio e dos filhos
void PK_Button::InternalUpdate(const PK_GameTimer &time)
{
    PK_2DSceneControl::InternalUpdate(time);
    if (m_pPressEffect != NULL &&
        m_pPressEffect->HasEnded() &&
        m_ButtonPressed)
    {
        InvokeOnClick();
        m_ButtonPressed = false;
        GetScene()->EnableInput();
    }
}
    
//
void PK_Button::SetFont(const PK_String &sAssetName)
{
    m_pLabel->SetFont(sAssetName);
}

//
void PK_Button::SetTextColor(const PK_Color &color)
{
    m_pLabel->SetColor(color);
}

//
void PK_Button::SetClickEffect(PK_Effect *pPressEffect)
{
    if (m_pPressEffect != NULL)
    {
        m_pPressEffect->RemoveFromBlender();
        m_pPressEffect->Release();
        
    }
    m_pPressEffect = pPressEffect;
    if (m_pPressEffect != NULL)
    {
        m_pPressEffect->Grab();
        m_pPressEffect->SetActive(false);
        m_pPressEffect->SetPersistent(true);
        AddEffect(*m_pPressEffect);
    }
}
    
//
void PK_Button::InternalControlClicked()
{
  if (m_pPressEffect == NULL)
  {
      InvokeOnClick();
  }
  else
  {
      m_pPressEffect->SetActive(true);
      m_pPressEffect->InternalReset();
      GetScene()->DisableInput();
      m_ButtonPressed = true;
  }
}
    
} // namespace
