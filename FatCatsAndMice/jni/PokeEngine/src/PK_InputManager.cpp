#include "PK_InputManager.h"
#include "PK_Config.h"

namespace PK {

PK_InputManager::PK_InputManager(const PK_String &sName) :
    PK_Component(sName)
{
  m_FlickAction = FlickAction_None;
  m_FlickVector = PK_Vector2(0.0f, 0.0f);
  m_fFlickLength = 0.0f;
  m_fFlickDelta = 0.0f;
}

//
void PK_InputManager::OnInitialize()
{
  // FIXME: Inicializar dos settings...
  m_SupportsKeyboard = PK_SUPPORTS_KEYBOARD;
  m_SupportsMouse = PK_SUPPORTS_MOUSE;
  m_SupportsTouch = PK_SUPPORTS_TOUCH;
}

//
void PK_InputManager::DisableInput()
{
    SetActive(false);
}

//
void PK_InputManager::EnableInput()
{
    SetActive(true);
}

} // namespace
