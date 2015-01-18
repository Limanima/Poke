#ifndef _PK_ASSETMANAGERPROFILERITEM_H_
#define _PK_ASSETMANAGERPROFILERITEM_H_

#include "PK_ProfilerItem.h"

namespace PK {

class PK_Panel;
class PK_FontAsset;
    
class PK_AssetManagerProfilerItem : public PK_ProfilerItem
{
private:
    PK_Panel *m_pPnlDody;
    PK_FontAsset *m_pFont;

public:
    PK_AssetManagerProfilerItem(const PK_String &sName, PK_Profiler & owner);
    ~PK_AssetManagerProfilerItem();
    void FreeResources();
    void InternalUnload();
    void OnInitialize();
    void OnDraw();

};

}

#endif
