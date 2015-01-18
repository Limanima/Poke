#ifndef _PK_APP_H_
#define _PK_APP_H_

#include "PK_String.h"
#include "PK_Component.h"
#include "PK_Dictionary.h"
#include "PK_Array.h"
#include "PK_Types.h"

namespace PK {

class PK_AssetManager;
class PK_RenderManager;

class PK_App : public PK_Component
{
    PK_Array<PK_Component *> m_Components;
    PK_eAppType              m_type;

public:
	PK_App(PK_eAppType type, const PK_String &sName);
    void AddComponent(PK_Component & component);
    
    virtual void InternalInitialize(PK_Dictionary<PK_String, PK_String> arguments);
    virtual void InternalRun();
    virtual void InternalUnInitialize();
    virtual void Exit() {};
    void UpdateComponents(const PK_GameTimer &time);
    void DrawComponents(PK_RenderManager &renderer);

    virtual void OnInitialize(PK_Dictionary<PK_String, PK_String> arguments) {}
    virtual void OnRun() = 0;
    virtual void OnUnInitialize() {}

    
  
    inline PK_eAppType GetType() { return m_type; }
    inline PK_Array<PK_Component *> & GetComponents() { return m_Components; }
};

}
#endif