#ifndef _PK_LOADABLEOBJECT_H_
#define _PK_LOADABLEOBJECT_H_

#include "PK_Object.h"

namespace PK {
    
class PK_LoadableObject : public PK_Object
{
public:
    PK_LoadableObject();
    PK_LoadableObject(const PK_String &sName);
    virtual void Load() = 0;
    
};
    
} // namespace

#endif
