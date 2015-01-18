#include <PokeEngine.h>
#include "FC_Player.h"     
#include "FC_Consts.h"   


FC_Player::FC_Player(const PK::PK_String &sName) :
    PK::PK_SceneControl(sName)
{  
    SetTypeName("FC_Player");

}

//
void FC_Player::OnInitialize()
{

}

//
void FC_Player::OnUpdate(const PK::PK_GameTimer &time) 
{ 
    // Flick
    if (PK::PokeEngine.GetInputManager().QueryAction(PK::InputAction_Flick))
    {
        if (PK::PokeEngine.GetInputManager().GetFlickLength() < 40.0f)
        {
            return;
        }
        PK::PK_eFlickActionType flickAction = PK::PokeEngine.GetInputManager().GetFlickAction();
        switch(flickAction)
        {
            case PK::FlickAction_Left:
                if (OnFlickedLeft.HasCallback())
                {
                    OnFlickedLeft->Execute(*this);
                }
                break;

            case PK::FlickAction_Right:
                if (OnFlickedRight.HasCallback())
                {
                    OnFlickedRight->Execute(*this);
                }
                break;

            default:
                break;
        }
    }
    else
    // Flick ended
    if (PK::PokeEngine.GetInputManager().QueryAction(PK::InputAction_FlickEnded))
    {
        if (OnFlickEnded.HasCallback())
        {
            OnFlickEnded->Execute(*this);
        }
    }
    else
    // Tap
    if (PK::PokeEngine.GetInputManager().QueryAction(PK::InputAction_Clicked))
    {
        if (OnTapped.HasCallback())
        {
            OnTapped->Execute(*this);
        }
        return;
    }
}

