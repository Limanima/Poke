#ifndef _PK_MATRIX4_H_
#define _PK_MATRIX4_H_

#include <glm/glm.hpp>

#define PK_Matrix4 glm::mat4
#define PK_Matrix3 glm::mat3
#define PK_Matrix2 glm::mat2

namespace glm
{
 	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> translate
	(
		detail::tmat3x3<T> const & m,
		detail::tvec2<T> const & v
	)
	{
		detail::tmat3x3<T> Result(m);
		Result[2] = m[0] * v[0] + m[1] * v[1] + m[2];
		return Result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> translate(detail::tvec2<T> const & v )
	{
		return translate(detail::tmat3x3<T>(1.0f), v);
	}

    template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> rotate
	(
		T const & angle)
	{
#ifdef GLM_FORCE_RADIANS
		T a = angle;
#else
		T a = radians(angle);		
#endif
		T c = cos(a);
		T s = sin(a);

		detail::tmat3x3<T> Rotate(detail::tmat3x3<T>::null);
		Rotate[0][0] = c;
		Rotate[0][1] = -s;
        Rotate[0][2] = 0;
        
		Rotate[1][0] = s;
		Rotate[1][1] = c;
		Rotate[1][2] = 0;

		Rotate[2][0] = 0;
		Rotate[2][1] = 0;
		Rotate[2][2] = 1;

		return Rotate;
	}
    
    template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> scale(detail::tmat3x3<T> const & m, detail::tvec2<T> const & v)
	{
		detail::tmat3x3<T> Result(detail::tmat3x3<T>::null);
		Result[0] = m[0] * v[0];
		Result[1] = m[1] * v[1];
		Result[2] = m[2];
		return Result;
	}
    
    template <typename T>
    GLM_FUNC_QUALIFIER detail::tmat3x3<T> scale(detail::tvec2<T> const & v)
    {
        return scale(detail::tmat3x3<T>(1.0f), v);
    }
    
}
#endif
