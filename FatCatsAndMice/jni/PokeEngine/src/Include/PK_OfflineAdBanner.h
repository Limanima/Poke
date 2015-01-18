#ifndef _PK_OFFLINEBANNER_H_
#define _PK_OFFLINEBANNER_H_

#include "PK_Sprite.h"

namespace PK {    

enum PK_eAdClickAction
{
    AdClickAction_None,
    AdClickAction_OpenAppInStore, // sData deve ser uma app id
    AdClickAction_OpenUrl         // sData deve ser um url
};
    
// Classe base para um asset: textura, sprite, font, etc
class PK_OfflineAdBanner : public PK_Sprite
{
protected:
    PK_String         m_sActionData;
    PK_eAdClickAction m_ActionType;

public:
	PK_OfflineAdBanner(const PK_String &sName);
    void Ad_Click(PK::PK_Object &sender);
    
    inline void SetActionData(const PK_String &sActionData) { m_sActionData = sActionData; }
    inline PK_String GetActionData() { return m_sActionData; }
    
    inline void SetActionType(PK_eAdClickAction actionType) { m_ActionType = actionType; }
    inline PK_eAdClickAction GetActionType() { return m_ActionType; }
};

} // namespace

#endif