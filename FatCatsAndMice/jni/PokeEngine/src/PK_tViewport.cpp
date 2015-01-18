#include "PK_tViewport.h"
#include "PK_Exceptions.h"

namespace PK
{

//
PK_tViewport PK_tViewport::Parse(const PK_String &str)
{
  PK_Array<PK_String> params;
  str.Split(',', params);
  if (params.GetCount() != 4)
  {
      throw PK_SystemException("Cannot convert string '%s' to PK_tViewport. Expected format is 'left, top, right, bottom'.", __FILE__, __LINE__, str.c_str());
  }
  return PK_tViewport((int)atoi(params[0].c_str()), (int)atoi(params[1].c_str()), (int)atoi(params[2].c_str()), (int)atoi(params[3].c_str()));
}
    
} // namespace
