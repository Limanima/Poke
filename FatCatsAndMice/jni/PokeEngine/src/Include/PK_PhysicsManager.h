#ifndef _PK_PHYSISCSMANAGER_H_
#define _PK_PHYSISCSMANAGER_H_

#include "PK_Component.h"
#include "PK_List.h"
#include "PK_Vector2.h"
#include "PK_Types.h"
#include "PK_CollisionCallback.h"
#include "PK_PhysicsManagerSettings.h"

namespace PK {

class PK_Body;
class PK_Scene;


class PK_PhysicsManager : public PK_Component
{
protected:
    PK_PhysicsManagerSettings m_Settings;

private:
    PK_List<PK_Body *>      m_Bodies;
    PK_Scene               *m_pScene;
    PK_ICollisionCallback  *m_pOnBodiesCollided; // Flick com o rato ou touch (ponto inicial do flick sobre o controlo)
    float                   m_fPixelsPerMeter;

protected:
    PK_Vector2              m_vGravity;

public:
    PK_PhysicsManager(PK_Scene &scene, const PK_String &sName);
    ~PK_PhysicsManager();

   void InternalInitialize();
    virtual void OnInitialize() {};
    virtual void OnUnload() {};
    virtual void OnUpdate(const PK_GameTimer &timer) {};
    void RemoveBody(PK_Body &body);
    virtual void OnBodyRemoved(PK_Body &body) {}
    void SetCollisionCallback(PK_ICollisionCallback *pCallback);
    void InvokeOnCollisionCallback(PK_Body &bodyA,PK_Body &bodyB);
    inline bool HasOnCollisionCallback() { return (m_pOnBodiesCollided != NULL); }

     virtual PK_Body * CreateBody(const PK_String &sName, const PK_Vector2 &vPosition, PK_tBodyDefinition &bodyDefinition) = 0;

    //
    inline PK_Vector2 GetGravity() { return m_vGravity; }
    virtual inline void SetGravity(const PK_Vector2 &vGravity) { m_vGravity = vGravity; }
    inline float GetPixelsPerMeter() { return m_fPixelsPerMeter; }
    inline void SetPixelsPerMeter(float fPixelsPerMeter) { m_fPixelsPerMeter = fPixelsPerMeter; }
    
    inline PK_Scene & GetScene() { return *m_pScene; }
    virtual void SetVelocityThreshold(float fVelocity) = 0;

protected:
    void AddBody(PK_Body &body);
};

} // namespace

#endif