#ifndef _PK_PK_RANDOMGENERATOR_H_
#define _PK_PK_RANDOMGENERATOR_H_

#include "PK_Object.h"
#include "PK_Matrix4.h"

namespace PK {
    
class PK_RandomGenerator
{
protected:

public:
    static void Initialize();
    // Devolve um numero random entre 0 e max
    static int GetRandNumber(int max);
    
};
    
} // namespace

#endif
