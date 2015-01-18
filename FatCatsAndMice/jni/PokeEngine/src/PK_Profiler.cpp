#include "PK_Globals.h"
#include "PK_Profiler.h"
#include "PK_Exceptions.h"
#include "PK_Log.h"
#include "PK_Panel.h"
#include "PK_Button.h"
#include "PK_ProfilerMenu.h"
#include "PK_AssetManagerProfilerItem.h"
#include "PK_LoadedObjsProfilerItem.h"
#include "PK_InputManager.h"
#include "PK_PointerInfoProfilerItem.h"
#include "PK_RemoteDebuggerClient.h"
#include "PK_Mutex.h"

namespace PK {

PK_List<PK_Object *> * PK_Profiler::pObjList = NULL;
PK_Mutex               PK_Profiler::ObjListMutex;
PK_RemoteDebuggerClient PK_Profiler::m_RemoteDebugger;
bool                   gPK_bProfilerIsReady = false;

//   
PK_Profiler::PK_Profiler() :
  PK_Component(PK_PROFILER_NAME)
{
    SetTypeName("PK_Profiler");
    m_pSettings = NULL;

    m_pScene = new PK_Scene(GetName() + "_scene__");
    m_pScene->Grab();
    
    // Painel para mostrar os items do profiler por trs do menu
    m_pPnlProfilerItems = new PK_Panel(GetName() + "_pnlContainer");
    m_pPnlProfilerItems->SetDockStyle(DockStyle_Fill);
    m_pScene->AddControl(m_pPnlProfilerItems);

    // Profiler Menu
 //   m_pProfilerMenu = new PK_ProfilerMenu(GetName() + "_menu");
 //   m_pProfilerMenu->SetVisible(false);
 //   m_pScene->AddControl(m_pProfilerMenu);
 
    // FPS Counter
    m_pFPSCounter = new PK_FPSCounterProfilerItem(PK_FPS_COUNTER_NAME, *this);
    m_pFPSCounter->SetVisible(true);
    AddItem(*m_pFPSCounter);

    // Pointer information
  //  m_pPointerInfo = new PK_PointerInfoProfilerItem(PK_POINTER_INFO_NAME, *this);
  //  m_pPointerInfo->SetVisible(true);
  //  AddItem(*m_pPointerInfo);

    // Asset manager
 //   m_pAssetManager = new PK_AssetManagerProfilerItem(PK_ASSET_MANAGER_PROFILER_ITEM_NAME, *this);
  //  m_pAssetManager->SetVisible(false);
 //   AddItem(*m_pAssetManager);

    // Loaded objs
 //   m_pLoadedObjects = new PK_LoadedObjsProfilerItem(PK_LOADED_OBJS_PROFILER_ITEM_NAME, *this);
  //  m_pLoadedObjects->SetVisible(false);
  //  AddItem(*m_pLoadedObjects);

  //  SetVisible(false);
}

//
PK_Profiler::~PK_Profiler()
{
    for(PK_ListIterator(PK_ProfilerItem *) itor = m_Items.Begin(); itor != m_Items.End(); itor++)
    {
        (*itor)->InternalUnload();
        (*itor)->Release();
    }
    m_Items.Clear();
}
  
// 
void PK_Profiler::OnInitialize()
{  
    m_pSettings = new PK_ProfilerSettings(); 
    m_pSettings->Grab();
    m_pSettings->Load(PK_PROFILER_SETTINGS_FILE);

     
    PK_tSize res = PokeEngine.GetRenderManager().GetViewport().size;
    PK_Camera *pCamera = PK_Camera::Create2D(GetName() + "_camera", PK_tSize((float)res.w, (float)res.h));

    m_pScene->SetCamera(pCamera);
    m_pScene->InternalInitialize();
    
    for(PK_ListIterator(PK_ProfilerItem *) itor = m_Items.Begin(); itor != m_Items.End(); itor++)
    {
        (*itor)->OnInitialize();
    }
//    m_pPointerInfo->SetVisible(PokeEngine.GetInputManager().SupportsMouse() || PokeEngine.GetInputManager().SupportsTouch());


    // Inicializar o remote debugger
    if (m_pSettings->GetRemoteDebbugerEnabled())
    {
        m_RemoteDebugger.Launch(m_pSettings->GetServerName(), m_pSettings->GetServerPort());
    }

}

// 
void PK_Profiler::OnUnInitialize()
{ 
    PK_FREE(m_pSettings);

    if (m_pScene != NULL)
    {
        m_pScene->InternalUnload();   
        PK_FREE(m_pScene);
    }
}

//
void PK_Profiler::OnUpdate(const PK_GameTimer &timer)
{
    m_pScene->InternalUpdate(timer);
    for(PK_ListIterator(PK_ProfilerItem *) itor = m_Items.Begin(); itor != m_Items.End(); itor++)
    {
        if ((*itor)->IsVisible())
        {
            (*itor)->OnUpdate(timer);
        }
    }
}

//
void PK_Profiler::OnDraw()
{
    m_pScene->InternalDraw();
    for(PK_ListIterator(PK_ProfilerItem *) itor = m_Items.Begin(); itor != m_Items.End(); itor++)
    {
        if ((*itor)->IsVisible())
        {
            (*itor)->OnDraw();
        }
    }
}


//
void PK_Profiler::AddItem(PK_ProfilerItem &item)
{
    item.Grab();
    m_Items.Add(&item);
    if (item.WithUI())
    {
        PK_SceneControl * pControl = item.GetUI();
        pControl->OnInitialize();
        pControl->OnLoad();
        m_pScene->AddControl(pControl);
    }
}

// Certifica que todos os objectos foram destruidos
// Utilizado quando o jogo termina para garantir que todos os objectos foram libertados
void PK_Profiler::AssertObjectsDestroyed()
{
    if (pObjList == NULL)
    {
        return;
    }
    
    ObjListMutex.Lock();
    for(PK_ListIterator(PK_Object *) itor = pObjList->Begin(); itor != pObjList->End(); itor++)
    {
        if ((*itor)->GetName() != PK_POKE_ENGINE_NAME)
        {
            DumpObjectList();
            ObjListMutex.Unlock();
    		throw PK_SystemException("Not all objects have been released. Possible memory leak (%d object(s) were not released).", __FILE__, __LINE__, PK_Profiler::pObjList->GetCount());
        }
    }
    ObjListMutex.Unlock();
}

//
void PK_Profiler::ObjectCreated(PK_Object * pObj)
{
    if (!gPK_bProfilerIsReady)
    {
        return;
    }
/*    if (!PokeEngine.GetProfiler().IsActive())
    {
        return;
    }*/
	if (pObj == NULL)
	{
		return;
	}

    ObjListMutex.Lock();
    if (pObjList == NULL)
    {
        pObjList = new PK_List<PK_Object *>();
    }
    pObjList->Add(pObj);
    ObjListMutex.Unlock();

    if (PokeEngine.GetProfiler().m_RemoteDebugger.IsRunning())
    {
        if (PK_Thread::GetCurrentThreadId() != PK_Profiler::m_RemoteDebugger.GetThread().GetThreadId())
        {
            PokeEngine.GetProfiler().m_RemoteDebugger.AddObjectCreated((unsigned long)pObj, pObj->GetTypeName(), pObj->GetName());
        }
    }
}
    
//
void PK_Profiler::ObjectDestroyed(PK_Object * pObj)
{
    if (!gPK_bProfilerIsReady)
    {
        return;
    }
    /*
    if (!PokeEngine.GetProfiler().IsActive())
    {
        return;
    }*/

	if (pObj == NULL)
	{ 
		return;
	}

    ObjListMutex.Lock();
    if (pObjList == NULL)
    {
        pObjList = new PK_List<PK_Object *>();
    }
	pObjList->Remove(pObj);
    ObjListMutex.Unlock();
    
    if (PokeEngine.GetProfiler().m_RemoteDebugger.IsRunning())
    {
        if (PK_Thread::GetCurrentThreadId() != PK_Profiler::m_RemoteDebugger.GetThread().GetThreadId())
        {
            PokeEngine.GetProfiler().m_RemoteDebugger.AddObjectDestroyed((unsigned long)pObj);
        }
    }
}

//
void PK_Profiler::DumpObjectList()
{
    PK_Log::WriteInfo(PK_LOG_TAG, "Profiler : %d objects in memory", pObjList->GetCount());
    PK_Log::WriteInfo(PK_LOG_TAG, "---------------------------------------------------------------------");
    PK_Log::WriteInfo(PK_LOG_TAG, "Refs  Type                                 Name");
    if (pObjList != NULL)
    {        
        ObjListMutex.Lock();
        for(PK_ListIterator(PK_Object *) itor = pObjList->Begin(); itor != pObjList->End(); itor++)
        {

            PK_Object * pObj = (*itor);
            PK_Log::WriteInfo(PK_LOG_TAG, "%d   %-*.*s  %s",
                        pObj->GetRefCount(),
                        30, 30, pObj->GetTypeName().c_str(), 
                        pObj->GetName().c_str());
            
        }
        ObjListMutex.Unlock();
    }
}


//
PK_Object * PK_Profiler::GetObjectX(unsigned long long address)
{
    if (pObjList != NULL)
    {        
        ObjListMutex.Lock();
        for(PK_ListIterator(PK_Object *) itor = pObjList->Begin(); itor != pObjList->End(); itor++)
        {
            if (address == (unsigned long long)(*itor))
            {
                ObjListMutex.Unlock();
                return (*itor);
            }
        }
        ObjListMutex.Unlock();
    }
    return NULL;
}

//
void PK_Profiler::BtnDebugOptions_Click(PK::PK_Object &sender)
{
//    m_pProfilerMenu->SetVisible(!m_pProfilerMenu->IsVisible());
}

//
void PK_Profiler::SetToReady()
{
    ObjListMutex.SetName(PK_PROFILER_NAME + PK_String("_objListMutex"));
    ObjListMutex.Initialize();
    gPK_bProfilerIsReady = true;
}

}
