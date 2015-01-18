#include "PK_Consts.h"
#include "PK_Globals.h"
#include "PK_Scene.h"
#include "PK_Path.h"
#include "PK_SceneManager.h"
#include "PK_PhysicsManager.h"
#include "PK_ClassFactory.h"
#include "PK_InputManager.h"
#include "PK_Body.h"
#include "PK_Globals.h"

// Valores por defeito
#define DEFAULT_BACKGROUND_COLOR PK_COLOR_TRANSPARENT
#define DEFAULT_BACKGROUND_IMAGE ""

namespace PK {

PK_Scene::PK_Scene(const PK_String &sName)
{
	SetTypeName("PK_Scene");
    SetName(sName);
    m_bOpened = true;
    m_pSceneRoot = new PK_SceneRoot(sName + PK_String("_root"), *this);
    m_pSceneRoot->Grab();
    m_bActive = true;
    m_bVisible = true;
    m_pClickedControl = NULL;
    m_pFlickedControl = NULL;
    SetBackgroundColor(DEFAULT_BACKGROUND_COLOR);
    m_bUpdateStarted = false;
    m_pPhysicsManager = NULL;
    m_pCamera = NULL;
}

//
PK_Scene::~PK_Scene()
{
    PK_FREE(m_pSceneRoot);
    PK_FREE(m_pPhysicsManager);
    PK_FREE(m_pCamera);
}

//
void PK_Scene::InitFromDataFileRecord(PK_DataFileRecord &record)
{
    PK_Object::InitFromDataFileRecord(record);

   // SetBackgroundColor(record.GetChildRecordFieldValue<PK_Color>("backgroundColor", "value", DEFAULT_BACKGROUND_COLOR));
 //   SetBackgroundImage(record.GetChildRecordFieldValue<PK_String>("backgroundSprite", "value", DEFAULT_BACKGROUND_IMAGE));

    m_pSceneRoot->InitFromDataFileRecord(record);
}

// Metodo implementado para PK_LoadableObject
void PK_Scene::Load()
{
/*    PK_DataFile dataFile;
    PK_DataFileRecord *pRootRecord = dataFile.LoadFromXML(GetFilename(), "scene");
    InitFromDataFileRecord(*pRootRecord);*/
    InternalLoad();
}
    
//
void PK_Scene::InternalUnload()
{
	PK_Log::WriteInfo(PK_LOG_TAG, "Unloading scene '%s'...", GetName().c_str());
    m_PostUpdateMessages.Clear();
	
	m_BroadcastMessages.Clear();
    if (m_pSceneRoot != NULL)
    {
        m_pSceneRoot->InternalUnload();
    }

    // Libertar os items da library que tenham scope de scene
    PokeEngine.GetLibrary().RemoveItemsInScope(LibraryItemScope_Scene);

    // Libertar os componentes
    for(PK_ListIterator(PK_Component *) itor = m_Components.Begin(); itor != m_Components.End(); itor++)
    {
        PK_Component *pComp = (*itor);
        pComp->OnUnload();
        pComp->OnUnInitialize();
        pComp->Release();
    }
    m_Components.Clear();
    PK_FREE(m_pPhysicsManager);
    PK_FREE(m_pCamera);
    OnUnload();
}


// Chama o load content dos controlos da scene
void PK_Scene::InternalInitialize()
{
	PK_Log::WriteInfo(PK_LOG_TAG, "Initializing scene '%s'...", GetName().c_str());
    OnInitialize();
    m_pSceneRoot->InternalInitialize();
}
    
// Chama o load content dos controlos da scene
void PK_Scene::InternalLoad()
{
	PK_Log::WriteInfo(PK_LOG_TAG, "Loading scene '%s'...", GetName().c_str());
    OnLoad();
    m_pSceneRoot->InternalLoad();
}

//
void PK_Scene::InternalLoad(PK_ObjectLoader &loader)
{
    loader.AddToQueue(*this);
    m_pSceneRoot->AddToLoadingQueue(loader);
}

//
void PK_Scene::AddToLoadingQueue(PK_ObjectLoader &loader)
{
    loader.AddToQueue(*this);
    m_pSceneRoot->AddToLoadingQueue(loader);
}

// Corre o update dos controlos 
void PK_Scene::InternalUpdate(const PK_GameTimer &time)
{
    m_bUpdateStarted = true;
    UpdateComponents(time);
    OnUpdate(time);
    m_pSceneRoot->InternalUpdate(time);

    // No final do update lancamos o evento de click do controlo
    if (m_pClickedControl != NULL)
    {
        m_pClickedControl->InternalControlClicked();
        m_pClickedControl = NULL;
    }
    // No final do update lancamos o evento de flick do controlo
    if (m_pFlickedControl != NULL)
    {
        m_pFlickedControl->InvokeOnFlick();
    }

    if (PokeEngine.GetInputManager().QueryAction(InputAction_FlickEnded) &&
        m_pFlickedControl != NULL)
    {
        m_pFlickedControl->InvokeOnFlickEnded();
        m_pFlickedControl = NULL;
    }

    ProcessPostUpdateMessages();
    m_bUpdateStarted = false;
}

// Corre o update dos controlos 
void PK_Scene::InternalDraw()
{
    if (m_pCamera != NULL)
    {
        PokeEngine.GetRenderManager().SetCamera(*m_pCamera);
    }
    else
    {
        PokeEngine.GetRenderManager().SetToDefaultCamera();
    }

	OnDraw();
    m_pSceneRoot->InternalDraw();
    if (m_Components.GetCount() > 0)
    {
        DrawComponents();
    }
}
 
//
void PK_Scene::InternalOpen()
{
    m_bOpened = true;
    SetVisible(true);
    SetActive(true);
    EnableInput();
    OnOpen();
}

//
void PK_Scene::InternalClose()
{
    m_bOpened = false;
    SetVisible(false);
    SetActive(false);
    OnClose();
}
    
//
void PK_Scene::AddControl(PK_SceneControl * pControl)
{
  if (!m_bUpdateStarted)
  {
        m_pSceneRoot->AddControl(pControl);
  }
  else
  {
    PK_tMessage msg;
    msg.uiType = PK_MSG_ADD_CONTROL;
    msg.detail.addControl.pControlToAdd = pControl;
    msg.detail.addControl.pControlToAdd->Grab();
    msg.detail.addControl.pParent = m_pSceneRoot;
    msg.detail.addControl.pParent->Grab();
    AddPostUpdateMessage(msg);
  }    
}

//
void PK_Scene::RemoveControl(PK_SceneControl * pControl)
{
  if (pControl == NULL)
  {
      throw PK_SystemException("Control to be removed cannot be NULL.", __FILE__, __LINE__);
  }
  if (pControl->GetScene() != this)
  {
      throw PK_SystemException("SceneControl named '%s' cannot be removed from the scene because it's not a child of the scene.",
                                __FILE__, __LINE__, pControl->GetName().c_str());
        
  }
  if (pControl->GetParent() == NULL)
  {
      throw PK_SystemException("Control to be removed it's not a child of another control.", __FILE__, __LINE__);
  }

  if (!m_bUpdateStarted)
  {
    pControl->GetParent()->RemoveControlImmediate(pControl);
  }
  else
  {
   // m_ControlsToRemove.Add(pControl);
    PK_tMessage msg;
    msg.uiType = PK_MSG_REMOVE_CONTROL;
    msg.detail.removeControl.pControl = pControl;
    msg.detail.removeControl.pControl->Grab();
    AddPostUpdateMessage(msg);
    pControl->SetRemovedFromScene(true);
  }
}

// 
void PK_Scene::AddComponent(PK_Component &component)
{
  // Nao podemos adicionar se o componente ja esta adicionado a outro componente
  if (component.GetParent() != NULL)
  {
      throw PK_SystemException("Cannot add component named '%s' because it is already added to another parent.", __FILE__, __LINE__, component.GetName().c_str());
  }

  m_Components.Add(&component);
  component.Grab();
}

//
void PK_Scene::SetWithPhysics(bool bWithPhysics)
{
  if (m_pPhysicsManager == NULL && bWithPhysics)
  {
    m_pPhysicsManager = PK_ClassFactory::CreatePhysicsManager(*this, GetName() + PK_String("_physicsManager"));
    AddComponent(*((PK_Component *)m_pPhysicsManager));
    m_pPhysicsManager->InternalInitialize();
    m_pPhysicsManager->Grab();
  }

  if (m_pPhysicsManager != NULL)
  {
    m_pPhysicsManager->SetActive(bWithPhysics);
  }
}

//
PK_SceneControl & PK_Scene::GetControl(const PK_String &sName)
{
    PK_SceneControl * pControl = m_pSceneRoot->GetControl(sName);
    if (pControl == NULL)
    {
        throw PK_SystemException("Control named '%s' doesn't exist.", __FILE__, __LINE__, sName.c_str());
    }
    return *pControl;
}

// 
PK_SceneControl * PK_Scene::FindControl(const PK_String &sName)
{
    return m_pSceneRoot->GetControl(sName);
}
   
// Click callback
void PK_Scene::SetOnClickCallback(PK_IObjectCallback *pCallback)
{
    m_pSceneRoot->OnClick.Set(pCallback);
}

//
void PK_Scene::SetBackgroundImage(PK_SpriteAsset *pSprite)
{
    m_pSceneRoot->SetBackgroundImage(pSprite);
}

//
void PK_Scene::SetBackgroundImage(const PK_String &sAssetName)
{
    m_pSceneRoot->SetBackgroundImage(sAssetName);
}

//
void PK_Scene::BroadcastMessage(unsigned int uiMsg, unsigned int uiCode, unsigned long ulParam)
{
	PK_tMessage1 msg;
	msg.m_pSender = this;
	msg.uiMsg = uiMsg;
	msg.uiCode = uiCode;
	msg.uiParam = ulParam;

	m_BroadcastMessages.Add(msg);
}

//
void PK_Scene::AddPostUpdateMessage(const PK_tMessage & message)
{
    m_PostUpdateMessages.Add(message);
}

//
void PK_Scene::ProcessPostUpdateMessages()
{
    if (m_PostUpdateMessages.GetCount() > 0)
    {
		// Usamos uma copia da lista porque e possivel que estas mensagens venham a adicionar novas mensagens
		PK_List<PK_tMessage> listCopy;
		for(PK_ListIterator(PK_tMessage) itor = m_PostUpdateMessages.Begin(); itor != m_PostUpdateMessages.End(); itor++)
		{
			listCopy.Add((*itor));
		}
		m_PostUpdateMessages.Clear();

		// Itera na copia
		for(PK_ListIterator(PK_tMessage) itor = listCopy.Begin(); itor != listCopy.End(); itor++)
		{
			PK_tMessage *pMessage = &(*itor);
			switch(pMessage->uiType)
			{
				case PK_MSG_BODY_COLLISION:
					if (m_pPhysicsManager->HasOnCollisionCallback())
					{
						m_pPhysicsManager->InvokeOnCollisionCallback(*pMessage->detail.bodyCollision.pBodyA, 
																	 *pMessage->detail.bodyCollision.pBodyA);
					}
					pMessage->detail.bodyCollision.pBodyA->OnCollideWithBody(*pMessage->detail.bodyCollision.pBodyB);
					pMessage->detail.bodyCollision.pBodyB->OnCollideWithBody(*pMessage->detail.bodyCollision.pBodyA);
					pMessage->detail.bodyCollision.pBodyA->Release();
					pMessage->detail.bodyCollision.pBodyB->Release();
					break;


				case PK_MSG_REMOVE_CONTROL:
                    {
					    PK_SceneControl *pControl = pMessage->detail.removeControl.pControl;
					    if (pControl->GetScene() == NULL)
					    {
						    continue;
					    }
					    pControl->GetParent()->RemoveControlImmediate(pControl);
					    pControl->Release();
                    }
					break;

                case PK_MSG_ADD_CONTROL:
                    {
					    PK_SceneControl *pControl = pMessage->detail.addControl.pControlToAdd;
                        PK_SceneControl *pParent = pMessage->detail.addControl.pParent;
					    if (pControl->GetScene() != NULL)
					    {
						    throw PK_SystemException("Cannot add control named '%s' to scene named '%s' because it's already added.", 
                                __FILE__, __LINE__, pControl->GetName().c_str(), GetName().c_str());
					    }
					    pParent->AddControl(pControl);
                        pParent->Release();
                        pControl->Release();
                    }
					break;
                default:
                    throw PK_SystemException("Cannot process message with id '%d' because it does not exist.", __FILE__, __LINE__, pMessage->uiType);
			}
		}
		listCopy.Clear();
	}

	// Broadcast de mensagens para todos os childs
	if (m_BroadcastMessages.GetCount() > 0)
	{
		SendBroadcastMessages();
	}
}

//
void PK_Scene::SendBroadcastMessages()
{
	SendBroadcastMessages(*m_pSceneRoot);
    m_BroadcastMessages.Clear();
}

// 
void PK_Scene::SendBroadcastMessages(PK_SceneControl &currentControl)
{
	PK_List<PK_SceneControl *> *pChilds = &currentControl.GetControls();

	for(PK_ListIterator(PK_tMessage1) itor = m_BroadcastMessages.Begin(); itor != m_BroadcastMessages.End(); itor++)
	{
		PK_tMessage1 *pMsg = &(*itor);
		currentControl.OnMessageReceived(*pMsg);	
	}

	if (pChilds->GetCount() > 0)
	{
		for(PK_ListIterator(PK_SceneControl *) itor = pChilds->Begin(); itor != pChilds->End(); itor++)
		{
			SendBroadcastMessages(*(*itor));
		}
	}
}

//
PK_String PK_Scene::GetFilename()
{
    PK_String sFilename = PK_Path::Combine(PokeEngine.GetSceneManager().GetSettings().GetScenesPath(), GetName());
    return PK_Path::CombineExtension(sFilename, PK_SCENE_EXTENSION);
}

//
void PK_Scene::UpdateComponents(const PK_GameTimer &timer)
{
    if (m_Components.GetCount() > 0)
    {
      for(PK_ListIterator(PK_Component *) itor = m_Components.Begin(); itor != m_Components.End(); itor++)
      {
        PK_Component * pComponent = (*itor);
        if (pComponent->IsActive())
        {
          pComponent->OnUpdate(timer);
        }
      }
    }
}

//
void PK_Scene::DrawComponents()
{
    for(PK_ListIterator(PK_Component *) itor = m_Components.Begin(); itor != m_Components.End(); itor++)
    {
        PK_Component * pComponent = (*itor);
        if (pComponent->IsVisible())
        {
            pComponent->OnDraw();
        }
    }
}

//
PK_Camera & PK_Scene::GetCamera()
{
    if (m_pCamera == NULL)
    {
        return PokeEngine.GetRenderManager().GetDefaultCamera();
    }
    return *m_pCamera;
}

//
void PK_Scene::SetCamera(PK_Camera * pCamera)
{
    if (m_pCamera == pCamera)
    {
        return;
    }

    if (m_pCamera != NULL)
    {
        m_pCamera->Release();
    }
    m_pCamera = pCamera;
    if (m_pCamera != NULL)
    {
        m_pCamera->Grab();
    }

}

//
PK_String PK_Scene::GetAssetContainerName()
{
	return m_pSceneRoot->GetAssetContainerName();
}
} // namespace
