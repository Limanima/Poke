#ifndef _PK_COLOR_H_
#define _PK_COLOR_H_

#include <glm/glm.hpp>

#define PK_Color glm::vec4

#define PK_COLOR_TRANSPARENT    PK_Color(0.0f, 0.0f, 0.0f, 0.0f)
#define PK_COLOR_BLACK          PK_Color(0.0f, 0.0f, 0.0f, 1.0f)
#define PK_COLOR_WHITE          PK_Color(1.0f, 1.0f, 1.0f, 1.0f)
#define PK_COLOR_RED            PK_Color(1.0f, 0.0f, 0.0f, 1.0f)
#define PK_COLOR_GREEN          PK_Color(0.0f, 1.0f, 0.0f, 1.0f)
#define PK_COLOR_BLUE           PK_Color(0.0f, 0.0f, 1.0f, 1.0f)
#define PK_COLOR_YELLOW         PK_Color(1.0f, 1.0f, 0.0f, 1.0f)
#define PK_COLOR_ORANGE         PK_Color(1.0f, 0.7f, 0.0f, 1.0f)
#define PK_COLOR_PINK           PK_Color(1.0f, 0.8f, 0.8f, 1.0f)
#define PK_COLOR_PURPLE         PK_Color(0.8f, 0.0f, 1.0f, 1.0f)
#define PK_COLOR_GRAY           PK_Color(0.5f, 0.5f, 0.5f, 1.0f)
#define PK_COLOR_LIGHT_GRAY     PK_Color(0.8f, 0.8f, 0.8f, 1.0f)
#define PK_COLOR_LIGHT_BLUE     PK_Color(0.4f, 0.4f, 1.8f, 1.0f)
#define PK_COLOR_DARK_TRANSP    PK_Color(0.2f, 0.2f, 0.2f, 0.8f)
#define PK_COLOR_BROWN          PK_Color(0.8f, 0.5f, 0.2f, 1.0f)

#define PK_COLOR_RGBA_INT(r,g,b,a) r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f

#endif
