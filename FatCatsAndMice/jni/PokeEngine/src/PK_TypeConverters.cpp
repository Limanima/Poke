#include "PK_TypeConverters.h"
#include "PK_Exceptions.h"
#include "PK_Array.h"

namespace PK {

//
PK_ePivotAlignmentType PK_TypeConverters::StrToPivotAlignment(const PK_String &value)
{
    if (value == "Center")      { return PivotAlignment_Center; }
    if (value == "TopLeft")     { return PivotAlignment_TopLeft; }
    if (value == "Top")         { return PivotAlignment_Top; }
    if (value == "TopRight")    { return PivotAlignment_TopRight; }
    if (value == "Right")       { return PivotAlignment_Right; }
    if (value == "BottomRight") { return PivotAlignment_BottomRight; }
    if (value == "Bottom")      { return PivotAlignment_Bottom; }
    if (value == "BottomLeft")  { return PivotAlignment_BottomLeft; }
    if (value == "Left")        { return PivotAlignment_Left; }
    if (value == "None")        { return PivotAlignment_None; }

    throw PK_SystemException("Type conversion error. Could not convert string '%s' to PK_ePivotAlignmentType type.", __FILE__, __LINE__, value.c_str());
}

//
PK_eParentAlignmentFlags PK_TypeConverters::StrToParentAlignment(const PK_String &value)
{
  PK_Array<PK_String> fields;
  unsigned int flags = ParentAlignment_None;
  value.Split('|', fields);
  for(int i = 0; i < fields.GetCount(); i++)
  {
    if (fields[i] == "None")        { flags |= ParentAlignment_None; continue; }
    if (fields[i] == "Horizontaly") { flags |= ParentAlignment_Horizontaly; continue; }
    if (fields[i] == "Verticaly")   { flags |= ParentAlignment_Verticaly; continue; }
    if (fields[i] == "Left")        { flags |= ParentAlignment_Left; continue; }   
    if (fields[i] == "Top")         { flags |= ParentAlignment_Top; continue; }
    if (fields[i] == "Bottom")      { flags |= ParentAlignment_Bottom; continue; }
    if (fields[i] == "Right")       { flags |= ParentAlignment_Right; continue; }
    if (fields[i] == "Center")      { flags |= ParentAlignment_Center; continue; }

    throw PK_SystemException("Type conversion error. Could not convert string '%s' to PK_eParentAlignmentFlags type.", __FILE__, __LINE__, value.c_str());
  }
  return (PK_eParentAlignmentFlags)flags;
}

//
PK_eDockStyleFlags PK_TypeConverters::StrToControlDock(const PK_String &value)
{
  PK_Array<PK_String> fields;
  unsigned int flags = DockStyle_None;
  value.Split('|', fields);
  for(int i = 0; i < fields.GetCount(); i++)
  {
    if (fields[i] == "None")    { flags |= DockStyle_None; continue; }
    if (fields[i] == "Left")    { flags |= DockStyle_Left; continue; }
    if (fields[i] == "Top")     { flags |= DockStyle_Top; continue; }
    if (fields[i] == "Bottom")  { flags |= DockStyle_Bottom; continue; }
    if (fields[i] == "Right ")  { flags |= DockStyle_Right; continue; }
    if (fields[i] == "Fill")    { flags |= DockStyle_Fill; continue; }

    throw PK_SystemException("Type conversion error. Could not convert string '%s' to PK_eDockStyleFlags type.", __FILE__, __LINE__, value.c_str());
  }

  return (PK_eDockStyleFlags)flags;
}

//
PK_String PK_TypeConverters::DataFieldTypeToStr(PK_eDataFieldType fieldType)
{
	switch(fieldType)
    {
        case DataFieldType_Int:
            return "Int";
            
        case DataFieldType_Str:
            return "String";
            
        case DataFieldType_Size:
            return "Size";

        case DataFieldType_Bool:
            return "Bool";
            
        case DataFieldType_Color:
            return "Color";

        case DataFieldType_Vector3:
            return "Vector3";
            
        case DataFieldType_Vector2:
            return "Vector2";
            
        case DataFieldType_Rect:
            return "Rect";
            
        case DataFieldType_Float:
            return "Float";
            
        case DataFieldType_Resolution:
            return "Resolution";
            
        case DataFieldType_Enum:
            return "Enum";
            
        case DataFieldType_Undef:
            return "UNDEF";
    }

    return "UNK_TYPE";
}

// Formatos aceites:
// r, g, b      ->Alpha assume 255
// r, g, b, a 
//
// Valores de 0 a 255 convertidos para 0.0f a 1.0f
PK_Color PK_TypeConverters::StrToColor(const PK_String &str)
{
  PK_Array<PK_String> params;
  str.Split(',', params);
  if (params.GetCount() < 3)
  {
      throw PK_SystemException("Cannot convert string '%s' to PK_Color.", __FILE__, __LINE__, str.c_str());
  }
  for(int i = 0; i < params.GetCount(); i++)
  {
    int f = atoi(params[i].c_str());
    if (f < 0 || f > 255)
    {
      throw PK_SystemException("String '%s' does not contain a valid color value. Format expected: r, g, b, [a] with values between 0 and 255.", __FILE__, __LINE__, str.c_str());
    }
  }

  int r = atoi(params[0].c_str());
  int g = atoi(params[1].c_str());
  int b = atoi(params[2].c_str());
  int a = (params.GetCount() > 3? atoi(params[3].c_str()): 255);

  return PK_Color((float)(r / (float)255),
                  (float)(g / (float)255),
                  (float)(b / (float)255),
                  (float)(a / (float)255));
}

//
PK_Vector3 PK_TypeConverters::StrToVector3(const PK_String &str)
{
  PK_Array<PK_String> params;
  str.Split(',', params);
  if (params.GetCount() != 3)
  {
      throw PK_SystemException("Cannot convert string '%s' to PK_Vector3.", __FILE__, __LINE__, str.c_str());
  }

  return PK_Vector3(atof(params[0].c_str()), atof(params[1].c_str()), atof(params[2].c_str()));
}

//
PK_Vector2 PK_TypeConverters::StrToVector2(const PK_String &str)
{
  PK_Array<PK_String> params;
  str.Split(',', params);
  if (params.GetCount() != 2)
  {
      throw PK_SystemException("Cannot convert string '%s' to PK_Vector2.", __FILE__, __LINE__, str.c_str());
  }

  return PK_Vector2(atof(params[0].c_str()), atof(params[1].c_str()));
}

// static 
PK_eAppType PK_TypeConverters::StrToAppType(const PK_String &sVal)
{
    if (sVal.CompareTo("Console", true))
    {
        return AppType_Console;
    }
    if (sVal.CompareTo("Game", true))
    {
        return AppType_Game;
    }

    throw PK_SystemException("Type conversion error. Could not convert string '%d' to App Type. Expected 'Console' or 'Game'.",
            __FILE__, __LINE__, sVal.c_str());
}

template<>
PK_eDeviceOrientation PK_TypeConverters::StrToEnum<PK_eDeviceOrientation>(const PK_String &str)
{
    if (str=="Portait")
    {
        return DeviceOrientation_Portait;
    }
    if (str=="Landscape")
    {
        return DeviceOrientation_Landscape;
    }
    
    throw PK_SystemException("String '%s' cannot be converted to enum PK_eDeviceOrientation.", __FILE__, __LINE__, str.c_str());
}
    

//
PK_String PK_TypeConverters::PlatformTypeToStr(PK_ePlatformType platform)
{
  switch(platform)
  {
    case Platform_Windows:
      return "Windows";
    case Platform_MacOS:
      return "MacOS";
    case Platform_iOS:
      return "iOS";
    case Platform_Android:
      return "Android";
    case Platform_WindowsPhone:
      return "WP";
    default:
      throw PK_SystemException("Type conversion error. Could not convert platform '%d' to a string.", __FILE__, __LINE__, platform);
  }
}


//
PK_String PK_TypeConverters::AssetTypeToStr(PK_eAssetType assetType)
{
  switch(assetType)
  {
    case AssetType_Texture:
        return "Texture";
    case AssetType_SpriteSet:
        return "SpriteSet";
    case AssetType_Sprite:
        return "Sprite";
    case AssetType_SoundEffect:
        return "SoundEffect";
    case AssetType_Music:
        return "Music";
    case AssetType_Font:
        return "Font";
    case AssetType_ObjectProperties:
        return "ObjectProperties";
    case AssetType_Settings:
        return "Setting";
    case AssetType_Script:
        return "Script";
    case AssetType_File:
        return "File";
     case AssetType_String:
        return "String";
   default:
      throw PK_SystemException("Type conversion error. Could not convert asset type '%d' to a string.", __FILE__, __LINE__, assetType);
  }
}

//
PK_String PK_TypeConverters::BodyTypeToStr(PK_eBodyType assetType)
{
  switch(assetType)
  {
    case BodyType_Static:
        return "Static";
    case BodyType_Dynamic:
        return "Dynamic";
    case BodyType_UserControlable:
        return "UserControlable";
    default:
      throw PK_SystemException("Type conversion error. Could not convert BodyType '%d' to a string.", __FILE__, __LINE__, assetType);
  }
}

//
PK_String PK_TypeConverters::SceneControlRefreshFlagsToStr(PK_eSceneControlRefreshFlags flags)
{
  PK_String sFlags;
  if (flags & RefreshFlags_Alignment) { sFlags = "Alignment|"; }
  if (flags & RefreshFlags_Dock) { sFlags = "Dock|"; }
  if (flags & RefreshFlags_Position) { sFlags = "Position|"; }
  if (flags & RefreshFlags_WorldPosition) { sFlags = "WorldPosition|"; }
  if (flags & RefreshFlags_WorldRotation) { sFlags = "WorldRotation|"; }
  if (flags & RefreshFlags_WorldScale) { sFlags = "WorldScale|"; }
  if (flags & RefreshFlags_TransformMatrix) { sFlags = "TransformMatrix|"; }
  if (flags & RefreshFlags_ClientRect) { sFlags = "ClientRect|"; }
  if (flags & RefreshFlags_Pivot) { sFlags = "Pivot|"; }
  if (flags & RefreshFlags_BackgroundImage) { sFlags = "BackgroundImage|"; }
  if (flags & RefreshFlags_ChildDocks) { sFlags = "ChildDocks|"; }
  if (flags & RefreshFlags_BlendedColor) { sFlags = "BlendedColor|"; }
  if (flags & RefreshFlags_BackgroundImageRect) { sFlags = "BackgroundImageRect|"; }
  if (flags & RefreshFlags_PhysicsBody) { sFlags = "PhysicsBody|"; }
  if (flags & RefreshFlags_CliRectPrimitiveData) { sFlags = "CliRectPrimitiveData|"; }

  return sFlags;
}

//
PK_String PK_TypeConverters::TimestampToStr(PK_tTimestamp &timestamp)
{
    PK_String sTime;
    sTime.Format("%04d%02d %02d%02d%02d%02d%03d", 
        timestamp.year, timestamp.month, timestamp.day, 
        timestamp.hour, timestamp.minute, timestamp.second, 
        timestamp.hundreths);

    return sTime;
}

//static 
PK_String PK_TypeConverters::BoolToStr(bool bValue)
{
    return (bValue? "true": "false");
}

// static
PK_String PK_TypeConverters::BuildTypeToStr(PK_eBuildType buildType)
{
    switch(buildType)
    {
        case BuildType_Debug:
            return "Debug";

        case BuildType_Release:
            return "Release";

        default:
            throw PK_SystemException("Type conversion error. Could not convert BuildType '%d' to a string.", __FILE__, __LINE__, buildType);
    }
} 

//static 
bool PK_TypeConverters::StrToBool(const PK_String &sVal)  
{ 
    if (sVal == "true")
    {
        return true;
    }
    if (sVal == "false")
    {
        return false;
    }

    throw PK_SystemException("Type conversion error. Could not convert string '%d' to bool. Expected 'true' or 'false'.",
            __FILE__, __LINE__, sVal.c_str());
}

} // namespace