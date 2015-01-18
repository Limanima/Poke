#ifndef _PK_BOX2DBODY_H_
#define _PK_BOX2DBODY_H_

#include <box2d/box2d.h>
#include "PK_Body.h"
#include "PK_MathHelper.h"

namespace PK {
 
class PK_Box2DPhysicsManager;

class PK_Box2DBody : public PK_Body
{
private:
    b2Body * m_pBody;
    PK_Box2DPhysicsManager * m_pManager;

public:
    PK_Box2DBody(b2Body *pBody, PK_Box2DPhysicsManager &manager, const PK_String &sName);
    
    PK_Vector2 GetPosition();
    void ApplyForce(const PK_Vector2 &vForce);
    void ApplyForce(const PK_Vector2 &vForce, const PK_Vector2 &vLocation);
    void RemoveFromSimulation();
    void OnRemovedFromBox2DWorld();
    void OnControlAttached(PK_2DSceneControl &control);
    void SetCollisionMask(unsigned short uiMask, int iPartIdx = -1);

    inline float GetRotation() { return (-PK_MathHelper::RadiansToDegrees(m_pBody->GetAngle())); }
    inline b2Body *GetBox2DBody() { return m_pBody; }
    inline bool WasDisposed() { return (m_pBody == NULL); }
    PK_Vector2 GetVelocity();
    float GetMass();
    void SetLinearDamping(float fDamping);
    void Rotate(float fAngle);
    void SetPosition(float x, float y);
    void SetRotation(float degrees);
    inline void SetPosition(const PK_Vector2 &vPos) { SetPosition(vPos.x, vPos.y);}
    void SetWorldPosition(float x, float y);
    virtual void SetWorldPosition(const PK_Vector2 &vPos) { SetWorldPosition(vPos.x, vPos.y);}
};

}

#endif
