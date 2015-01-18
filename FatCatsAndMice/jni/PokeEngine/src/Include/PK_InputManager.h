#ifndef _PK_INPUTMANAGER_H_
#define _PK_INPUTMANAGER_H_

#include "PK_Component.h"
#include "PK_Types.h"
#include "PK_Vector2.h"

namespace PK {

class PK_InputManager : public PK_Component
{
protected:
  bool m_SupportsKeyboard;
  bool m_SupportsMouse;
  bool m_SupportsTouch;
 
  PK_Vector2    m_vPointerPosition; 
  PK_Vector2    m_vClickPosition;   
  PK_Vector2    m_vPointerDownPosition;

  // Suporte para flick
  PK_eFlickActionType   m_FlickAction;
  float                 m_fFlickLength; // Comprimento total, soma de todos os vectores
  float                 m_fFlickDelta;  // Delta do comprimento do ultimo movimento
  PK_Vector2            m_FlickVector;

public:
  PK_InputManager(const PK_String &sName);
  virtual void OnInitialize();
  virtual bool QueryKeyPressed(PK_eKeyCodeType key) = 0;
  virtual bool QueryKeyDown(PK_eKeyCodeType key) = 0;
  virtual bool QueryKeyUp(PK_eKeyCodeType key) = 0;
  virtual bool QueryAction(PK_eInputActionType action) = 0; 

  void DisableInput();
  void EnableInput();

  // Flick
  inline PK_eFlickActionType GetFlickAction() { return m_FlickAction; } 
  inline PK_Vector2 GetFlickVector() { return m_FlickVector; }
  inline PK_Vector2 GetFlickStartingPoint() { return m_vPointerDownPosition; }
  inline float GetFlickLength() { return m_fFlickLength; }
  inline float GetFlickDelta() { return m_fFlickDelta; }
  inline bool SupportsKeyboard() { return m_SupportsKeyboard; }
  inline bool SupportsMouse() { return m_SupportsMouse; }
  inline bool SupportsTouch() { return m_SupportsTouch; }
  inline PK_Vector2 GetPointerPosition() { return m_vPointerPosition; } 
  inline PK_Vector2 GetClickPosition() { return m_vClickPosition; }   


};

}

#endif
