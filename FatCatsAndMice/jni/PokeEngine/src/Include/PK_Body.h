#ifndef _PK_BODY_H_
#define _PK_BODY_H_

#include "PK_Object.h"
#include "PK_Vector2.h"
#include "PK_Types.h"

namespace PK {

class PK_2DSceneControl;

class PK_Body : public PK_Object
{
private:
    PK_2DSceneControl          *m_pControl;
    PK_eBodyType                m_BodyType;
 
public:
    PK_Body(PK_eBodyType bodyType, const PK_String &sName);
    ~PK_Body();

    void SetAttachedControl(PK_2DSceneControl *pControl);
    void OnCollideWithBody(PK_Body &body);
    virtual void RemoveFromSimulation() { }
    virtual void OnControlAttached(PK_2DSceneControl &control) { }
    virtual void OnControlDettached() { }
    virtual void SetCollisionMask(unsigned short uiMask, int iPartIdx = -1) = 0;

    virtual PK_Vector2 GetPosition() = 0;
    virtual float GetRotation() = 0;
    virtual void ApplyForce(const PK_Vector2 &vForce) = 0;
    virtual void ApplyForce(const PK_Vector2 &vForce, const PK_Vector2 &vLocation) = 0;
    virtual PK_Vector2 GetVelocity() = 0;
    virtual float GetMass() = 0;
    virtual void SetLinearDamping(float fDamping) = 0;
    virtual void Rotate(float fAngle) = 0;
    virtual void SetPosition(float x, float y) = 0;
    virtual void SetRotation(float degrees) = 0;
    virtual void SetPosition(const PK_Vector2 &vPos) = 0;
    virtual void SetWorldPosition(float x, float y) = 0;
    virtual void SetWorldPosition(const PK_Vector2 &vPos) = 0;

    inline PK_2DSceneControl * GetParentControl() { return (m_pControl); }
};

}

#endif
