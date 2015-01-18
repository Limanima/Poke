#ifndef _PK_BUTTON_H_
#define _PK_BUTTON_H_

#include "PK_2DSceneControl.h"

namespace PK {

class PK_Effect;
    
class PK_Button : public PK_2DSceneControl
{
private:
    PK_Label  *m_pLabel;
    PK_Effect *m_pPressEffect;
    bool       m_ButtonPressed;

public:
    PK_Button(const PK_String &sName = "");
    ~PK_Button();
    void FreeResources();
    void InitFromDataFileRecord(PK_DataFileRecord &record);
    void InternalUnload();
    void InternalUpdate(const PK_GameTimer &time);
    inline void SetText(const PK_String &sText) { m_pLabel->SetText(sText); }
    inline PK_String GetText() { return m_pLabel->GetText(); }
    void SetFont(const PK_String &sAssetName);
    void SetTextColor(const PK_Color &color);
    void SetClickEffect(PK_Effect *pPressEffect);
    void InternalControlClicked();
};

}

#endif
