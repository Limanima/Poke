#include "PK_tBoundingCircle.h"

namespace PK
{

//  
PK_tBoundingCircle::PK_tBoundingCircle()
{
  Set(PK_Vector2(.0f, .0f), .0f);
}
 
//
PK_tBoundingCircle::PK_tBoundingCircle(const PK_Vector2 &vCenter, float fRadius)
{
  Set(vCenter, fRadius);
}

//
PK_tBoundingCircle::PK_tBoundingCircle(float x, float y, float fRadius)
{
  Set(PK_Vector2(x, y), fRadius);
}

//
void PK_tBoundingCircle::Set(const PK_Vector2 &vCenter, float fRadius)
{
  m_vCenter = vCenter;
  m_fRadius = fRadius;
}

} // namespace
