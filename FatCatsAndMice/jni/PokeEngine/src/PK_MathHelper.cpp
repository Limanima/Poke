#include <glm/gtx/transform.hpp>
#include "PK_MathHelper.h"

namespace PK
{
  
// FIXME
// Nao devia ser preciso isto.
// Converter no SceneControl MAT3(GL) para MAT4 (DX)
void PK_MathHelper::FromM3ToM4(const PK_Matrix3 & mat3, PK_Matrix4 &retMat4)
{
	retMat4[0][0] = mat3[0][0];
	retMat4[0][1] = mat3[0][1];
	retMat4[0][2] = mat3[0][2];
	retMat4[0][3] = 0.0f;

	retMat4[1][0] = mat3[1][0];
	retMat4[1][1] = mat3[1][1];
	retMat4[1][2] = mat3[1][2];
	retMat4[1][3] = 0.0f;

	retMat4[2][0] = 0.0f;
	retMat4[2][1] = 0.0f;
	retMat4[2][2] = 1.0f;
	retMat4[0][3] = 0.0f;

	retMat4[3][0] = mat3[2][0];
	retMat4[3][1] = mat3[2][1];
	retMat4[3][2] = 0.0f;
	retMat4[3][3] = mat3[2][2];
}

//
PK_Matrix4 PK_MathHelper::ComputeTransformMatrix(const PK_Vector3 &vPosition, float fRotation, const PK_Vector3 &vScale)
{
    PK_Matrix4 matTransform;
    if (fRotation != 0)
    {
        matTransform = glm::translate(vPosition) * glm::rotate(fRotation, PK_Vector3(0.0f, 0.0f, 1.0f));
    }
    else
    {
        matTransform = glm::translate(vPosition);
    }
    
    matTransform *= glm::scale(vScale);
    
    return matTransform;
}

// Angulo entre 2 vectores
// Refa: http://stackoverflow.com/questions/13984154/different-methods-for-finding-angle-between-two-vectors
float PK_MathHelper::AngleBetweenVectors(const PK_Vector2 &v1, const PK_Vector2 &v2)
{
    // cross product
    double y = (v1.x * v2.y) - (v2.x * v1.y);

    // dot product
    double x = (v1.x * v2.x) + (v1.y * v2.y);

    return (float)atan2(y, x);
}

// Retidado daqui:
// http://stackoverflow.com/questions/11498169/dealing-with-angle-wrap-in-c-code
float PK_MathHelper::NormalizeAngle(float x)
{
    x = fmod(x + 180, 360);

    if (x < 0)
        x += 360;

    return x - 180;
}
} // namespace
