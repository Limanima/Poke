#include "PK_RandomGenerator.h"
#include <time.h>

namespace PK {

//
void PK_RandomGenerator::Initialize()
{
    srand((unsigned int)time(NULL));
}

// 
int PK_RandomGenerator::GetRandNumber(int max)
{
    return (int)(rand() % max);
}
    

} // namespace
