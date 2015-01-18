#ifndef _POKEGAME_H_
#define _POKEGAME_H_

#include "PK_Component.h"

namespace PK {
class PK_Scene;
class PK_SceneControl;

class PK_Game : public PK_Component
{
private:
    PK_String m_sStoreId;
    
public:
	PK_Game(const PK_String &sName);
	// FIXME, ver destes quais devem ser passados para PK_Component
		// a semelhanca do enterforegroudn/background
    void OnInitialize();
	  virtual void OnStart() {};
	  virtual void OnExit() {};
	  virtual void OnLowMemory() {}
	  virtual bool OnClose();
	  virtual void OnGamerServicesLogin(bool bSuccess)  {}
	  virtual void OnGamerServicesLogout()  {}
	
	  void OpenInAppStore();
    void Exit();
    virtual PK_Scene * CreateScene(const PK_String &name) = 0;
    virtual PK_SceneControl * CreateControl(const PK_String &typeName, const PK_String &sName);
    bool IsActive() { return true; } // FIXME: Ver isto
    
    inline PK_String GetAppStoreId() { return m_sStoreId; }
};

}
#endif
