#ifndef _PK_BOUNDINGSQUARE_H_
#define _PK_BOUNDINGSQUARE_H_

#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "PK_Consts.h"
#include "PK_tAABoundingSquare.h"
#include "PK_tSize.h"
#include "PK_Matrix4.h"
#include "PK_Vector2.h"

namespace PK {

// Representa um rectangulo (axis oriented)
struct PK_tBoundingSquare
{
public:
    static const int LL_IDX = 0;
    static const int UL_IDX = 1;
    static const int UR_IDX = 2;
    static const int LR_IDX = 3;
    
public:
    // Vertices da bounding box
    //
    // UL 1------2 UR
    //    |      |
    //    |      |
    // LL 0------3 LR
    //
    PK_Vector2 m_Vertices[4];

public:
    PK_tBoundingSquare ();
    PK_tBoundingSquare (const PK_tBoundingSquare &bs);
    PK_tBoundingSquare (float x, float y, float width, float height);
    PK_tBoundingSquare (int x, int y, int width, int height);
    PK_tBoundingSquare (float x, float y, const PK_tSize & size);
    void TransformInPlace(const PK_Matrix3 &mat);
	void TransformInPlace(const PK_Matrix4 &mat);
    void TransformInPlace(const PK_Vector2 &vTranslation);
    void Set(float x, float y, float width, float height);
    inline void Set(float x, float y, PK_tSize &size) { Set(x, y, size.w, size.h); }
    bool ContainsPoint(const PK_Vector2 &vPoint);
    void operator=(const PK_tBoundingSquare & bs)
    {
        for(int i = 0; i< 4; i++)
        {
            m_Vertices[i] = bs.m_Vertices[i];
        }
    }
    void ToTextureCoords(const PK_tSize &size, PK_Vector2 retCoords[4]) const;
    inline float GetX() { return m_Vertices[0].x; }
    inline float GetY() { return m_Vertices[0].y; }
    inline float GetWidth() const { return abs(m_Vertices[LL_IDX].x - m_Vertices[LR_IDX].x); }
    inline float GetHeight() const { return abs(m_Vertices[LL_IDX].y - m_Vertices[UL_IDX].y); }
    inline float GetMinX() const { return std::min(m_Vertices[LL_IDX].x, m_Vertices[UL_IDX].x); }
    inline float GetMaxX() const { return std::max(m_Vertices[LL_IDX].x, m_Vertices[UR_IDX].x); }
    inline float GetMinY() const { return std::min(m_Vertices[UL_IDX].y, m_Vertices[LR_IDX].y); }
    inline float GetMaxY() const { return std::max(m_Vertices[UL_IDX].y, m_Vertices[LR_IDX].y); }

    inline bool IsAxisOriented() const { return (m_Vertices[LL_IDX].x == m_Vertices[UL_IDX].x); }

    inline void ToAABoundingSquare(PK_tAABoundingSquare &retBS) const
    {
        retBS.Set(GetMinX(), GetMaxY(), GetWidth(), GetHeight());
    }

};

}

#endif