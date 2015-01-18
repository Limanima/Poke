#include "PK_MathHelper.h"
#include <sdl.h>
#include "PK_Globals.h"
#include "PK_Consts.h"
#include "PK_Types.h"
#include "PK_SDLInputManager.h"
#include "PK_SDLManager.h"
#include "PK_Exceptions.h"
#include "PK_Log.h"

namespace PK {

PK_SDLInputManager::PK_SDLInputManager(const PK_String &sName) :
  PK_InputManager(sName)
{
    SetTypeName("PK_SDLInputManager");
    memset(m_keyStates, '\0', sizeof(m_keyStates));
    m_vPointerPosition = PK_Vector2(.0f, .0f);
    m_FlickVector = PK_Vector2(.0f, .0f);
	m_vClickPosition = PK_Vector2(.0f, .0f);
    m_Actions = InputAction_None;
    m_bFlickStarted = false;
    m_bFingerDown = false;
    m_bMouseDown = false;
}

//
void PK_SDLInputManager::OnInitialize()
{
    PK_InputManager::OnInitialize();
    memset(m_keyMapping, '\0', sizeof(m_keyMapping));
    m_keyMapping[SDL_SCANCODE_ESCAPE] = KeyCode_Esc;
    m_keyMapping[SDL_SCANCODE_AC_BACK] = KeyCode_Back;

    PK_SDLManager *pManager = (PK_SDLManager *)PokeEngine.GetComponent(PK_SDL_MANAGER_NAME);
    if (pManager == NULL)
    {
        throw PK_SystemException("SDL manager was not added to the PokeEngine. SDLInputManager cannot be initialized.", __FILE__, __LINE__);
    }
    pManager->SetSDLInputManager(this);
   
}

//
void PK_SDLInputManager::OnUpdate(const PK_GameTimer &time)
{
  #define EVENT_BUFFER_SIZE 16
  m_Actions = InputAction_None;
  m_FlickAction = FlickAction_None;
  m_FlickVector = PK_Vector2(0.0f, 0.0f);

  if (SupportsKeyboard() &&
      m_KeyboardEvents.GetCount() > 0)
  {
    ProcessKeyboard();
  }

  if (SupportsTouch() &&
      m_TouchEvents.GetCount() > 0)
  {
    ProcessTouch();
  }

  if (SupportsMouse() &&
    m_MouseEvents.GetCount() > 0)
  {
    ProcessMouse();
  }
}

//
void PK_SDLInputManager::AddEvent(SDL_Event &event)
{
    if (SupportsKeyboard())
    {
        if (event.type >= SDL_KEYDOWN &&
            event.type <= SDL_KEYUP)
        {
            m_KeyboardEvents.Add(event);
        }
    }
    
    if (SupportsTouch())
    {
        if (event.type >= SDL_FINGERDOWN &&
            event.type <= SDL_FINGERMOTION)
        {
            m_TouchEvents.Add(event);
        }
    }
    
    if (SupportsMouse())
    {
        if (event.type >= SDL_MOUSEMOTION &&
            event.type <= SDL_MOUSEWHEEL)
        {
            m_MouseEvents.Add(event);
        }
    }
}

//
bool PK_SDLInputManager::QueryAction(PK_eInputActionType action)
{
    switch(action)
    {
      case InputAction_Back:
        return (QueryKeyPressed(KeyCode_Esc) || 
                QueryKeyPressed(KeyCode_Back));

      default:
        return ((m_Actions & action) == action);

    }

    return false;
}

//
void PK_SDLInputManager::ProcessKeyboard()
{
  memcpy(m_prevKeyStates, m_keyStates, sizeof(m_keyStates));
  memset(m_keyStates, SDLKeyState_None, sizeof(m_keyStates));
  for(PK_ListIterator(SDL_Event) itor = m_KeyboardEvents.Begin(); itor != m_KeyboardEvents.End(); itor++)
    {
        switch((*itor).type)
        {
            case SDL_KEYDOWN:   
              if (m_keyMapping[(*itor).key.keysym.scancode] < PK_MAX_KEYS)
              {
                    m_keyStates[m_keyMapping[(*itor).key.keysym.scancode]] = SDLKeyState_Down;
              }
              break;

            case SDL_KEYUP:
              if (m_keyMapping[(*itor).key.keysym.scancode] < PK_MAX_KEYS)
              {
                  int idx = m_keyMapping[(*itor).key.keysym.scancode];
                  if (m_prevKeyStates[idx] == SDLKeyState_Down)
                  {
                    m_keyStates[idx] = SDLKeyState_Pressed;
                  }
                  else
                  {
                    m_keyStates[idx] = SDLKeyState_Up;
                  }
              }
              break;
        }
    }
    m_KeyboardEvents.Clear();
}

// Nota: o SDL devolve valores para posicao entre 0 e 1
void PK_SDLInputManager::ProcessTouch()
{
  for(PK_ListIterator(SDL_Event) itor = m_TouchEvents.Begin(); itor != m_TouchEvents.End(); itor++)
  {    
    SDL_Event *pEvent = &(*itor);
    switch((*itor).type)
    {
        case SDL_FINGERDOWN:
            {
                FingerDown( pEvent->tfinger.x, pEvent->tfinger.y);
            }
        break;
            
      case SDL_FINGERUP:
          {
              PK_Vector2 vPos =  TouchCoords2ScreenCoords( pEvent->tfinger.x, pEvent->tfinger.y);
              m_vPointerPosition = PokeEngine.GetRenderManager().GetCamera().Unproject(vPos);
              m_Actions |= InputAction_LeftClicked;
			  CheckForClick(m_vPointerDownPosition, m_vPointerPosition);
              if (m_bFlickStarted)
              {
                  FlickEnded();
              }
              m_bFingerDown = false;
          }
          break;
          
      case SDL_FINGERMOTION:
          {
              // Se por acaso o finger down n for apanhado, damos o finger down como started aqui
              if (!m_bFingerDown)
              {
                  FingerDown(pEvent->tfinger.x, pEvent->tfinger.y);
              }
              PK_Vector2 vPos = TouchCoords2ScreenCoords(pEvent->tfinger.x, pEvent->tfinger.y);
              m_vPointerPosition = PokeEngine.GetRenderManager().GetCamera().Unproject(vPos);
              PK_Vector2 vFlick = TouchCoords2ScreenCoords(pEvent->tfinger.dx, pEvent->tfinger.dy);
              SetFlickAction(PokeEngine.GetRenderManager().GetCamera().UnprojectOffset(vFlick));
          }
          break;
    }
  }
    

  m_TouchEvents.Clear();
}

// As coordenadas do SDL estao nomralizadas entre 0 e 1, temos que converter em screen coords (e 0, 0 e o centro do ecran)
PK_Vector2 PK_SDLInputManager::TouchCoords2ScreenCoords(float x,  float y)
{
    static PK_tSize screenRes = PokeEngine.GetRenderManager().GetWindowSize();
    // As coordenadas do SDL estao nomralizadas entre 0 e 1, temos que converter em screen coords (e 0, 0 e o centro do ecran)
    return  PK_Vector2( x * screenRes.w, y * screenRes.h);
}
    
//
void PK_SDLInputManager::ProcessMouse()
{
  	for(PK_ListIterator(SDL_Event) itor = m_MouseEvents.Begin(); itor != m_MouseEvents.End(); itor++)
    {
      SDL_Event *pEvent = &(*itor);
      switch ((*itor).type)
      {
        case SDL_MOUSEBUTTONDOWN:
          {
              MouseDown((float)pEvent->button.x, (float)pEvent->button.y);
          }
          break;

        case SDL_MOUSEBUTTONUP:
          {
            PK_Vector2 vPos = PK_Vector2(pEvent->button.x, pEvent->button.y);
            m_vPointerPosition = PokeEngine.GetRenderManager().GetCamera().Unproject(vPos);
            m_Actions |= InputAction_LeftClicked;
			CheckForClick(m_vPointerDownPosition, m_vPointerPosition);
            if (m_bFlickStarted)
            {
                FlickEnded();
            }
           }
          break;

        case SDL_MOUSEMOTION:
          {
             // Se por acaso o finger down n for apanhado, damos o finger down como started aqui
             if (!m_bMouseDown)
             {
                  MouseDown((float)pEvent->button.x, (float)pEvent->button.y);
             }
            PK_Vector2 vPos = PK_Vector2(pEvent->motion.x, pEvent->motion.y);
            m_vPointerPosition = PokeEngine.GetRenderManager().GetCamera().Unproject(vPos);
            PK_Vector2 vFlick = PK_Vector2(pEvent->motion.xrel, pEvent->motion.yrel);
            if (pEvent->motion.state == SDL_PRESSED)
            {
                SetFlickAction(PokeEngine.GetRenderManager().GetCamera().UnprojectOffset(vFlick));
            }
            else
            {
                if (m_bFlickStarted)
                {
                    FlickEnded();
                }
            }
          }
          break;
      }
    }
    m_MouseEvents.Clear();

}

//
void PK_SDLInputManager::FingerDown(float x, float y)
{
    PK_Vector2 vPos = TouchCoords2ScreenCoords(x, y);
    m_vPointerDownPosition = PokeEngine.GetRenderManager().GetCamera().Unproject(vPos);
    m_bFingerDown = true;
}

//
void PK_SDLInputManager::MouseDown(float x, float y)
{
    PK_Vector2 vPos = PK_Vector2(x, y);
    m_vPointerDownPosition = PokeEngine.GetRenderManager().GetCamera().Unproject(vPos);
    m_bMouseDown = true;
}

//
bool PK_SDLInputManager::IsInputEvent(SDL_Event &event)
{
    if (event.type >= SDL_KEYDOWN &&
        event.type <= SDL_KEYUP)
    {
        return true;
    }

    if (event.type >= SDL_FINGERDOWN &&
        event.type <= SDL_FINGERMOTION)
    {
        return true;
    }


    if (event.type >= SDL_MOUSEMOTION &&
        event.type <= SDL_MOUSEWHEEL)
    {
        return true;
    }
    return false;
    
}
 

//
void PK_SDLInputManager::SetFlickAction(const PK_Vector2 &vFlickVector)
{
  m_FlickVector = vFlickVector;
  m_fFlickDelta = glm::length(m_FlickVector);
  m_fFlickLength += m_fFlickDelta;
  m_bFlickStarted = true;

  PK_Vector2 vFlick = glm::normalize(vFlickVector);

  float fAngle = PK_MathHelper::AngleBetweenVectors(vFlick, PK_Vector2(1.0f, 0.0f));
  fAngle = PK_MathHelper::RadiansToDegrees(fAngle);

  if (fAngle >= 45 && fAngle <= 135)
  {
    m_FlickAction = FlickAction_Up;
  }
  else
  if (fAngle < 45 && fAngle > -45)
  {
    m_FlickAction = FlickAction_Right;
  }
  else
  if (fAngle >= -135 && fAngle <= -45)
  {
    m_FlickAction = FlickAction_Down;
  }
  else
  if (fAngle > 135 || fAngle < -135)
  {
    m_FlickAction = FlickAction_Left;
  }
  m_Actions |= InputAction_Flick;

}

//
void PK_SDLInputManager::FlickEnded()
{
    m_Actions |= InputAction_FlickEnded;
    m_Actions &= ~InputAction_Flick;
    m_bFlickStarted = false;
    m_fFlickLength = 0;
}

// Existe click se :
//   -nao hou ve movimento do dedo/rato (com um threshold)
//   -nao passou x tempo (n implementado) FIXME
void PK_SDLInputManager::CheckForClick(const PK_Vector2 vPointerDown, const PK_Vector2 vPointerUp)
{
	PK_Vector2 vMove = (vPointerDown - vPointerUp);
	if (glm::length(vMove) < 10.0f)
	{
		m_vClickPosition = m_vPointerPosition;
        m_Actions |= InputAction_Clicked;
	}
}

} // namespace
