#include <PokeEngine.h>
#include "FC_Consts.h"   
#include "FC_Button.h"              
       
                    
FC_Button::FC_Button(const PK::PK_String &sName, FC_eButtonType buttonType) :
    PK::PK_Panel(sName)
{ 
    switch(buttonType) 
    { 
        case ButtonType_Play:
            SetSize(215.0f, 120.0f);
            SetPosition(-235.0f, -245.0f);
            //SetBackgroundColor(PK_COLOR_RED);
            break;

        case ButtonType_Leaderboards:
            SetSize(215.0f, 120.0f);
            SetPosition(235.0f, -245.0f);
            //SetBackgroundColor(PK_COLOR_GREEN);
            break;
        default:
            SetSize(400.0f, 120.0f);
            break;
    }
} 
  
//
void FC_Button::OnInitialize()
{ 

}
