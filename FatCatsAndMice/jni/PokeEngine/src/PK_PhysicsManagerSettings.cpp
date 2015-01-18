#include "PK_PhysicsManagerSettings.h"
#include "PK_Profiler.h"

namespace PK {

PK_PhysicsManagerSettings::PK_PhysicsManagerSettings() :
 PK_Settings(PK_PHYSICS_MANAGER_SETTINGS_NAME, "pokeSettings/physicsManager")
{
    SetTypeName("PK_PhysicsManagerSettings");	
}

//
void PK_PhysicsManagerSettings::OnLoad()
{
    m_bVisible = GetParameterValue_Bool("visible");
    m_vGravity = GetParameterValue_Vector2("gravity");
    m_fPixelsPerMeter= GetParameterValue_Float("pixelsPerMeter");
}

}