#include "PK_tSize.h"
#include "PK_Exceptions.h"

namespace PK
{

//
PK_tSize PK_tSize::Parse(const PK_String &str)
{
  PK_Array<PK_String> params;
  str.Split(',', params);
  if (params.GetCount() != 2)
  {
      throw PK_SystemException("Cannot convert string '%s' to PK_tSize. Expected format is 'width, height'.", __FILE__, __LINE__, str.c_str());
  }
  return PK_tSize((float)atoi(params[0].c_str()), (float)atoi(params[1].c_str()));
}
    
} // namespace
