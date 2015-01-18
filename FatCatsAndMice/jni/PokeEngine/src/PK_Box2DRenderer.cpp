#include "PK_Box2DRenderer.h"
#include "PK_RenderManager.h"
#include "PK_GLobals.h"
#include "PK_Camera.h"
#include "PK_Box2DPhysicsManager.h"

namespace PK {

PK_Box2DRenderer::PK_Box2DRenderer(PK_Box2DPhysicsManager &manager)
{
    m_pManager = &manager;
    SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_centerOfMassBit);
    m_pCamera = NULL;
    m_pEngineCamera = NULL;
}

//
PK_Box2DRenderer::~PK_Box2DRenderer()
{
    if (m_pEngineCamera != NULL)
    {
        m_pEngineCamera->Release();
        m_pEngineCamera = NULL;
    }
    if (m_pCamera != NULL)
    {
        m_pCamera->Grab();
        m_pCamera = NULL;
    }
}

//
void PK_Box2DRenderer::BeginRender()
{
    if (m_pCamera == NULL)
    {
        m_pEngineCamera = &PokeEngine.GetRenderManager().GetCamera();
        m_pEngineCamera->Grab();
        PK_tSize size = m_pEngineCamera->GetViewport();
        size.h /= m_pManager->GetPixelsPerMeter();
        size.w /= m_pManager->GetPixelsPerMeter();
        m_pCamera = PK_Camera::Create2D(PK_PHYSICS_MANAGER_CAMERA, size);   
        m_pCamera->Grab();
    }
    PokeEngine.GetRenderManager().SetCamera(*m_pCamera);
}

//
void PK_Box2DRenderer::EndRender()
{
    PokeEngine.GetRenderManager().SetCamera(*m_pEngineCamera);
}

//
void PK_Box2DRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    PK_Vector2 *p = (PK_Vector2 *)vertices;
    PokeEngine.GetRenderManager().RenderPolygon(p, vertexCount, PK_Color(color.r, color.g, color.b, 1.0f));
}

//
void PK_Box2DRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    PK_Vector2 *p = (PK_Vector2 *)vertices;
    PokeEngine.GetRenderManager().RenderPolygon(p, vertexCount, PK_Color(color.r, color.g, color.b, 1.0f));
}

//
void PK_Box2DRenderer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
/*	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();*/
}

//
void PK_Box2DRenderer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    PK_Vector2 vPos = PK_Vector2(center.x, center.y);
    PokeEngine.GetRenderManager().RenderSolidCircle(vPos, radius, PK_Color(color.r, color.g, color.b, 1.0f), 12);
}

//
void PK_Box2DRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
/*	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();*/
}

void PK_Box2DRenderer::DrawTransform(const b2Transform& xf)
{
	/*b2Vec2 p1 = xf.p, p2;
	const float32 k_axisScale = 0.4f;
	glBegin(GL_LINES);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(p1.x, p1.y);
	p2 = p1 + k_axisScale * xf.q.GetXAxis();
	glVertex2f(p2.x, p2.y);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(p1.x, p1.y);
	p2 = p1 + k_axisScale * xf.q.GetYAxis();
	glVertex2f(p2.x, p2.y);

	glEnd();*/
}

//
void PK_Box2DRenderer::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	/*glPointSize(size);
	glBegin(GL_POINTS);
	glColor3f(color.r, color.g, color.b);
	glVertex2f(p.x, p.y);
	glEnd();
	glPointSize(1.0f);*/
}

//
void PK_Box2DRenderer::DrawString(int x, int y, const char *string, ...)
{
	/*char buffer[128];

	va_list arg;
	va_start(arg, string);
	vsprintf(buffer, string, arg);
	va_end(arg);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(0.9f, 0.6f, 0.6f);
	glRasterPos2i(x, y);
	int32 length = (int32)strlen(buffer);
	for (int32 i = 0; i < length; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]);
		//glutBitmapCharacter(GLUT_BITMAP_9_BY_15, buffer[i]);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);*/
}

//
void PK_Box2DRenderer::DrawString(const b2Vec2& p, const char *string, ...)
{
	/*char buffer[128];

	va_list arg;
	va_start(arg, string);
	vsprintf(buffer, string, arg);
	va_end(arg);

	glColor3f(0.5f, 0.9f, 0.5f);
	glRasterPos2f(p.x, p.y);

	int32 length = (int32)strlen(buffer);
	for (int32 i = 0; i < length; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer[i]);
	}

	glPopMatrix();*/
}

//
void PK_Box2DRenderer::DrawAABB(b2AABB* aabb, const b2Color& c)
{
/*	glColor3f(c.r, c.g, c.b);
	glBegin(GL_LINE_LOOP);
	glVertex2f(aabb->lowerBound.x, aabb->lowerBound.y);
	glVertex2f(aabb->upperBound.x, aabb->lowerBound.y);
	glVertex2f(aabb->upperBound.x, aabb->upperBound.y);
	glVertex2f(aabb->lowerBound.x, aabb->upperBound.y);
	glEnd();*/
}

} // namespace
