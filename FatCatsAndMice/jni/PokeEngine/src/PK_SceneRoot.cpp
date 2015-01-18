#include "PK_SceneRoot.h"
#include "PK_Globals.h"
#include "PK_Log.h"

namespace PK {
//
PK_SceneRoot::PK_SceneRoot(const PK_String &sName, PK_Scene &scene) :
    PK_2DSceneControl(sName)
{
	SetTypeName("PK_SceneRoot");
    m_pScene = &scene;
}

// Este metodo nao chama o metodo virtual da base de proposito
// As propriedades da root sao inicializadas na Scene
void PK_SceneRoot::InitFromDataFileRecord(PK_DataFileRecord &record)
{
    InitChildsDataFileRecord(record);
}


//
void PK_SceneRoot::InternalInitialize()
{
    SetSize(GetScene()->GetCamera().GetSafeFrame().size);
    PK_2DSceneControl::InternalInitialize();
}

} // namespace
