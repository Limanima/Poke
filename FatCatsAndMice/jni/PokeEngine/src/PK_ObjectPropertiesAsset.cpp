#include "PK_ObjectPropertiesAsset.h"
#include "PK_Globals.h"
#include "PK_Path.h"

namespace PK {
//----------------------------------------------------------------------------
PK_ObjectPropertiesAsset::PK_ObjectPropertiesAsset(PK_AssetContainer &assetContainer) :
	PK_DataFileAsset(AssetType_ObjectProperties, assetContainer, PK_OBJECT_PROPS_EXTENSION)
{
	SetTypeName("PK_ObjectPropertiesAsset");
}

//----------------------------------------------------------------------------
PK_ObjectPropertiesAsset::PK_ObjectPropertiesAsset(PK_AssetContainer &assetContainer, const PK_String &sExtension) :
	PK_DataFileAsset(AssetType_ObjectProperties, assetContainer, sExtension)
{
	SetTypeName("PK_ObjectPropertiesAsset");
}
//----------------------------------------------------------------------------
int PK_ObjectPropertiesAsset::GetProperty_Int(const PK_String &sPropertyName)
{
    PK_DataFileField * pField = GetRootRecord()->GetConditionalChildRecordField(sPropertyName, PROPERTY_NAME);
    return pField->GetValue_Int();
}
//----------------------------------------------------------------------------
bool PK_ObjectPropertiesAsset::GetProperty_Bool(const PK_String &sPropertyName)
{
    PK_DataFileField * pField = GetRootRecord()->GetConditionalChildRecordField(sPropertyName, PROPERTY_NAME);
    return pField->GetValue_Bool();
}
//----------------------------------------------------------------------------
float PK_ObjectPropertiesAsset::GetProperty_Float(const PK_String &sPropertyName)
{
    PK_DataFileField * pField = GetRootRecord()->GetConditionalChildRecordField(sPropertyName, PROPERTY_NAME);
    return pField->GetValue_Float();
}
//----------------------------------------------------------------------------
PK_String PK_ObjectPropertiesAsset::GetProperty_String(const PK_String &sPropertyName)
{
    PK_DataFileField * pField = GetRootRecord()->GetConditionalChildRecordField(sPropertyName, PROPERTY_NAME);
    return pField->GetValue_String();
}
//----------------------------------------------------------------------------
PK_Color PK_ObjectPropertiesAsset::GetProperty_Color(const PK_String &sPropertyName)
{
    PK_DataFileField * pField = GetRootRecord()->GetConditionalChildRecordField(sPropertyName, PROPERTY_NAME);
    return pField->GetValue_Color();
}
//----------------------------------------------------------------------------
PK_Vector3 PK_ObjectPropertiesAsset::GetProperty_Vector3(const PK_String &sPropertyName)
{
    PK_DataFileField * pField = GetRootRecord()->GetConditionalChildRecordField(sPropertyName, PROPERTY_NAME);
    return pField->GetValue_Vector3();
}
//----------------------------------------------------------------------------
PK_Vector2 PK_ObjectPropertiesAsset::GetProperty_Vector2(const PK_String &sPropertyName)
{
    PK_DataFileField * pField = GetRootRecord()->GetConditionalChildRecordField(sPropertyName, PROPERTY_NAME);
    return pField->GetValue_Vector2();
}
//----------------------------------------------------------------------------
PK_tSize PK_ObjectPropertiesAsset::GetProperty_Size(const PK_String &sPropertyName)
{
    PK_DataFileField * pField = GetRootRecord()->GetConditionalChildRecordField(sPropertyName, PROPERTY_NAME);
    return pField->GetValue_Size();
}
//----------------------------------------------------------------------------
PK_tAABoundingSquare PK_ObjectPropertiesAsset::GetProperty_AABoundingSquare(const PK_String &sPropertyName)
{
    PK_DataFileField * pField = GetRootRecord()->GetConditionalChildRecordField(sPropertyName, PROPERTY_NAME);
    return pField->GetValue_AABoundingSquare();
}
//----------------------------------------------------------------------------
PK_tResolution PK_ObjectPropertiesAsset::GetProperty_Resolution(const PK_String &sPropertyName)
{
    PK_DataFileField * pField = GetRootRecord()->GetConditionalChildRecordField(sPropertyName, PROPERTY_NAME);
    return pField->GetValue_Resolution();
}
} // namespace
