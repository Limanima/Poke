#include "PK_Consts.h"
#include "PK_Globals.h"
#include "PK_ProfilerMenu.h"
#include "PK_Color.h"
#include "PK_Button.h"
#include "PK_FPSCounterProfilerItem.h"
#include "PK_AssetManagerProfilerItem.h"
#include "PK_LoadedObjsProfilerItem.h"

namespace PK {

PK_ProfilerMenu::PK_ProfilerMenu(const PK_String &sName) :
    PK_2DSceneControl(sName)
{
    SetBackgroundColor(PK_Color(0.2f, 0.2f, 0.2f, 0.8f));
    SetSize(300.0f, 300.0f);
    SetParentAlignment(ParentAlignment_Center);
    SetPadding(10.0f);

    // Debug object list
    m_pBtnObjList = new PK_Button(sName + "_btnDebug");
    m_pBtnObjList->SetDockStyle(DockStyle_Top);
    m_pBtnObjList->SetHeight(30.0f);
    m_pBtnObjList->SetText("Show/Hide loaded objects");
    m_pBtnObjList->SetBackgroundColor(PK_Color(PK_COLOR_GREEN));
    m_pBtnObjList->SetFont(PK_FONT_NAME);
    m_pBtnObjList->OnClick.Set(new PK::PK_ObjectCallback<PK_ProfilerMenu>(*this, &PK_ProfilerMenu::BtnShowHideObjects_Click));
    AddControl(m_pBtnObjList);

    // Debug asset list
    m_pBtnAssetList = new PK_Button(sName + "_btnAssets");
    m_pBtnAssetList->SetDockStyle(DockStyle_Top);
    m_pBtnAssetList->SetHeight(30.0f);
    m_pBtnAssetList->SetText("Show/Hide loaded assets");
    m_pBtnAssetList->SetBackgroundColor(PK_Color(PK_COLOR_GREEN));
    m_pBtnAssetList->SetFont(PK_FONT_NAME);
    m_pBtnAssetList->OnClick.Set(new PK::PK_ObjectCallback<PK_ProfilerMenu>(*this, &PK_ProfilerMenu::BtnShowHideAssets_Click));
    AddControl(m_pBtnAssetList);

    // Debug asset list
    m_pBtnFPS = new PK_Button(sName + "_btnFPS");
    m_pBtnFPS->SetDockStyle(DockStyle_Top);
    m_pBtnFPS->SetHeight(30.0f);
    m_pBtnFPS->SetText("Show/Hide FPS");
    m_pBtnFPS->SetBackgroundColor(PK_Color(PK_COLOR_GREEN));
    m_pBtnFPS->SetFont(PK_FONT_NAME);
    m_pBtnFPS->OnClick.Set(new PK::PK_ObjectCallback<PK_ProfilerMenu>(*this, &PK_ProfilerMenu::BtnShowHideFPS_Click));
    AddControl(m_pBtnFPS);
    
    // Reload Scene
    m_pBtnReloadScene = new PK_Button(sName + "_btnReloadScene");
    m_pBtnReloadScene->SetDockStyle(DockStyle_Top);
    m_pBtnReloadScene->SetHeight(30.0f);
    m_pBtnReloadScene->SetText("Reload Scene");
    m_pBtnReloadScene->SetBackgroundColor(PK_Color(PK_COLOR_GREEN));
    m_pBtnReloadScene->SetFont(PK_FONT_NAME);
    m_pBtnReloadScene->OnClick.Set(new PK::PK_ObjectCallback<PK_ProfilerMenu>(*this, &PK_ProfilerMenu::BtnReloadScene_Click));
    AddControl(m_pBtnReloadScene);
}

//
void PK_ProfilerMenu::BtnShowHideObjects_Click(PK::PK_Object &sender)
{
//    PK_LoadedObjsProfilerItem *pLoadedObjects = PokeEngine.GetProfiler().GetLoadedObjects();
//    pLoadedObjects->SetVisible(!pLoadedObjects->IsVisible());
}

//
void PK_ProfilerMenu::BtnShowHideAssets_Click(PK::PK_Object &sender)
{
//    PK_AssetManagerProfilerItem *pAssetManager = PokeEngine.GetProfiler().GetAssetManager();
//    pAssetManager->SetVisible(!pAssetManager->IsVisible());
}

//
void PK_ProfilerMenu::BtnShowHideFPS_Click(PK::PK_Object &sender)
{
    PK_FPSCounterProfilerItem *pCounter = PokeEngine.GetProfiler().GetFPSCounter();
    pCounter->SetVisible(!pCounter->IsVisible());    
}
    
//
void PK_ProfilerMenu::BtnReloadScene_Click(PK::PK_Object &sender)
{
    PokeEngine.GetSceneManager().RestartCurrentScene();
}

}