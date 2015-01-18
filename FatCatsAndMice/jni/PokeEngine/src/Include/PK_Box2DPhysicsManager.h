#ifndef _PK_BOX2DPHYSISCSMANAGER_H_
#define _PK_BOX2DPHYSISCSMANAGER_H_

#include <box2d/box2d.h>
#include "PK_PhysicsManager.h"
#include "PK_Box2dRenderer.h"
#include "PK_Box2DContactListener.h"

namespace PK {

class PK_Box2DRenderer;
class PK_Box2DContactListener;

class PK_Box2DPhysicsManager : public PK_PhysicsManager
{

private:
    b2World             *m_pWorld;
    PK_Box2DRenderer    *m_pRenderer;
    int                  m_iPositionIterations;
    int                  m_iVelocityIterations;
    PK_Box2DContactListener * m_pContactListener;

public:
    PK_Box2DPhysicsManager(PK_Scene &scene, const PK_String &sName);
    ~PK_Box2DPhysicsManager();

    void OnUpdate(const PK_GameTimer &timer);
    void OnDraw();
    void SetVisible(bool bVisible);
    void OnBodyRemoved(PK_Body &body);

    // Criacao de bodies
    PK_Body * CreateBody(const PK_String &sName, const PK_Vector2 &vPosition, PK_tBodyDefinition &bodyDefinition);

    inline void SetGravity(const PK_Vector2 &vGravity);
    
    // Converters & helpers
    static PK_eBodyType ConvertBodyType(b2BodyType type);
    static b2BodyType ConvertBodyType(PK_eBodyType type);
    inline static b2Vec2 ConvertVector(const PK_Vector2 &v)
    {
        return b2Vec2(v.x, v.y);
    }
    inline b2Vec2 EngineToB2dSystem(const PK_Vector2 v)
    {
        return b2Vec2(v.x / GetPixelsPerMeter(), v.y / GetPixelsPerMeter());
    }
    inline float EngineToB2dSystem(float fVal)
    {
        return (fVal / GetPixelsPerMeter());
    }

    void SetVelocityThreshold(float fVelocity);

};

} // namespace

#endif