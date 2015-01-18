#include "PK_Consts.h"
#include "PK_Globals.h"
#include "PK_AssetManagerProfilerItem.h"
#include "PK_Panel.h"
#include "PK_RenderManager.h"
#include "PK_AssetManager.h"
#include "PK_Vector2.h"
#include "PK_FontAsset.h"

namespace PK {

PK_AssetManagerProfilerItem::PK_AssetManagerProfilerItem(const PK_String &sName, PK_Profiler & owner) :
    PK_ProfilerItem(sName, owner)
{
	SetTypeName("PK_AssetManagerProfilerItem");
    m_pFont = NULL;

    m_pPnlDody = new PK_Panel(sName + "_pnlBody");
    m_pPnlDody->SetDockStyle(DockStyle_Fill);
    m_pPnlDody->SetBackgroundColor(PK_COLOR_DARK_TRANSP);
    SetUI((PK_SceneControl*)m_pPnlDody);
}

//
PK_AssetManagerProfilerItem::~PK_AssetManagerProfilerItem()
{
    FreeResources();
}

//
void PK_AssetManagerProfilerItem::FreeResources()
{
    if (m_pFont != NULL)
    {
        m_pFont->Release();
        m_pFont = NULL;
    }
}

//
void PK_AssetManagerProfilerItem::InternalUnload()
{
    FreeResources();
}

//
void PK_AssetManagerProfilerItem::OnInitialize()
{
    if (m_pFont == NULL)
    {
        m_pFont = PokeEngine.GetAssetManager().LoadFont(PK_FONT_NAME, PK_ASSET_CONTAINER_NAME);
        m_pFont->Grab();
    }
}

//
void PK_AssetManagerProfilerItem::OnDraw()
{
    PK_List<PK_AssetContainer *> *pContainers = PokeEngine.GetAssetManager().GetContainers();
    
    PK_Vector2 vPosition(10.0f, 10.0f);
    for(PK_ListIterator(PK_AssetContainer *) itor = pContainers->Begin(); itor != pContainers->End(); itor++)
	{
        PK_AssetContainer *pContainer = (*itor);
        PokeEngine.GetRenderManager().RenderText(pContainer->GetName(), *m_pFont, vPosition, PK_COLOR_RED);
        vPosition.y += 20;

        PK_List<PK_Asset *> *pAssets =  pContainer->GetAssets();
        for(PK_ListIterator(PK_Asset*) itorAsset = pAssets->Begin(); itorAsset != pAssets->End(); itorAsset++)
    	{
            PokeEngine.GetRenderManager().RenderText((*itorAsset)->GetName(), *m_pFont, vPosition, PK_COLOR_YELLOW);
            vPosition.y += 20;
        }
    }
}

} // namespace
