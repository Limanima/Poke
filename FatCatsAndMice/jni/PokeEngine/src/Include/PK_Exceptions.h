// Incluir esta source para utilizar excepcoes
#include "PK_Exception.h"
#include "PK_SystemException.h"
#include "PK_NullArgumentException.h"
#include "PK_OutOfMemoryException.h"
#include "PK_FileNotFoundException.h"
#include "PK_NotImplementedException.h"
#include "PK_DataFieldFormatException.h"
#include "PK_InvalidObjectException.h"
#include "PK_GameException.h"
#include "PK_ArgumentOutOfRangeException.h"
#include "PK_OverflowException.h"
#include "PK_SDLException.h"
#include "PK_GLESException.h"
#include "PK_JNIException.h"
#include "PK_InvalidAppArgumentsException.h"
  
// Macros
// Para utilizar a seguir a um new de um objecto
#define PK_CHECK_OBJECT_ALLOC(className, obj) \
if (obj == NULL) \
{ \
    throw PK_OutOfMemoryException(#className, sizeof(className), __FILE__, __LINE__); \
}

#define PK_PARAM_NOT_NULL(paramName)\
if (paramName == NULL) \
{ \
	throw PK_NullArgumentException(#paramName, __FILE__, __LINE__);\
}


#define PK_THROW_NOT_IMPLEMENTED(methodName)\
throw PK_NotImplementedException("PK_GLRenderManager::BeginRender", __FILE__, __LINE__);
