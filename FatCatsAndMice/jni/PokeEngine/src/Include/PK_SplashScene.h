#ifndef _PK_SPLASH_H_
#define _PK_SPLASH_H_

#include "PK_Scene.h"

namespace PK {    

class PK_Sprite;
class PK_TimerControl;

// 
class PK_SplashScene : public PK_Scene
{
protected:
    PK_TimerControl *m_pTimer;
    PK_Sprite       *m_pSprite;

public:
	PK_SplashScene(const PK_String &sName);
    void EndTimer_Timer(PK_Object &sender);

    void SetSprite(const PK_String &sSpriteResourceName);
};

} // namespace

#endif
