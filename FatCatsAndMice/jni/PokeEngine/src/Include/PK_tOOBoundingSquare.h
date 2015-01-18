#ifndef _PK_tOOBOUNDINGSQUARE_H_
#define _PK_tOOBOUNDINGSQUARE_H_

#include "PK_Vector2.h"

namespace PK {

// Representa um rectangulo (axis oriented)
struct PK_tOOBoundingSquare
{
    PK_Vector2  vPosition;
    float w, h; // Manter tamanhos com float!
    
    PK_tOOBoundingSquare () 
    { 
        w = 0;
        h = 0;
    }

    PK_tOOBoundingSquare (PK_Vector2 vPosition, float iWidth, float iHeight)
    {
        vPosition = vPosition;
        w = iWidth;
        h = iHeight;
    }
    
    PK_tOOBoundingSquare (float x, float y, float iWidth, float iHeight)
    {
        vPosition = PK_Vector2(x, y);
        w = iWidth;
        h = iHeight;
    }
};

}

#endif