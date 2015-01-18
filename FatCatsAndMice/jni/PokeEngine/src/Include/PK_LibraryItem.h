#ifndef _PK_LIBRARYITEM_H_
#define _PK_LIBRARYITEM_H_

#include "PK_LoadableObject.h"
#include "PK_Types.h"

namespace PK {
      
// 
class PK_LibraryItem : public PK_LoadableObject
{
private:
	PK_eLibraryItemScope  m_Scope;
    PK_SceneControl      *m_pSceneControl;
    int                   m_iIndex; // Indice no array 
    bool                  m_bLoaded;

public:
    PK_LibraryItem(PK_eLibraryItemScope scope, PK_SceneControl &control, const PK_String &sName);
    ~PK_LibraryItem();
    void Load();

    inline PK_eLibraryItemScope GetScope() { return m_Scope; }
    inline PK_SceneControl & GetControl() { return *m_pSceneControl; }
    inline bool IsLoaded() { return m_bLoaded; }
};

} // namespace

#endif