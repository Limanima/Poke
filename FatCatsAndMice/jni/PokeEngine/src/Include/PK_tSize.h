#ifndef __PK_TSIZE_H__
#define __PK_TSIZE_H__

#include "PK_String.h"

namespace PK {

struct PK_tSize
{
    float w;
    float h;
    
	PK_tSize() 
	{
		w = 0;
		h = 0;
	}
    PK_tSize(const PK_tSize & size)
    {
        w = size.w;
		h = size.h;
    }
    
    PK_tSize(float fWidth, float fHeight) { Set(fWidth, fHeight); }
    inline void Set(float fWidth, float fHeight) { w = fWidth; h = fHeight; }
    inline void Set(int iWidth, int iHeight) { w = (float)iWidth; h = (float)iHeight; }
   
    inline PK_tSize & operator=(const PK_tSize &size)
    {
        if(this == &size)
        {
            return *this;
        }
        w = size.w;
        h = size.h;
        return *this;
    }
      
    inline bool operator!=(const PK_tSize &size)
    {
        return (w != size.w || h != size.h);
    }
    
    inline bool operator==(const PK_tSize &size)
    {
        return (w == size.w && h == size.h);
    }

    static PK_tSize Parse(const PK_String &str);
};

} // Namespace
#endif
