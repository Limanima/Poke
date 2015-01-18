#include "PK_tBoundingSquare.h"
#include "PK_Exceptions.h"
#include "PK_Vector3.h"
#include "PK_TextureAsset.h"

// Format DataFile de tSize
//
//<size>
//    <width value="10"/>
//    <height value="20"/>
//</size>
namespace PK
{
    
PK_tBoundingSquare::PK_tBoundingSquare()
{
    Set(.0f, .0f, .0f, .0f);
}
    
PK_tBoundingSquare::PK_tBoundingSquare(const PK_tBoundingSquare &bs)
{
    for(int i= 0 ; i < 4; i++)
    {
        m_Vertices[i] = bs.m_Vertices[i];
    }
}
    
PK_tBoundingSquare::PK_tBoundingSquare (float x, float y, float width, float height)
{
    Set(x, y, width, height);
}

PK_tBoundingSquare::PK_tBoundingSquare (int x, int y, int width, int height)
{
    Set((float)x, (float)y, (float)width, (float)height);
}

PK_tBoundingSquare::PK_tBoundingSquare (float x, float y, const PK_tSize & size)
{
    Set(x, y, size.w, size.h);
}


//
void PK_tBoundingSquare::TransformInPlace(const PK_Matrix3 &mat)
{
    for(int i = 0; i < 4; i++)
    {
        m_Vertices[i] = PK_Vector2(mat * PK_Vector3(m_Vertices[i], 1.0f));
   }
}

//
void PK_tBoundingSquare::TransformInPlace(const PK_Matrix4 &mat)
{
    for(int i = 0; i < 4; i++)
    {
        m_Vertices[i] = PK_Vector2(mat * PK_Vector4(m_Vertices[i], 1.0f, 1.0f));
   }
}
//
void PK_tBoundingSquare::TransformInPlace(const PK_Vector2 &vTranslation)
{
    for(int i = 0; i < 4; i++)
    {
        m_Vertices[i] += vTranslation;
   }
}  
//
void PK_tBoundingSquare::Set(float x, float y, float width, float height)
{
    m_Vertices[LL_IDX] = PK_Vector2(x, y);
    m_Vertices[UL_IDX] = PK_Vector2(x, y + height);
    m_Vertices[UR_IDX] = PK_Vector2(x + width, y + height);
    m_Vertices[LR_IDX] = PK_Vector2(x + width, y);
}
    

// Testa se um ponto esta dentro da bs
// Ref: http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
bool PK_tBoundingSquare::ContainsPoint(const PK_Vector2 &vPoint)
{
    int i, j, c = 0;
    for (i = 0, j = 3; i < 4; j = i++)
    {
        if ( ((m_Vertices[i].y > vPoint.y) != (m_Vertices[j].y > vPoint.y)) &&
            (vPoint.x < (m_Vertices[j].x-m_Vertices[i].x) * (vPoint.y-m_Vertices[i].y) / (m_Vertices[j].y-m_Vertices[i].y) + m_Vertices[i].x) )
            c = !c;
    }
        
    return (c != 0);
}
    
//
void PK_tBoundingSquare::ToTextureCoords(const PK_tSize &size, PK_Vector2 retCoords[4]) const
{
    retCoords[LL_IDX] = PK_Vector2(m_Vertices[1].x / size.w, m_Vertices[1].y / size.h);
    retCoords[UL_IDX] = PK_Vector2(m_Vertices[0].x / size.w, m_Vertices[0].y / size.h);
    retCoords[UR_IDX] = PK_Vector2(m_Vertices[3].x / size.w, m_Vertices[3].y / size.h);
    retCoords[LR_IDX] = PK_Vector2(m_Vertices[2].x / size.w, m_Vertices[2].y / size.h);
    
}

} // namespace
