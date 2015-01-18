#ifndef _PK_CAMERA_H_
#define _PK_CAMERA_H_

#include "PK_Object.h"
#include "PK_Matrix4.h"
#include "PK_tSize.h"
#include "PK_Types.h"

namespace PK {
    
class PK_Camera : public PK_Object
{
protected:
    PK_Matrix4 m_matView;
    PK_Matrix4 m_matProjection;
    PK_Matrix4 m_matViewProjection;
    PK_Matrix4 m_matViewProjectionInverse;
    PK_tSize m_Viewport;
    PK_tAABoundingSquare m_frame;
    PK_tAABoundingSquare m_safeFrame;
    PK_Vector2 m_safeFrameBorder;
    
public:
    PK_Camera();
    inline PK_Matrix4 GetProjectionMatrix() { return m_matViewProjection; }
    inline PK_Matrix4 * GetProjectionMatrixPtr() { return &m_matViewProjection; }
    void SetProjection(const PK_Matrix4 &proj);
    void SetView(const PK_Matrix4 &view);
    PK_Vector2 Unproject(const PK_Vector2 &coords);
    PK_Vector2 UnprojectOffset(const PK_Vector2 &vPoint);

    inline PK_tAABoundingSquare & GetSafeFrame() { return  m_safeFrame; }
    inline PK_tAABoundingSquare & GetFrame() { return  m_frame; }
    inline PK_tSize GetViewport() { return m_Viewport; }
    static PK_Camera * Create2D(const PK_String & sName, const PK_tSize &viewportSize);

private:
    void InitFrames(const PK_tSize &viewportSize);
};
    
} // namespace

#endif
