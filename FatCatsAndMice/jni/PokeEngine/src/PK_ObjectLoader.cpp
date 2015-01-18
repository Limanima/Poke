#include "PK_Globals.h"
#include "PK_ObjectLoader.h"
#include "PK_Exceptions.h"
#include "PK_LoadingIcon.h"
#include "PK_Log.h"

namespace PK {

PK_ObjectLoader::PK_ObjectLoader()
{
    SetTypeName("PK_ObjectLoader");
    SetName(PK_OBJECT_LOADER_NAME);
    m_bIsLoading = false;
    m_pLoadingIcon = NULL;
}

//
PK_ObjectLoader::~PK_ObjectLoader()
{
    OnUnload();
}
    
//
void PK_ObjectLoader::OnUpdate(const PK_GameTimer &time)
{
    if (IsLoading() == false)
    {
        return;
    }
    
    if (m_pLoadingIcon != NULL &&
        m_pLoadingIcon->IsVisible())
    {
        m_pLoadingIcon->InternalUpdate(time);
    }
    
    if (!IsQueueEmpty())
    {
        LoadQueuedObject();
    }
    else
    {
        EndLoading();
    }
}
    
//
void PK_ObjectLoader::OnDraw()
{
    if (m_pLoadingIcon != NULL)
    {
        m_pLoadingIcon->InternalDraw();
    }
}

//
void PK_ObjectLoader::OnUnload()
{
    SetLoadingIcon(NULL);
    ClearQueue();
}
       
//
void PK_ObjectLoader::StartLoading()
{
    if (m_bIsLoading)
    {
        throw PK_SystemException("Cannot start a new scene load while a loading is in progress.", __FILE__, __LINE__);
    }
    
    m_bIsLoading = true;
        
    // Mostrar o icon do loading
    if (m_pLoadingIcon != NULL)
    {
        m_pLoadingIcon->SetVisible(true);
    }
}

//
void PK_ObjectLoader::EndLoading()
{
    if (!m_bIsLoading)
    {
        throw PK_SystemException("Cannot end a scene loading because a load has not been started.", __FILE__, __LINE__);
    }
    
    m_bIsLoading = false;
    
    // Esconder o icon do loading
    if (m_pLoadingIcon != NULL)
    {
        m_pLoadingIcon->SetVisible(false);
    }
}

// Aceita NULL para se poder remover o icon
void PK_ObjectLoader::SetLoadingIcon(PK_LoadingIcon *pIcon)
{
    if (m_pLoadingIcon != NULL)
    {
        m_pLoadingIcon->Release();
    }
    m_pLoadingIcon = pIcon;
    if(m_pLoadingIcon != NULL)
    {
        m_pLoadingIcon->Grab();
        m_pLoadingIcon->InternalInitialize();
        m_pLoadingIcon->InternalLoad();
    }
}

//
void PK_ObjectLoader::AddToQueue(PK_LoadableObject &obj)
{
  PK_LoadableObject * pObject = &obj;
  m_LoadingQueue.Add(pObject);
  pObject->Grab();
}

//
void PK_ObjectLoader::ClearQueue()
{
  for(PK_ListIterator(PK_LoadableObject *) itor = m_LoadingQueue.Begin(); itor != m_LoadingQueue.End(); itor++)
  {
    (*itor)->Release();
  }
  m_LoadingQueue.Clear();
}

//
void PK_ObjectLoader::LoadQueuedObject()
{
  if (IsQueueEmpty())
  {
    return;
  }
  
  PK_ListIterator(PK_LoadableObject *) item = m_LoadingQueue.Begin();
  PK_LoadableObject *pObject = (*item);
  PK_Log::WriteInfo(PK_LOG_TAG, "Loading object [%s] type[%s]", pObject->GetName().c_str(), pObject->GetTypeName().c_str());
  m_LoadingQueue.Erase(item);
  pObject->Load();
  pObject->Release();
}

} // namespace