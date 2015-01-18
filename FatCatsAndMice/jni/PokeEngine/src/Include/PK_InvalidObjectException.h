#ifndef _PK_INVALIDOBJECTEXCEPTION_
#define _PK_INVALIDOBJECTEXCEPTION_

#include "PK_Exception.h"
#include "PK_Object.h"

namespace PK {
// Esta excepcao e lancado quando e passado ao PokeEngine um PK_Object que nao seja global
// Um objecto local, e um objecto definido dentro de uma funcao da seguinte forma:
//
// void Func()
// {
//    ObjA obj; -->Objecto local, se for passado ao poke engine num método pode dar problemas porque o poke engine pode agarrar a
//                 referencia de um objecto que fica out of scope a saida da funcao
//
//    ObjA *pObj = PK_Object::CreateInstance<ObjA();->Ok, porque o objecto é criado na global heap, portanto pode ser passado ao poke engine
// }
class PK_InvalidObjectException : public PK_Exception
{
	public:
		PK_InvalidObjectException(const PK_Object &pObject, const char * pszSourceFile, int iLineNumber);
};

}
#endif
