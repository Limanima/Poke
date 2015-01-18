#ifndef __PK_MATHHELPER_H__
#define __PK_MATHHELPER_H__

#include "PK_Matrix4.h"
#include "PK_Vector3.h"
#include "PK_Vector2.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define PK_MATH_90_RADIANS   M_PI_2
#define PK_MATH_180_RADIANS  M_PI
#define PK_MATH_270_RADIANS  3 * M_PI / 2
#define PK_MATH_PI           M_PI

namespace PK {

class PK_MathHelper
{
public:
	static void FromM3ToM4(const PK_Matrix3 & mat3, PK_Matrix4 &retMat4);
    static PK_Matrix4 ComputeTransformMatrix(const PK_Vector3 &vPosition, float fRotation, const PK_Vector3 &vScale);
    static float AngleBetweenVectors(const PK_Vector2 &v1, const PK_Vector2 &v2);
    inline static float RadiansToDegrees(float fRadians) { return (float)(fRadians * 180.0 / PK_MATH_PI);}
    inline static float DegreesToRadians(float fDegrees) { return (float)(fDegrees * PK_MATH_PI / 180.0);}
    inline static float NormalizeDegreesToPositives(float fDegrees)
    {
        return (fDegrees < 0 ? 360 + fDegrees : fDegrees);
    }
    static float NormalizeAngle(float fDegrees);
};
 

} // Namespace
#endif
