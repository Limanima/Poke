#ifndef _PK_PROFILERMENU_H_
#define _PK_PROFILERMENU_H_

#include "PK_2DSceneControl.h"

namespace PK {
class PK_Button;

class PK_ProfilerMenu : public PK_2DSceneControl
{
private:
    PK_Button *m_pBtnObjList;
    PK_Button *m_pBtnAssetList;
    PK_Button *m_pBtnFPS;
    PK_Button *m_pBtnReloadScene;
    
public:
    PK_ProfilerMenu(const PK_String &sName);
    void BtnShowHideObjects_Click(PK::PK_Object &sender);
    void BtnShowHideAssets_Click(PK::PK_Object &sender);
    void BtnShowHideFPS_Click(PK::PK_Object &sender);
    void BtnReloadScene_Click(PK::PK_Object &sender);
};

}
#endif
