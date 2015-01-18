#include <assert.h>
#include "PK_Object.h"
#include "PK_Profiler.h"
#include "PK_DataFileRecord.h"
#include "PK_Exceptions.h"
#include "PK_Log.h"

namespace PK {
    
//
PK_Object::PK_Object()
{
   m_iRefCount = 0;
   m_iTag = 0;
   PK_PROFILER_OBJ_CREATED
}

//
PK_Object::PK_Object(const PK_String &sName)
{
   m_iRefCount = 0;
   SetName(sName);
   PK_PROFILER_OBJ_CREATED
}

//
PK_Object::~PK_Object()
{
    PK_PROFILER_OBJ_DESTROYED
}

//
void PK_Object::InitFromDataFileRecord(PK_DataFileRecord &record)
{
    SetName(record.GetFieldValue_String("name"));
    SetTypeName(record.GetFieldValue_String("type"));
}

} // namespace
