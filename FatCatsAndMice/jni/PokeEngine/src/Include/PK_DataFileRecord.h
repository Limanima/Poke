#ifndef _PK_DATAFILERECORD_H_
#define _PK_DATAFILERECORD_H_

#include "PK_Consts.h"
#include "PK_Object.h"
#include "PK_List.h"
#include "PK_String.h"
#include "tinyxml2.h"
#include "PK_tAABoundingSquare.h"
#include "PK_Color.h"
#include "PK_DataFileField.h"
#include "PK_Exceptions.h"

namespace PK {


// DataFileRecord()
// Representa um registo num DataFile
// Um registo pode ter registos filhos e pode conter DataFileFields
class PK_DataFileRecord : public PK_Object
{
private:
	PK_List<PK_DataFileField *>	  m_fields;
	PK_List<PK_DataFileRecord *>  m_records;

public:
    PK_DataFileRecord();
	PK_DataFileRecord(const PK_String &sName);
    ~PK_DataFileRecord();
    void Init(const PK_String &sName);
    void FreeResources();
    void InitializeFromXML(tinyxml2::XMLElement * pElem);
	
    void CreatePath(const PK_String &sPath);
    // Fields
    PK_DataFileField * AddField(const PK_String &sName, const int value);
    PK_DataFileField * AddField(const PK_String &sName, const PK_String &sValue);
	PK_DataFileField * AddField(const PK_String &sName, bool value);
    void AddField(PK_DataFileField &field);

    // Records
	PK_DataFileRecord * AddRecord(const PK_String &sName);
	void AddRecord(PK_DataFileRecord &record);

	PK_DataFileRecord * SelectRecord(const PK_String &sName);
	PK_DataFileRecord * SelectRecordWithFieldValue(const PK_String &sRecordName, const PK_String &sFieldName, const PK_String &sFieldValue);
	void SelectRecords(const PK_String &sName, PK_List<PK_DataFileRecord *> &retList, bool bGrabReferences);
	
	PK_List<PK_DataFileField *> * GetFields() { return &m_fields; }
	PK_List<PK_DataFileRecord *> * GetRecords() { return &m_records; }
    
  PK_DataFileRecord * GetChildRecord(const PK_String &sRecordName);
  PK_DataFileRecord * GetChildRecord(const PK_String &sRecordName, bool bThrowsException);
  
  PK_DataFileField * GetField(const PK_String &sFieldName);
  PK_DataFileField * GetField(const PK_String &sFieldName, bool bThrowsException);
  PK_DataFileField * GetConditionalField(const PK_String &sFieldName);
  PK_DataFileField * GetConditionalChildRecordField(const PK_String &sRecordName, const PK_String &sFieldName, bool bMandatory = false);
  
  // Field geters
  int GetFieldValue_Int(const PK_String &sFieldName);
  bool GetFieldValue_Bool(const PK_String &sFieldName);
  float GetFieldValue_Float(const PK_String &sFieldName);
  PK_String GetFieldValue_String(const PK_String &sFieldName);
  PK_Color GetFieldValue_Color(const PK_String &sFieldName);
  PK_Vector3 GetFieldValue_Vector3(const PK_String &sFieldName);
  PK_Vector2 GetFieldValue_Vector2(const PK_String &sFieldName);
  PK_tSize GetFieldValue_Size(const PK_String &sFieldName);
  PK_tAABoundingSquare GetFieldValue_AABoundingSquare(const PK_String &sFieldName);
  PK_tResolution GetFieldValue_Resolution(const PK_String &sFieldName);

  // Field geters com valor default, nao seria necessario o _XXXXX porque como tem parametro de entrada
  // dava com overloading do metodo, mas mantemos o _XXXXX para ficar igual aos outros metodos
  int GetFieldValue_Int(const PK_String &sFieldName, const int defaultValue);
  bool GetFieldValue_Bool(const PK_String &sFieldName, const bool defaultValue);
  float GetFieldValue_Float(const PK_String &sFieldName, const float defaultValue);
  PK_String GetFieldValue_String(const PK_String &sFieldName, const PK_String &defaultValue);
  PK_Color GetFieldValue_Color(const PK_String &sFieldName, const PK_Color &defaultValue);
  PK_Vector3 GetFieldValue_Vector3(const PK_String &sFieldName, const PK_Vector3 &defaultValue);
  PK_Vector2 GetFieldValue_Vector2(const PK_String &sFieldName, const PK_Vector2 &defaultValue);
  PK_tSize GetFieldValue_Size(const PK_String &sFieldName, const PK_tSize &defaultValue);
  PK_tAABoundingSquare GetFieldValue_AABoundingSquare(const PK_String &sFieldName, const PK_tAABoundingSquare &defaultValue);
  PK_tResolution GetFieldValue_Resolution(const PK_String &sFieldName, const PK_tResolution &defaultValue);


  // Field geters para um record child
  int GetChildRecordFieldValue_Int(const PK_String &sChildRecordName, const PK_String &sFieldName);
  bool GetChildRecordFieldValue_Bool(const PK_String &sChildRecordName, const PK_String &sFieldName);
  float GetChildRecordFieldValue_Float(const PK_String &sChildRecordName, const PK_String &sFieldName);
  PK_String GetChildRecordFieldValue_String(const PK_String &sChildRecordName, const PK_String &sFieldName);
  PK_Color GetChildRecordFieldValue_Color(const PK_String &sChildRecordName, const PK_String &sFieldName);
  PK_Vector3 GetChildRecordFieldValue_Vector3(const PK_String &sChildRecordName, const PK_String &sFieldName);
  PK_Vector2 GetChildRecordFieldValue_Vector2(const PK_String &sChildRecordName, const PK_String &sFieldName);
  PK_tSize GetChildRecordFieldValue_Size(const PK_String &sChildRecordName, const PK_String &sFieldName);
  PK_tAABoundingSquare GetChildRecordFieldValue_AABoundingSquare(const PK_String &sChildRecordName, const PK_String &sFieldName);
  PK_tResolution GetChildRecordFieldValue_Resolution(const PK_String &sChildRecordName, const PK_String &sFieldName);

  // Field geters para um record child com valor default
  int GetChildRecordFieldValue_Int(const PK_String &sChildRecordName, const PK_String &sFieldName, const int &defaultValue);
  bool GetChildRecordFieldValue_Bool(const PK_String &sChildRecordName, const PK_String &sFieldName, const bool &defaultValue);
  float GetChildRecordFieldValue_Float(const PK_String &sChildRecordName, const PK_String &sFieldName, const float &defaultValue);
  PK_String GetChildRecordFieldValue_String(const PK_String &sChildRecordName, const PK_String &sFieldName, const PK_String &defaultValue);
  PK_Color GetChildRecordFieldValue_Color(const PK_String &sChildRecordName, const PK_String &sFieldName, const PK_Color &defaultValue);
  PK_Vector3 GetChildRecordFieldValue_Vector3(const PK_String &sChildRecordName, const PK_String &sFieldName, const PK_Vector3 &defaultValue);
  PK_Vector2 GetChildRecordFieldValue_Vector2(const PK_String &sChildRecordName, const PK_String &sFieldName, const PK_Vector2 &defaultValue);
  PK_tSize GetChildRecordFieldValue_Size(const PK_String &sChildRecordName, const PK_String &sFieldName, const PK_tSize &defaultValue);
  PK_tAABoundingSquare GetChildRecordFieldValue_AABoundingSquare(const PK_String &sChildRecordName, const PK_String &sFieldName, const PK_tAABoundingSquare &defaultValue);
  PK_tResolution GetChildRecordFieldValue_Resolution(const PK_String &sChildRecordName, const PK_String &sFieldName, const PK_tResolution &defaultValue);
    template<typename T> T GetChildRecordFieldEnumValue(const PK_String &sChildRecordName, const PK_String &sFieldName)
    {
        PK_DataFileField *pField = GetField(sFieldName);
        if (pField == NULL)
        {
            throw PK_SystemException("Field with name %s not found in DataFileRecord named %s.", __FILE__, __LINE__, sFieldName.c_str(), GetName().c_str());
        }
        
        return pField->GetEnumValue<T>();
    }
     
   
    // Field seters
    void SetFieldValue_Str(const PK_String &sFieldName, const PK_String & sValue);
    void SetFieldValue_Int(const PK_String &sFieldName, int iValue);

  
  static PK_DataFileRecord * CreateFromXML(tinyxml2::XMLElement * pElem);
  static bool EvaluateCondition(const PK_String &sCondition);
  static char * GetValue(char * strCode, int *iLen, char ** strRet);
  static int GetVariable(char * strCode, char ** strRet);

};

}
#endif
