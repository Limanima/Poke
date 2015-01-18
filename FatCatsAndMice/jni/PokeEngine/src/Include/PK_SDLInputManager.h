#ifndef _PK_SDLINPUTMANAGER_H_
#define _PK_SDLINPUTMANAGER_H_

#include "PK_InputManager.h"
#include "PK_Types.h"
#include "PK_Vector2.h"
#include "PK_String.h"

#define PK_MAX_KEYS 300

namespace PK {

class PK_SDLInputManager : public PK_InputManager
{
  enum PK_tSDLKeyStateType
  {
    SDLKeyState_None,
    SDLKeyState_Down,
    SDLKeyState_Up,
    SDLKeyState_Pressed
  };

private:
    PK_tSDLKeyStateType m_keyStates[PK_MAX_KEYS];
    PK_tSDLKeyStateType m_prevKeyStates[PK_MAX_KEYS];
    short m_keyMapping[PK_MAX_KEYS]; // Mapeia os codigos das teclas do Poke Engine com o SDL
    unsigned int m_Actions;
    PK_List<SDL_Event> m_KeyboardEvents;
    PK_List<SDL_Event> m_TouchEvents;
    PK_List<SDL_Event> m_MouseEvents;

    // Flick support
    bool m_bFlickStarted;
    bool m_bFingerDown;
    bool m_bMouseDown;

public:
    PK_SDLInputManager(const PK_String &sName);
    void OnInitialize();
    void OnUpdate(const PK_GameTimer &time);
    void AddEvent(SDL_Event &event);

    inline bool QueryKeyPressed(PK_eKeyCodeType key) { return (m_keyStates[key] == SDLKeyState_Pressed); };
    inline bool QueryKeyDown(PK_eKeyCodeType key) { return (m_keyStates[key] == SDLKeyState_Down); };
    inline bool QueryKeyUp(PK_eKeyCodeType key) { return (m_keyStates[key] == SDLKeyState_Up); };
    bool QueryAction(PK_eInputActionType action);
    bool IsInputEvent(SDL_Event &event);
    PK_Vector2 TouchCoords2ScreenCoords(float x, float y);
                   
private:
    void ProcessKeyboard();
    void ProcessTouch();
    void ProcessMouse();
    void FingerDown(float x, float y);
    void MouseDown(float x, float y);
    void SetFlickAction(const PK_Vector2 &vFlickVector);
    void FlickEnded();
	void CheckForClick(const PK_Vector2 vPointerDown, const PK_Vector2 vPointerUp);
};

}

#endif
