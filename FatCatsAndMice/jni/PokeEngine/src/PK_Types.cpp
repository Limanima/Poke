#include "PK_Types.h"
#include "PK_Exceptions.h"

namespace PK
{

//
PK_tResolution PK_tResolution::Parse(const PK_String &str)
{
  PK_Array<PK_String> params;
  str.Split(',', params);
  if (params.GetCount() != 2)
  {
      throw PK_SystemException("Cannot convert string '%s' to PK_tResolution. Expected format is 'width, height'.", __FILE__, __LINE__, str.c_str());
  }
  return PK_tResolution(atoi(params[0].c_str()), atoi(params[1].c_str()));
}
    
} // namespace
