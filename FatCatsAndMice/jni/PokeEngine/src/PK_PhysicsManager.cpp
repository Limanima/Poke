#include "PK_PhysicsManager.h"
#include "PK_Body.h"
#include "PK_Exceptions.h"
#include "PK_Scene.h"

#define DEFAULT_PIXELS_PER_METER  300

namespace PK {

//
PK_PhysicsManager::PK_PhysicsManager(PK_Scene &scene, const PK_String &sName) :
  PK_Component(sName)
{
	SetTypeName("PK_PhysicsManager");
    m_pScene = &scene;
    m_pOnBodiesCollided = NULL;
    m_vGravity = PK_DEFAULT_GRAVITY;
    m_fPixelsPerMeter = DEFAULT_PIXELS_PER_METER;
 }

//
PK_PhysicsManager::~PK_PhysicsManager()
{
    for(PK_ListIterator(PK_Body *) itor = m_Bodies.Begin(); itor != m_Bodies.End(); )
    {
      RemoveBody(*(*itor));
      itor = m_Bodies.Begin();
    }
    m_Bodies.Clear();
}

//
void PK_PhysicsManager::InternalInitialize()
{
    m_Settings.Load(PK_PHYISICSMANAGER_SETTINGS_FILE);
    SetVisible(m_Settings.GetVisible());
    SetGravity(m_Settings.GetGravity());
    SetPixelsPerMeter(m_Settings.GetPixelsPerMeter());
    OnInitialize();
}

//
void PK_PhysicsManager::AddBody(PK_Body &body)
{
  m_Bodies.Add(&body);
  body.Grab();
}

//
void PK_PhysicsManager::RemoveBody(PK_Body &body)
{
    if (!m_Bodies.Contains(&body))
    {
        throw PK_SystemException("Cannot remove body named '%s' from this physics manager because not part of the simulation.", __FILE__, __LINE__, body.GetName().c_str());
    }
    m_Bodies.Remove(&body);
    OnBodyRemoved(body);
    body.Release();
}

//
void PK_PhysicsManager::SetCollisionCallback(PK_ICollisionCallback *pCallback)
{ 
  m_pOnBodiesCollided = pCallback;
}

//
void PK_PhysicsManager::InvokeOnCollisionCallback(PK_Body &bodyA, PK_Body &bodyB)
{
  if (m_pOnBodiesCollided != NULL)
  {
    m_pOnBodiesCollided->Execute(bodyA, bodyB);
  }
}

} // namespace
