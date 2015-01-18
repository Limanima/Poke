#include "PK_LibraryItem.h"
#include "PK_SceneControl.h"

namespace PK {

//
PK_LibraryItem::PK_LibraryItem(PK_eLibraryItemScope scope, PK_SceneControl &control, const PK_String &sName) :
  PK_LoadableObject(sName)
{
    SetTypeName("PK_LibraryItem");
    m_Scope = scope;
    m_bLoaded = false;
    m_pSceneControl = &control;
    m_pSceneControl->Grab();
}

//
PK_LibraryItem::~PK_LibraryItem()
{
  if (m_pSceneControl != NULL)
  {
      m_pSceneControl->InternalUnload();
      m_pSceneControl->Release();
  }
}

// 
void PK_LibraryItem::Load()
{
  m_pSceneControl->InternalLoad();
  m_bLoaded = true;
}

} // namespace