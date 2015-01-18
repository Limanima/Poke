#ifndef _PK_TYPECONVERTERS_H_
#define _PK_TYPECONVERTERS_H_

#include "PK_String.h"
#include "PK_Types.h"
#include "PK_tSize.h"
#include "PK_Color.h"
#include "PK_Vector3.h"
#include "PK_Exceptions.h"

namespace PK {

class PK_TypeConverters
{
public:
  static PK_eParentAlignmentFlags StrToParentAlignment(const PK_String &value);
  static PK_ePivotAlignmentType StrToPivotAlignment(const PK_String &value);
  static PK_eDockStyleFlags StrToControlDock(const PK_String &value);
  static PK_tSize StrToSize(const PK_String &string);
  static PK_String DataFieldTypeToStr(PK_eDataFieldType fieldTypeStr);
  static PK_Color StrToColor(const PK_String &string);
  static PK_Vector3 StrToVector3(const PK_String &string);
  static PK_Vector2 StrToVector2(const PK_String &string);
  static PK_eAppType StrToAppType(const PK_String &string);

  static PK_String PlatformTypeToStr(PK_ePlatformType platform);
  static PK_String AssetTypeToStr(PK_eAssetType assetType);
  static PK_String BodyTypeToStr(PK_eBodyType assetType);
  static PK_String SceneControlRefreshFlagsToStr(PK_eSceneControlRefreshFlags flags);
  static PK_String TimestampToStr(PK_tTimestamp &timestamp);
  static PK_String BoolToStr(bool bValue);
  static PK_String BuildTypeToStr(PK_eBuildType buildType);
  

  static inline float StrToFloat(const PK_String &sVal)  { return (float)atof(sVal.c_str()); }
  static inline int StrToInt(const PK_String &sVal)  { return atoi(sVal.c_str()); }
  static bool StrToBool(const PK_String &sVal);

  template<typename T> 
  static T StrToEnum(const PK_String &str)
  {
     throw PK_SystemException("Enum cannot be converted from the string '%s' because PK_TypeConverters::StrToEnum() does not support the type.", __FILE__, __LINE__, str.c_str());
  }
 
};

}
#endif
