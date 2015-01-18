#ifndef _PK_AABOUNDINGSQUARE_H_
#define _PK_AABOUNDINGSQUARE_H_

#include "PK_tSize.h"
#include "PK_Vector2.h"
#include "PK_String.h"

namespace PK {

struct PK_tBoundingSquare;

// Representa um rectangulo (axis oriented)
struct PK_tAABoundingSquare
{
    
public:
    PK_Vector2 vPosition;
    PK_tSize   size;

public:
    PK_tAABoundingSquare () 
    {
        vPosition = PK_Vector2(0,0);
        size.Set(0, 0);
    }

    PK_tAABoundingSquare (const PK_tAABoundingSquare &bs)
    {
        vPosition = bs.vPosition;
        size = bs.size;
    }
    
    //
    PK_tAABoundingSquare (const PK_Vector2 &vPos, const PK_tSize & s)
    {
        vPosition = vPos;
        size = s;
    }

    //
    PK_tAABoundingSquare (float x, float y, const PK_tSize & s)
    {
        vPosition = PK_Vector2(x, y);
        size = s;
    }

    //
    PK_tAABoundingSquare (float x, float y, float fWidth, float fHeight)
    {
        Set(x, y, fWidth, fHeight);
    }

    //
    PK_tAABoundingSquare (int x, int y, int fWidth, int fHeight)
    {
        Set(x, y, fWidth, fHeight);
    }

    inline void Set(int x, int y, int fWidth, int fHeight)
    {
        vPosition = PK_Vector2(x, y);
        size.Set(fWidth, fHeight);    
    }

    inline void Set(float x, float y, float fWidth, float fHeight)
    {
        vPosition = PK_Vector2(x, y);
        size.Set(fWidth, fHeight);    
    }

    inline void Translate(const PK_Vector2 &pos)
    {
        vPosition += pos;
    }

    PK_tBoundingSquare ToBoundingSquare();
    inline PK_Vector2 GetUL() { return vPosition; }
    inline PK_Vector2 GetUR() { return PK_Vector2(vPosition.x + size.w, vPosition.y); }
    inline PK_Vector2 GetLL() { return PK_Vector2(vPosition.x, vPosition.y + size.h); }
    inline PK_Vector2 GetLR() { return PK_Vector2(vPosition.x + size.w, vPosition.y + size.h); }
    inline PK_Vector2 GetCenter() { return PK_Vector2(vPosition.x + size.w / 2, vPosition.y + size.h / 2); } 
    //
    static PK_tAABoundingSquare Parse(const PK_String &str);
   
};

}

#endif