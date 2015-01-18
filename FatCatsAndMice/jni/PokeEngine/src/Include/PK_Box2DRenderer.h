#ifndef _PK_BOX2DRENDERER_H_
#define _PK_BOX2DRENDERER_H_

#include <box2d/box2d.h>

namespace PK {

class PK_Camera;
class PK_Box2DPhysicsManager;

class PK_Box2DRenderer : public ::b2Draw
{
private:
    PK_Box2DPhysicsManager  *m_pManager;
    PK_Camera               *m_pCamera;
    PK_Camera               *m_pEngineCamera;

public:
    PK_Box2DRenderer(PK_Box2DPhysicsManager &manager);
    ~PK_Box2DRenderer();
    void BeginRender();
    void EndRender();
  	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	void DrawTransform(const b2Transform& xf);
    void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
    void DrawString(int x, int y, const char* string, ...); 
    void DrawString(const b2Vec2& p, const char* string, ...);
    void DrawAABB(b2AABB* aabb, const b2Color& color);

   
};

} // namespace

#endif