#ifndef _PK_SCENEROOT_H_
#define _PK_SCENEROOT_H_

#include "PK_2DSceneControl.h"

namespace PK {

class PK_SceneRoot : public PK_2DSceneControl
{
private:
    PK_Scene *m_pScene;

public:
    PK_SceneRoot(const PK_String &sName, PK_Scene &scene);
    void InitFromDataFileRecord(PK_DataFileRecord &record);
    virtual void InternalInitialize();
    inline PK_Scene * GetScene() { return m_pScene; }

};

}

#endif