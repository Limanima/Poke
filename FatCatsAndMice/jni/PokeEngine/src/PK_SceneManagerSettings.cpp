#include "PK_Consts.h"
#include "PK_SceneManagerSettings.h"
#include "PK_Profiler.h"
#include "PK_Exceptions.h"
#include "PK_Types.h"
#include "PK_DataFiles.h"

namespace PK {

PK_SceneManagerSettings::PK_SceneManagerSettings() :
    PK_Settings(PK_SCENE_MANAGER_SETTINGS_NAME, "pokeSettings/sceneManager")
{
    SetTypeName("PK_SceneManagerSettings");
}
    
PK_SceneManagerSettings::~PK_SceneManagerSettings()
{
	// Libertar todos os grupos
	for(PK_ListIterator(PK_tSceneGroup *) itor = m_SceneGroups.Begin(); itor != m_SceneGroups.End(); itor++)
	{
		if ((*itor)->scenes != NULL)
		{
			delete [] (*itor)->scenes;
		}
		delete (*itor);
	}
	m_SceneGroups.Clear();
}
    
//
void PK_SceneManagerSettings::OnLoad()
{
    m_sStartupGroupName = GetParameterValue_String("startupGroup");
    m_sStartupSceneName = GetParameterValue_String("startupScene");
    m_sScenesPath = GetParameterValue_String("scenesPath");
    
    PK_DataFileRecord * pRecord = GetRootRecord();
    // Procurar todos os grupos de ecrans
    PK_List<PK_DataFileRecord *> groupRecs;
    pRecord->SelectRecords("sceneGroup", groupRecs, false);
    for(PK_ListIterator(PK_DataFileRecord *) itor = groupRecs.Begin(); itor != groupRecs.End(); itor++)
    {
        PK_DataFileRecord * groupRec = (*itor);
        // Criar o grupo
        PK_tSceneGroup *pGroup = new PK_tSceneGroup();
        PK_CHECK_OBJECT_ALLOC(PK_tSceneGroup, pGroup);
        pGroup->sName = groupRec->GetFieldValue_String("name");
        pGroup->scenes = NULL;
        pGroup->uiSceneCount = 0;
        m_SceneGroups.Add(pGroup);
        
        // Procurar todas as scenes dentro do grupo
        PK_List<PK_DataFileRecord *> sceneRecs;
        groupRec->SelectRecords("scenes/scene", sceneRecs, false);
        if (sceneRecs.GetCount() > 0)
        {
            // Inicializar o array de scenes dentro do grupo
            pGroup->uiSceneCount = sceneRecs.GetCount();
            pGroup->scenes = new PK_tSceneGroupItem[pGroup->uiSceneCount];
            PK_CHECK_OBJECT_ALLOC(PK_tSceneGroupItem, pGroup->scenes);
            
            int i = 0;
            for(PK_ListIterator(PK_DataFileRecord *) itor = sceneRecs.Begin(); itor != sceneRecs.End(); itor++, i++)
            {
                // Inicializar a scene e adicionar ao grupo
                pGroup->scenes[i].sName = (*itor)->GetFieldValue_String("name");
            }
        }
    }
}
    
//
PK_tSceneGroup * PK_SceneManagerSettings::GetSceneGroup(const PK_String &sGroupName)
{
    for(PK_ListIterator(PK_tSceneGroup *) itor = m_SceneGroups.Begin(); itor != m_SceneGroups.End(); itor++)
    {
        if ((*itor)->sName == sGroupName)
        {
            return (*itor);
        }
    }
    
    throw PK_SystemException("Could not find Scene Group named '%s'", __FILE__, __LINE__, sGroupName.c_str());
}

}