#ifndef _PK_OBJECTPROPERTIESASSET_H_
#define _PK_OBJECTPROPERTIESASSET_H_

#include "PK_DataFileAsset.h"
#include "PK_DataFiles.h"
#include "PK_Assert.h"

namespace PK {
   
#define PROPERTY_NAME "value"
// 
class PK_ObjectPropertiesAsset : public PK_DataFileAsset
{
private:
    
public:
	PK_ObjectPropertiesAsset(PK_AssetContainer &assetContainer);
	PK_ObjectPropertiesAsset(PK_AssetContainer &assetContainer, const PK_String &sExtension);

public:
    int GetProperty_Int(const PK_String &sPropertyName);
    bool GetProperty_Bool(const PK_String &sPropertyName);
    float GetProperty_Float(const PK_String &sPropertyName);
    PK_String GetProperty_String(const PK_String &sPropertyName);
    PK_Color GetProperty_Color(const PK_String &sPropertyName);
    PK_Vector3 GetProperty_Vector3(const PK_String &sPropertyName);
    PK_Vector2 GetProperty_Vector2(const PK_String &sPropertyName);
    PK_tSize GetProperty_Size(const PK_String &sPropertyName);
    PK_tAABoundingSquare GetProperty_AABoundingSquare(const PK_String &sPropertyName);
    PK_tResolution GetProperty_Resolution(const PK_String &sPropertyName);

    template<typename T> T GetEnumProperty(const PK_String sPropertyName)
    {
        return GetRootRecord()->GetChildRecordFieldEnumValue<T>(sPropertyName, "value");
        
    }
};

} // namespace

#endif
