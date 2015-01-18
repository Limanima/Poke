#ifndef _PK_DRAWABLECOMPONENT_H_
#define _PK_DRAWABLECOMPONENT_H_

#include "PK_Component.h"


namespace PK {

class PK_Scene;
// 
class PK_DrawableComponent : public PK_Component
{
private:
	PK_Scene   *m_pScene;
 
public:
    PK_DrawableComponent();
    PK_DrawableComponent(const PK_String &sName);
    ~PK_DrawableComponent();
	void InitInstance();
	virtual void OnInitialize();
    virtual void OnLoad();
    virtual void OnUpdate(const PK_GameTimer &timer);
    virtual void OnUnload();
    virtual void OnDraw();

	inline PK_Scene & GetScene() { return *m_pScene; }
};

}

#endif