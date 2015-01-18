#include "PK_Globals.h"
#include "PK_SceneManager.h"
#include "PK_Exceptions.h"
#include "PK_DataFile.h"
#include "PK_Thread.h"
#include "PK_SceneTransition.h"
#include "PK_Scene.h"
#include "PK_LoadingIcon.h"
#include "PK_Log.h"
#include "PK_SplashScene.h"

namespace PK {

//
PK_SceneManager::PK_SceneManager(const PK_String &sName) :
    PK_Component(sName)
{
    m_pActiveScene = NULL;
    m_pTransition = NULL;
    m_CurrentTransitionType = TransitionType_None;
    m_pCurrentGroup = NULL;
    m_bInitialized = false;
    m_pSplash = NULL;
}

//
PK_SceneManager::~PK_SceneManager()
{
    ClearActiveScenes();
    ClearScenes();
    ClearQueuedActions();
}

//
void PK_SceneManager::OnInitialize()
{
    if (m_bInitialized)
    {
        throw PK_SystemException("Scene Manager was already initialized.",__FILE__, __LINE__);
    }
	m_Settings.Load(PK_SCENEMANAGER_SETTINGS_FILE);
    
    m_bInitialized = true;

    // FIXME! ISto de splash devia era ser uma scene transition
    // porque assim podemos mostrar o splash quando esta a carregar o grupo
    // Como esta tambem funciona mas esta martelado
    // Se splash enabled, cria uma splash scene e mostra
    if (PokeEngine.GetSettings().GetSplashEnabled())
    {
        m_pSplash = new PK_SplashScene(PK_SPLASH_SCENE_NAME);
        m_pSplash->SetBackgroundColor(PokeEngine.GetSettings().GetSplashBackColor());
        m_pSplash->SetSprite(PokeEngine.GetSettings().GetSplashSprite());
        m_pSplash->InternalLoad();
        m_pSplash->InternalInitialize();
        m_pSplash->InternalOpen();
        m_pSplash->Grab();
    }
    NavigateToStartup();
}

// Faz update a todas as scenes que estao na lista de scenes activas
void PK_SceneManager::OnUpdate(const PK_GameTimer &time)
{
    if (m_SceneLoader.IsLoading())
    {
        m_SceneLoader.OnUpdate(time);
        if (!m_SceneLoader.IsLoading())
        {
            // O que se segue e estranho, isto precisa de ser melhorado:
            // A chamada de OnLoad nas scenes/objectos pode provocar que sejam adicionados objectos na library
            // E necessario chamar o OnLoad dos objectos da library. Portanto depois da queue de loading estiver vazia, vamos
            // ver se a library tem alguma coisa para carregar, se tiver, adicionamos na queue e continuamos com o loading
            PokeEngine.GetLibrary().AddItemsToLoader(m_SceneLoader);
            // Nao foram adicionados novos items? Finalizar o loading
            if (m_SceneLoader.IsQueueEmpty())
            {
                ProcessQueuedSceneActions(time);
                if(m_pSplash != NULL)
                {
                    m_pSplash->Release();
                    m_pSplash = NULL;
                }
            }
            else
            {
                m_SceneLoader.StartLoading();
            }
        }
        return;
    }
    
    if (m_pTransition != NULL)
    {                             
        m_pTransition->OnUpdate(time);
        if (m_pTransition->HasEnded())
        {
            if (m_pActiveScene != NULL && m_CurrentTransitionType == TransitionType_Open)
            {
                m_pActiveScene->OnOpenTrasitionEnded();
            }
            ProcessQueuedSceneActions(time);  
        }
    }
    else // Update the screen
    {
        ProcessQueuedSceneActions(time);
        if (m_pActiveScene != 0)
        {
            for(PK_ListIterator(PK_Scene *) itor = m_ActiveScenes.Begin(); itor != m_ActiveScenes.End(); itor++)
            {
                PK_Scene * pScene  = (*itor);
                if (pScene->IsActive())
                {
                    pScene->InternalUpdate(time);
                }
            }
        }
    }

    if (m_pSplash != NULL)
    {
        m_pSplash->InternalUpdate(time);
    }
}

//
void PK_SceneManager::OnUnload()   
{
    UnloadCurrentGroup();
}

// Faz draw a todas as scenes que estao na lista de scenes activas
void PK_SceneManager::OnDraw()
{

    if (!m_SceneLoader.IsLoading())
    {
        for(PK_ListIterator(PK_Scene *) itor = m_ActiveScenes.Begin(); itor != m_ActiveScenes.End(); itor++)
        {
            if ((*itor)->IsVisible()) 
            {
                (*itor)->InternalDraw();
            }
        }
    }
    else
    {
        m_SceneLoader.OnDraw();
    }
    
    if (m_pTransition != NULL) // There's a screen transition, update the transition
    {
        m_pTransition->OnDraw();
    }
    
    if (m_pSplash != NULL)
    {
        m_pSplash->InternalDraw();
    }
   
}

// Devolve a scene com o nome sSceneName
// Se nao encontrar devolve NULL
PK_Scene * PK_SceneManager::GetScene(const PK_String &sSceneName)
{
	for(PK_ListIterator(PK_Scene *) itor = m_Scenes.Begin(); itor != m_Scenes.End(); itor++)
    {
        if ((*itor)->GetName() == sSceneName)
        {
            return (*itor);
        }
    }

	throw PK_SystemException("Scene named '%s' could not be found because it's not loaded.", __FILE__, __LINE__, sSceneName.c_str());
}

//
void PK_SceneManager::LoadGroup(const PK_String &sGroupName)
{
    m_SceneLoader.StartLoading();
    UnloadCurrentGroup();
    LoadGroupData(sGroupName);
}

//
void PK_SceneManager::LoadGroupData(const PK_String &sGroupName)
{
  PK_tSceneGroup * pGroup = m_Settings.GetSceneGroup(sGroupName);
  for(unsigned int i = 0; i < pGroup->uiSceneCount; i++)
    {
        PK_Log::WriteInfo(PK_LOG_TAG, "Creating scene [%s]", pGroup->scenes[i].sName.c_str());
        PK_Scene * pScene = PokeEngine.GetGame().CreateScene(pGroup->scenes[i].sName);
        if (pScene == NULL)
        {
            throw PK_SystemException("Could not create scene named '%s'. Please check overriden method Game.CreateScreen()", __FILE__, __LINE__, pGroup->scenes[i].sName.c_str());
        }
        pScene->SetName(pGroup->scenes[i].sName);
        pScene->AddToLoadingQueue(m_SceneLoader);
        AddScene(pScene);
    }
    m_pCurrentGroup = pGroup;
}

    
//
void PK_SceneManager::UnloadCurrentGroup()
{
    if (m_pCurrentGroup == NULL)
    {
        return;
    } 
    // Invocar unload em todas as scenes carregadas
    for(PK_ListIterator(PK_Scene *) itor = m_Scenes.Begin(); itor != m_Scenes.End(); itor++)
	{
        PK_Scene * pScene = (*itor);
        pScene->InternalUnload();
        pScene->Release();
    }
    m_Scenes.Clear();

    // Libertar as active scenes
    for(PK_ListIterator(PK_Scene *) itor = m_ActiveScenes.Begin(); itor != m_ActiveScenes.End(); itor++)
	{
        PK_Scene * pScene = (*itor);
        pScene->Release();
    }
    m_ActiveScenes.Clear();

    // Fazer unload de todos os resources temporarios
    PokeEngine.GetAssetManager().UnloadTemporaryContainers();

    // Libertar os items da library que tenham scope de grupo
    PokeEngine.GetLibrary().RemoveItemsInScope(LibraryItemScope_SceneGroup);
    m_pCurrentGroup = NULL;
}

// Navega para o inicio
void PK_SceneManager::NavigateToStartup()
{
    NavigateTo(m_Settings.GetStartupGroupName(), m_Settings.GetStartupSceneName());
}

// 
void PK_SceneManager::NavigateTo(const PK_String &sSceneName)
{
    NavigateTo(*m_pCurrentGroup, sSceneName);
}

//
void PK_SceneManager::NavigateTo(const PK_String &sSceneName, PK_SceneTransition *pCloseTransition, PK_SceneTransition *pOpenTransition)
{
    NavigateTo(*m_pCurrentGroup, sSceneName, pCloseTransition, pOpenTransition);
}

//
void PK_SceneManager::NavigateTo(PK_tSceneGroup &group, const PK_String &sSceneName)
{
    NavigateTo(group, sSceneName, NULL, NULL);
}

//
void PK_SceneManager::NavigateTo(const PK_String &sGroupName, const PK_String &sSceneName)
{
  PK_tSceneGroup *pGroup =  m_Settings.GetSceneGroup(sGroupName);
  if (pGroup == NULL)
  {
    throw PK_SystemException("Cannot navigate to scene '%s'. Scene Group named '%s' does not exist.", __FILE__, __LINE__, sSceneName.c_str(), sGroupName.c_str());
  }

  NavigateTo(*pGroup, sSceneName, NULL, NULL);
}

//
void PK_SceneManager::NavigateTo(PK_tSceneGroup &group, const PK_String &sSceneName, PK_SceneTransition *pCloseTransition, PK_SceneTransition *pOpenTransition)
{
    if (pCloseTransition != NULL)
    {
      QueueAction(SceneActionType_CloseTransition, sSceneName, (void *)pCloseTransition, true);
    }
    QueueAction(SceneActionType_GroupLoad, sSceneName, (void *)&group, true);
    QueueAction(SceneActionType_NavigateTo, sSceneName, (void *)&group, false);
    if (pOpenTransition != NULL)
    {
        QueueAction(SceneActionType_OpenTransition, sSceneName, pOpenTransition, true);
        QueueAction(SceneActionType_RemoveTransition, sSceneName, pOpenTransition, false);
    }
}

//
void PK_SceneManager::PopUp(const PK_String &sSceneName, bool bModal)
{
    QueueAction(SceneActionType_PopUp, sSceneName,(void*) bModal, true);
}
    
//
void PK_SceneManager::SetLoadingIcon(PK_LoadingIcon *pIcon)
{
    m_SceneLoader.SetLoadingIcon(pIcon);
}
    
// Esta funcao tem como objetivo fazer o refresh de uma scene
// Utilizado principalmente em debug para fazer reload quando se esta a alterar os ficheiros objProp
void PK_SceneManager::RestartCurrentScene()
{
    if (m_pActiveScene == NULL)
    {
        return;
    }
    
    // FIXME: Isto fica estranho aqui, porque vai libertar todos os assets do tipo ObjectProperties, mesmo os que
    // nao esta em uso pelo screen que vamos libertar
    PokeEngine.GetAssetManager().UnloadAssetsOfType(AssetType_ObjectProperties);
    m_pActiveScene->InternalLoad();
    m_pActiveScene->InternalInitialize();
    m_pActiveScene->InternalOpen();
}

//
void PK_SceneManager::OnSplashClosed()
{
    NavigateToStartup();
}

// Adicionada uma accao na queue de accoes
void PK_SceneManager::QueueAction(PK_eSceneActionType actionType, const PK_String &sSceneName, void *param, bool bSyncronous)
{
    PK_tSceneAction *pAction = new PK_tSceneAction();
    PK_CHECK_OBJECT_ALLOC(PK_tSceneAction, pAction);
    pAction->actionType = actionType;
    pAction->sSceneName = sSceneName;
    pAction->param = param;
    pAction->bSyncronous = bSyncronous;
    m_QueuedSceneActions.Add(pAction);
}
    
//
void PK_SceneManager::ProcessQueuedSceneActions(const PK_GameTimer &time)
{
    // Remover os ecrans que foram fechados
    for(PK_ListIterator(PK_Scene *) itor = m_ActiveScenes.Begin(); itor != m_ActiveScenes.End(); itor++)
    {
        if ((*itor)->IsClosed())
        {
            m_ActiveScenes.Remove((*itor));
            (*itor)->OnClose();
        }
    } 
    
    if (m_QueuedSceneActions.GetCount() > 0)
    {
        for(PK_ListIterator(PK_tSceneAction *) itor = m_QueuedSceneActions.Begin(); itor != m_QueuedSceneActions.End(); )
        {
            ProcessSceneAction(*(*itor), time);
            if ((*itor)->bSyncronous) // Syncronous actions break the loop. Next action should only run when current action ends
            {
                m_QueuedSceneActions.Remove((*itor));
                break;
            }
            itor = m_QueuedSceneActions.Erase(itor);
        }
    }
}

//
void PK_SceneManager::ProcessSceneAction(PK_tSceneAction &action, const PK_GameTimer &time)
{
    switch (action.actionType)
    {
        case SceneActionType_PopUp:
            {
                PK_Scene * popUpScene = GetScene(action.sSceneName);
                bool bModal = (action.param == 0? false: true);
                if (bModal)
                {
                    DisableAllActiveScenes();
                }
                m_pActiveScene = popUpScene;
                AddActiveScene(popUpScene);
                popUpScene->InternalInitialize();
                popUpScene->InternalOpen();
            }
            break;
            
        case SceneActionType_GroupLoad:
            {
                PK_tSceneGroup * pGroup = (PK_tSceneGroup *)action.param;
                if (pGroup != m_pCurrentGroup)
                {
                    LoadGroup(pGroup->sName);
                }
            }
            break;
            
        case SceneActionType_NavigateTo:
            {
                PK_Scene * pNavigateScene = GetScene(action.sSceneName);
                if (m_pActiveScene != NULL)
                {
                    m_pActiveScene->InternalClose();
                }
                ClearActiveScenes();
                m_pActiveScene = pNavigateScene;
                AddActiveScene(pNavigateScene);
                pNavigateScene->InternalInitialize();
                pNavigateScene->InternalOpen();
                pNavigateScene->InternalUpdate(time);
            }
            break;
            
        case SceneActionType_OpenTransition:
            {
                SetTransition((PK_SceneTransition *)action.param);
                m_CurrentTransitionType = TransitionType_Open;
                m_pTransition->OnInitialize();
                m_pTransition->OnStart();
            }
            break;
            
        case SceneActionType_CloseTransition:
            {
                SetTransition((PK_SceneTransition *)action.param);
                m_CurrentTransitionType = TransitionType_Close;
                m_pTransition->OnInitialize();
                m_pTransition->OnStart();
            }
            break;
            
        case SceneActionType_RemoveTransition:
            SetTransition(NULL);
            break;
            
        default:
            throw PK_SystemException("Unexpected Scene Action '%d'.", __FILE__, __LINE__, action.actionType);
    }
    
}
    
//
void PK_SceneManager::AddActiveScene(PK_Scene *pScene)
{
    m_ActiveScenes.Add(pScene);
    pScene->Grab();
}

//
void PK_SceneManager::DisableAllActiveScenes()
{
    // Active scenes
    for(PK_ListIterator(PK_Scene *) itor = m_ActiveScenes.Begin(); itor != m_ActiveScenes.End(); itor++)
	{
        (*itor)->SetActive(false);
    }
}

//
void PK_SceneManager::ClearActiveScenes()
{

    // Active scenes
    for(PK_ListIterator(PK_Scene *) itor = m_ActiveScenes.Begin(); itor != m_ActiveScenes.End(); itor++)
	{
        (*itor)->Release();
    }
	m_ActiveScenes.Clear();
}
    
//
void PK_SceneManager::ClearScenes()
{
   
    // Scenes
	for(PK_ListIterator(PK_Scene *) itor = m_Scenes.Begin(); itor != m_Scenes.End(); itor++)
	{
        (*itor)->InternalUnload();
        (*itor)->Release();
    }
	m_Scenes.Clear();
}
    
//
void PK_SceneManager::ClearQueuedActions()
{
    // Scenes
	for(PK_ListIterator(PK_tSceneAction *) itor = m_QueuedSceneActions.Begin(); itor != m_QueuedSceneActions.End(); itor++)
	{
        delete (*itor);
    }
	m_QueuedSceneActions.Clear();
}
    
//
void PK_SceneManager::SetTransition(PK_SceneTransition *pTransition)
{
    if (m_pTransition != NULL)
    {
        m_pTransition->Release();
    }
    
    m_pTransition = pTransition;
    if (m_pTransition != NULL)
    {
        m_pTransition->Grab();
    }
    else
    {
        m_CurrentTransitionType = TransitionType_None;
    }
}
    
//
void PK_SceneManager::AddScene(PK_Scene * pScene)
{
    m_Scenes.Add(pScene);
    pScene->Grab();
}

} // namespace
