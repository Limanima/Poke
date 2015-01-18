#ifndef _PK_PROFILER_H_
#define _PK_PROFILER_H_

#include "PK_List.h"
#include "PK_ProfilerItem.h"
#include "PK_Scene.h"
#include "PK_FPSCounterProfilerItem.h"
#include "PK_SceneRoot.h"
#include "PK_Component.h"
#include "PK_ProfilerSettings.h"
#include "PK_RemoteDebuggerClient.h"

#ifdef POKE_DEBUG
    #define PK_PROFILER_OBJ_CREATED PK_Profiler::ObjectCreated(this);
    #define PK_PROFILER_OBJ_DESTROYED PK_Profiler::ObjectDestroyed(this);
#else
    #define PK_PROFILER_OBJ_CREATED 
    #define PK_PROFILER_OBJ_DESTROYED 
#endif

namespace PK {

class PK_Button;
class PK_Panel;
class PK_ProfilerMenu;
class PK_FPSCounterProfilerItem;
class PK_PointerInfoProfilerItem;
class PK_AssetManagerProfilerItem;
class PK_LoadedObjsProfilerItem;
class PK_Mutex;

class PK_Profiler : public PK_Component
{
protected:
    PK_ProfilerSettings *m_pSettings;

private:
    PK_Scene        *m_pScene;
    PK_List<PK_ProfilerItem *> m_Items;

    // Items
    PK_FPSCounterProfilerItem   *m_pFPSCounter;
   // PK_AssetManagerProfilerItem *m_pAssetManager;
   // PK_LoadedObjsProfilerItem   *m_pLoadedObjects;
  //  PK_PointerInfoProfilerItem  *m_pPointerInfo;

    // UI
    PK_Panel        *m_pPnlProfilerItems; // Painel para mostrar os items do profiler por trás do menu
    //PK_ProfilerMenu *m_pProfilerMenu;

public:
    PK_Profiler();
    ~PK_Profiler();
    
    void OnInitialize();
    void OnUnInitialize();
    void OnUpdate(const PK_GameTimer &timer);
    void OnDraw();
    void AddItem(PK_ProfilerItem &item);
    void BtnDebugOptions_Click(PK::PK_Object &sender);
    bool IsFPSCounterVisible();
    void SetFPSCounterVisible(bool bVisible);

    inline PK_FPSCounterProfilerItem   * GetFPSCounter() { return m_pFPSCounter; }
    //inline PK_AssetManagerProfilerItem * GetAssetManager() { return m_pAssetManager; }
    //inline PK_LoadedObjsProfilerItem   * GetLoadedObjects() { return m_pLoadedObjects; }

// Estaticos
public:
    static PK_List<PK_Object *> *pObjList;
    static PK_Mutex ObjListMutex;
    static PK_RemoteDebuggerClient m_RemoteDebugger;

	static void AssertObjectsDestroyed();
	static void ObjectCreated(PK_Object * pObj);
	static void ObjectDestroyed(PK_Object * pObj);
    static void DumpObjectList();
    static PK_Object * GetObjectX(unsigned long long address);
    static void SetToReady();
};

}

#endif