#ifndef _PK_BOUNDINGCIRCLE_H_
#define _PK_BOUNDINGCIRCLE_H_

#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "PK_Consts.h"
#include "PK_tBoundingCircle.h"
#include "PK_tSize.h"
#include "PK_Matrix4.h"
#include "PK_Vector2.h"

namespace PK {

// Representa um rectangulo (axis oriented)
struct PK_tBoundingCircle
{
public:
    PK_Vector2 m_vCenter;
    float      m_fRadius;

public:
    PK_tBoundingCircle ();
    PK_tBoundingCircle (const PK_Vector2 &vCenter, float fRadius);
    PK_tBoundingCircle (float x, float y, float fRadius);

    void Set(const PK_Vector2 &vCenter, float fRadius);
};

}

#endif