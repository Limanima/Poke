#ifndef _PK_SCENEMANAGERSETTINGS_H_
#define _PK_SCENEMANAGERSETTINGS_H_

#include "PK_Settings.h"
#include "PK_Types.h"
#include "PK_List.h"

namespace PK {
    
class PK_DataFileRecord;
    
class PK_SceneManagerSettings : public PK_Settings
{
private:
    PK_String     m_sStartupGroupName;
    PK_String     m_sStartupSceneName;
    PK_String     m_sScenesPath;

    PK_List<PK_tSceneGroup *> m_SceneGroups;

public:
	PK_SceneManagerSettings();
    ~PK_SceneManagerSettings();
    void OnLoad();
    
    PK_tSceneGroup * GetSceneGroup(const PK_String &sGroupName);
	inline PK_String GetStartupGroupName() { return m_sStartupGroupName; }
	inline PK_String GetStartupSceneName() { return m_sStartupSceneName; }
	inline PK_String GetScenesPath() { return m_sScenesPath; }

};

}
#endif
