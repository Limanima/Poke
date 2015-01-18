#include <PokeEngine.h>
#include "FC_ScorePoint.h"     
#include "FC_Consts.h"

#define SPEED 50.0f // Em pixeis por segundo

//
FC_ScorePoint::FC_ScorePoint() :
    PK::PK_Label("fc_scorePoint")
{  
    SetScore(1);
    SetFont(FCAM_ASSET_FONT_DEFAULT);
    SetColor(PK_Color(PK_COLOR_RGBA_INT(190, 255, 255, 255)));

    PK::PK_ColorEffect *pClrEffect = new PK::PK_ColorEffect(GetName() + "btnColorFx", PK_COLOR_WHITE, PK_COLOR_TRANSPARENT, 1.0f, false, PK_COLOR_TRANSPARENT);
    AddEffect(*pClrEffect);
}

//
void FC_ScorePoint::SetScore(int iScore)
{
    SetText(iScore);

}

//
void FC_ScorePoint::OnUpdate(const PK::PK_GameTimer &time)
{ 
	float fSpeed = (SPEED * time.GetEllapsedTime() / 1000.0f);
	Move(0.0f, fSpeed);

	if (GetColor() == PK_COLOR_TRANSPARENT)
	{
		RemoveFromScene();
	}
}

//
void FC_ScorePoint::OnMessageReceived(PK::PK_tMessage1 &msg)
{
    if(msg.uiMsg == FCAM_MSG_GAMEOVER)
    {
        RemoveFromScene();
    }
}