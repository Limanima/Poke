#ifndef _PK_SCENEMANAGER_H_
#define _PK_SCENEMANAGER_H_

#include "PK_List.h"
#include "PK_Consts.h"
#include "PK_Component.h"
#include "PK_Scene.h"
#include "PK_String.h"
#include "PK_Types.h"
#include "PK_SystemException.h"
#include "PK_ObjectLoader.h"
#include "PK_SceneManagerSettings.h"
#include "PK_FPSCounterProfilerItem.h"
#include "PK_Component.h"

namespace PK {

class PK_DataFileRecord;
class PK_SceneTransition;
class PK_LoadingIcon;
class PK_SplashScene;
    
class PK_SceneManager : public PK_Component
{

private:
    bool                         m_bInitialized;
    PK_SceneManagerSettings      m_Settings;
    PK_List<PK_Scene *>          m_Scenes;
    PK_List<PK_Scene *>          m_ActiveScenes;
    PK_List<PK_tSceneAction *>   m_QueuedSceneActions;
    PK_tSceneGroup			    *m_pCurrentGroup;
    PK_String                    m_sCurrentGroupName;
    PK_Scene                    *m_pActiveScene;
    PK_SceneTransition          *m_pTransition;
    PK_eTransitionType           m_CurrentTransitionType;
    PK_ObjectLoader              m_SceneLoader; 
    PK_SplashScene              *m_pSplash;
     
public:
	PK_SceneManager(const PK_String &sName);
    ~PK_SceneManager();
    void OnInitialize();
    void OnUpdate(const PK_GameTimer &time);
    void OnUnload();
    void OnDraw();

    PK_Scene * GetScene(const PK_String &sSceneName);
	void NavigateToStartup();
	void NavigateTo(const PK_String &sSceneName);
	void NavigateTo(const PK_String &sSceneName, PK_SceneTransition *pCloseTransition, PK_SceneTransition *pOpenTransition);
	void NavigateTo(PK_tSceneGroup &group, const PK_String &sSceneName, PK_SceneTransition *pCloseTransition,PK_SceneTransition *pOpenTransition);
	void NavigateTo(PK_tSceneGroup &group, const PK_String &sSceneName);
	void NavigateTo(const PK_String &sGroupName, const PK_String &sSceneName);
    void PopUp(const PK_String &sSceneName, bool bModal);
    void SetLoadingIcon(PK_LoadingIcon *pIcon);
    void RestartCurrentScene();
    inline PK_SceneManagerSettings & GetSettings() { return m_Settings; }

    void OnSplashClosed();

private:
    void LoadGroupData(const PK_String &sGroupName);
    void LoadGroup(const PK_String &sGroupName);
    void UnloadCurrentGroup();
	void QueueAction(PK_eSceneActionType actionType, const PK_String &sSceneName, void *param, bool bSyncronous);
    void ProcessQueuedSceneActions(const PK_GameTimer &time);
    void ProcessSceneAction(PK_tSceneAction &action, const PK_GameTimer &time);
    void AddActiveScene(PK_Scene *pScene);
    void DisableAllActiveScenes();
    void ClearActiveScenes();
    void ClearScenes();
    void ClearQueuedActions();
    void SetTransition(PK_SceneTransition *pTransition);
    void AddScene(PK_Scene * pScene);
};

}

#endif