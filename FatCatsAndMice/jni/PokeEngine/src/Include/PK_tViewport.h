#ifndef __PK_TVIEWPORT_H__
#define __PK_TVIEWPORT_H__

#include "PK_String.h"

namespace PK {

struct PK_tViewport
{
    int left;
    int right;
    int top;
    int bottom;
      
    PK_tViewport() 
    {
      left = right = top = bottom = 0;
    }
    PK_tViewport(const PK_tViewport& viewport)
    {
        left = viewport.left;
		right = viewport.right;
        top = viewport.top;
        bottom = viewport.bottom;
    }
    
    PK_tViewport(int l, int t, int r, int b) 
    { 
        Set(l, t, r, b); 
    }

    inline void Set(int l, int t, int r, int b)
    { 
        left = l;
		right = r;
        top = t;
        bottom = b;
    }
   
    inline PK_tViewport & operator=(const PK_tViewport &viewport)
    {
        if(this == &viewport)
        {
            return *this;
        }
        left = viewport.left;
		    right = viewport.right;
        top = viewport.top;
        bottom = viewport.bottom;
        return *this;
    }
      
    inline bool operator!=(const PK_tViewport &viewport)
    {
        return (left != viewport.left || 
                right != viewport.right || 
                top != viewport.top || 
                bottom != viewport.bottom );
    }
    
    inline bool operator==(const PK_tViewport &viewport)
    {
        return (left == viewport.left && 
                right == viewport.right && 
                top == viewport.top && 
                bottom == viewport.bottom);
    }

    static PK_tViewport Parse(const PK_String &str);
};

} // Namespace
#endif
