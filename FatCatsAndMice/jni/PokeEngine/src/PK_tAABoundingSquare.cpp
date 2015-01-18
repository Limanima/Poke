#include "PK_tAABoundingSquare.h"
#include "PK_Exceptions.h"
#include "PK_Array.h"

namespace PK
{

PK_tBoundingSquare PK_tAABoundingSquare::ToBoundingSquare()
{
    return PK_tBoundingSquare(vPosition.x, vPosition.y, size.w, size.h);
}

//
PK_tAABoundingSquare PK_tAABoundingSquare::Parse(const PK_String &str)
{
  PK_Array<PK_String> params;
  str.Split(',', params);
  if (params.GetCount() != 4)
  {
      throw PK_SystemException("Cannot convert string '%s' to PK_tAABoundingSquare. Expected format is 'x, y, width, height'.", __FILE__, __LINE__, str.c_str());
  }

  return PK_tAABoundingSquare(  (float)atof(params[0].c_str()), 
                                (float)atof(params[1].c_str()), 
                                (float)atof(params[2].c_str()), 
                                (float)atof(params[3].c_str()));
}
    
} // namespace
