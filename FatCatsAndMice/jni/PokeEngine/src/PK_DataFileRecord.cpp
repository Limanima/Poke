#include "PK_DataFileRecord.h"
#include "PK_DataFileField.h"
#include "PK_List.h"
#include "PK_Exceptions.h"
#include "tinyxml2.h"
#include "PK_Globals.h"
#include "PK_Environment.h"

#define VARIABLE_NAME_PLATFORM   "platform"
#define VARIABLE_NAME_RESOLUTION "resolution"

#define VARIABLE_CODE_UNK        0
#define VARIABLE_CODE_PLATFORM   1
#define VARIABLE_CODE_BUILD      3

#define OPER_OR  0
#define OPER_AND 1

#define STATE_VARIABLE   0  // Nome da variavel a comparar 
#define STATE_COMPARER   1  // Comparacao =, !=
#define STATE_VALUE      2  // Valor a comparar
#define STATE_OPERATION  3  // Operacao &, |

namespace PK {
    
PK_DataFileRecord::PK_DataFileRecord()
{
    Init("");
}
    
PK_DataFileRecord::PK_DataFileRecord(const PK_String &sName)
{
    Init(sName);
}
    
PK_DataFileRecord::~PK_DataFileRecord()
{
    FreeResources();
}
    
void PK_DataFileRecord::Init(const PK_String &sName)
{
	SetTypeName("PK_DataFileRecord");
	SetName(sName);

}
    
// Liberta todos fields e records
void PK_DataFileRecord::FreeResources()
{
	// Release de todos os campos
  	for(PK_ListIterator(PK_DataFileField *) itor = m_fields.Begin(); itor != m_fields.End(); itor++)
    {
		  (*itor)->Release();
    }
    m_fields.Clear();

    
	// Release de todos os records
	for(PK_ListIterator(PK_DataFileRecord *) itor = m_records.Begin(); itor != m_records.End(); itor++)
	{
		(*itor)->Release();
	}
    m_records.Clear();
}
    
//
void PK_DataFileRecord::CreatePath(const PK_String &sPath)
{
    PK_String path = sPath;
	PK_String recordName = path.ExtractWord(PK_DataFile::GetPathDelimiter().c_str());
    if (recordName.length() == 0)
    {
        return;
    }
    
    PK_DataFileRecord *pRecord = SelectRecord(recordName);
    if (pRecord == NULL)
    {
        pRecord = AddRecord(recordName);
    }
    pRecord->CreatePath(path);
}
    
// Cria um novo campo e adiciona ao registo
PK_DataFileField * PK_DataFileRecord::AddField(const PK_String &sName, const int value)
{

	PK_DataFileField * pField = new PK_DataFileField(sName);
	if (pField == NULL)
	{
		throw PK_OutOfMemoryException("PK_DataFileField", sizeof(PK_DataFileField), __FILE__, __LINE__);
	}
	pField->SetValue_Int(value);
	AddField(*pField);
    return pField;
}
    
// Cria um novo campo e adiciona ao registo
PK_DataFileField * PK_DataFileRecord::AddField(const PK_String &sName, bool value)
{
        
    PK_DataFileField * pField = new PK_DataFileField(sName);
    if (pField == NULL)
    {
            throw PK_OutOfMemoryException("PK_DataFileField", sizeof(PK_DataFileField), __FILE__, __LINE__);
    }
    pField->SetValue_Bool(value);
    AddField(*pField);
    return pField;
}
    
// Cria um novo campo e adiciona ao registo
PK_DataFileField * PK_DataFileRecord::AddField(const PK_String &sName, const PK_String &sValue)
{

    PK_DataFileField * pField = new PK_DataFileField(sName);
    if (pField == NULL)
    {
        throw PK_OutOfMemoryException("PK_DataFileField", sizeof(PK_DataFileField), __FILE__, __LINE__);
    }
    pField->SetValue_Str(sValue);
    AddField(*pField);
    return pField;
}
    
// Adiciona um campo ao registo
void PK_DataFileRecord::AddField(PK_DataFileField &field)
{
	m_fields.Add(&field);
	field.Grab();
}

// Cria um novo registo e adicionao ao registo
PK_DataFileRecord * PK_DataFileRecord::AddRecord(const PK_String &sName)
{
	PK_DataFileRecord * pRecord = new PK_DataFileRecord(sName);
	if (pRecord == NULL)
	{
		throw PK_OutOfMemoryException("PK_DataFileRecord", sizeof(PK_DataFileRecord), __FILE__, __LINE__);
	}
	AddRecord(*pRecord);
    return pRecord;
}

// Adiciona um registo ao registo
void PK_DataFileRecord::AddRecord(PK_DataFileRecord &record)
{
	m_records.Add(&record);
	record.Grab();
}

// Seleciona o registo por nome. Aceita paths no formato nome1\nome2\nome3
PK_DataFileRecord * PK_DataFileRecord::SelectRecord(const PK_String &sName)
{
	PK_String path = sName;
	PK_String recordName = path.ExtractWord(PK_DataFile::GetPathDelimiter().c_str());
	if (recordName.length() == 0)
	{
		return NULL;
	}
	if (path.length() != 0)
	{
		PK_DataFileRecord *pChild = GetChildRecord(recordName);
        if (pChild == NULL)
        {
            return NULL;
        }
        return pChild->SelectRecord(path);
	}
	
	return GetChildRecord(recordName);
}

// Seleciona um registo filho que contenha o campo com o nome sFieldName e valor sFieldValue (para ja so suporta valores do tipo string)
// Aceita paths no sRecordName
PK_DataFileRecord * PK_DataFileRecord::SelectRecordWithFieldValue(const PK_String &sRecordName, const PK_String &sFieldName, const PK_String &sFieldValue)
{
  PK_List<PK_DataFileRecord *> recList;
  SelectRecords(sRecordName, recList, false);
  for(PK_ListIterator(PK_DataFileRecord *) itor = recList.Begin(); itor != recList.End(); itor++)
  {
    PK_DataFileField * pField = (*itor)->GetField(sFieldName);
    if (pField != NULL)
    {
      if (pField->GetValue_String() == sFieldValue)
      {
        return (*itor);
      }
    }
  }

  return NULL;
}

// Seleciona todos os registos filhos com o nome sName. O resultado é colocado em retList
void PK_DataFileRecord::SelectRecords(const PK_String &sName, PK_List<PK_DataFileRecord *> &retList, bool bGrabReferences)
{
	retList.Clear();
	
    PK_String sNameAux = sName;
	PK_String sToFind = sNameAux.ExtractLastWord(PK_DataFile::GetPathDelimiter());
    
    PK_DataFileRecord * pRecord;
    if (sNameAux.length() > 0)
    {
        pRecord = SelectRecord(sNameAux);
    }
    else
    {
        pRecord = this;
    }
    
	if (pRecord != NULL)
	{
        PK_List<PK_DataFileRecord *> * pRecords = pRecord->GetRecords();
        for(PK_ListIterator(PK_DataFileRecord *) itor = pRecords->Begin(); itor != pRecords->End(); itor++)
    		{
            if ((*itor)->GetName() == sToFind)
			    {
				    retList.Add((*itor));
				    if (bGrabReferences)
				    {
					    (*itor)->Grab();
				    }
			    }
		}
	}
}

// Cria um DataFileRecord a partir de um XMLElement
void PK_DataFileRecord::InitializeFromXML(tinyxml2::XMLElement * pElem)
{
    if (pElem == NULL)
    {
        throw PK_NullArgumentException("pElem", __FILE__, __LINE__);
    }
    
    FreeResources();
    
    SetName(pElem->Name());
    
    // Campos
    const tinyxml2::XMLAttribute * pAttrib = pElem->FirstAttribute();
    if (pAttrib != NULL)
    {
        do
        {
            PK_DataFileField * pField = new PK_DataFileField(pAttrib->Name());
            AddField(*pField);
            pField->SetValue_Str(pAttrib->Value());
        }
        while((pAttrib = pAttrib->Next()) != NULL);
    }
       
    // Records filhos
    tinyxml2::XMLElement * pChildElem = pElem->FirstChildElement();
    if (pChildElem != NULL)
    {
        do
        {
            AddRecord(*PK_DataFileRecord::CreateFromXML(pChildElem));
        }
        while((pChildElem = pChildElem->NextSiblingElement()) != NULL);
    }
}
    
// Devolve o child record com o nome sRecordName. Se nao existir, devolve NULL
PK_DataFileRecord * PK_DataFileRecord::GetChildRecord(const PK_String &sRecordName)
{
    for(PK_ListIterator(PK_DataFileRecord *) itor = m_records.Begin(); itor != m_records.End(); itor++)
    {
  		if ((*itor)->GetName() == sRecordName)
        {
            return (*itor);
        }
    }
    
    return NULL;
}

// Devolve o child record com o nome sRecordName. Se nao existir, devolve NULL
PK_DataFileRecord * PK_DataFileRecord::GetChildRecord(const PK_String &sRecordName, bool bThrowsException)
{
    PK_DataFileRecord *pChildRec = GetChildRecord(sRecordName);
    if (pChildRec == NULL && bThrowsException)
    {
        throw PK_SystemException("Record named %s not found in DataFileRecord named %s.", __FILE__, __LINE__, sRecordName.c_str(), GetName().c_str());
    }
    return NULL;
}
  
// Devolve o field com o nome sFieldName. Se nao existir devolve NULL
PK_DataFileField * PK_DataFileRecord::GetField(const PK_String &sFieldName)
{
    for(PK_ListIterator(PK_DataFileField *) itor = m_fields.Begin(); itor != m_fields.End(); itor++)
    {
  		if ((*itor)->GetName() == sFieldName)
        {
            return (*itor);
        }
    }
   
    return NULL;
}

// Devolve o field com o nome sFieldName. Se nao existir lanca excepcao se bThrowsException = true
PK_DataFileField * PK_DataFileRecord::GetField(const PK_String &sFieldName, bool bThrowsException)
{
  PK_DataFileField *pField = GetField(sFieldName);
  if (pField == NULL && bThrowsException)
  {
      throw PK_SystemException("Field with name %s not found in DataFileRecord named %s.", __FILE__, __LINE__, sFieldName.c_str(), GetName().c_str());
  }

  return pField;
}


// Records condicionais teem o seguinte formato:
//    <color value="0, 255, 0">
//        <condition statement="platform=iPad" value="0,0,0"/>
//    </color>
PK_DataFileField * PK_DataFileRecord::GetConditionalField(const PK_String &sFieldName)
{
    PK_List<PK_DataFileRecord *> retList;
    SelectRecords("condition", retList, false);
    if (retList.GetCount() > 0)
    {
        for(PK_ListIterator(PK_DataFileRecord *) itor = retList.Begin(); itor != retList.End(); itor++)
        {
            PK_DataFileField * pStatementField = (*itor)->GetField("statement");
            if (pStatementField == NULL)
            {
                throw PK_SystemException("Condition field must have 'statement' field.", __FILE__, __LINE__);
            }
            if (PK_DataFileRecord::EvaluateCondition(pStatementField->GetValue_String()) == false)
            {
                continue;
            }
            PK_DataFileField * pField = (*itor)->GetField(sFieldName);
            if (pField == NULL)
            {
                throw PK_SystemException("Field named '%s' not found in record '%s'.", __FILE__, __LINE__, GetName().c_str(), sFieldName.c_str());
            }
            return pField;
        }
    }

    return GetField(sFieldName);
}
    
//
PK_DataFileField * PK_DataFileRecord::GetConditionalChildRecordField(const PK_String &sRecordName, const PK_String &sFieldName, bool bMandatory)
{
    PK_DataFileRecord *pRecord = SelectRecord(sRecordName);
    if (pRecord == NULL)
    {
        if (!bMandatory)
        {
            return NULL;
        }
        throw PK_SystemException("Record named '%s' not found in record '%s'.", __FILE__, __LINE__, sRecordName.c_str(), GetName().c_str());
    }
    return  pRecord->GetConditionalField(sFieldName);
}
    

// Seta um valor num campo do tipo string
void PK_DataFileRecord::SetFieldValue_Str(const PK_String &sFieldName, const PK_String & sValue)
{
    PK_DataFileField * pField = GetField(sFieldName);
    if (pField == NULL)
    {
        AddField(sFieldName, sValue);
    }
    else
    {
        pField->SetValue_Str(sValue);
    }
}
    
// Seta um valor num campo do tipo int
void PK_DataFileRecord::SetFieldValue_Int(const PK_String &sFieldName, int iValue)
{
    PK_DataFileField * pField = GetField(sFieldName);
    if (pField == NULL)
    {
        AddField(sFieldName, iValue);
    }
    else
    {
        pField->SetValue_Int(iValue);
    }    
}
// ----------------------------------------------------
int PK_DataFileRecord::GetFieldValue_Int(const PK_String &sFieldName)
{
    PK_DataFileField *pField = GetField(sFieldName, true);
    return pField->GetValue_Int();
}
// ----------------------------------------------------
bool PK_DataFileRecord::GetFieldValue_Bool(const PK_String &sFieldName)
{
    PK_DataFileField *pField = GetField(sFieldName, true);
    return pField->GetValue_Bool();
}
// ----------------------------------------------------
float PK_DataFileRecord::GetFieldValue_Float(const PK_String &sFieldName)
{
    PK_DataFileField *pField = GetField(sFieldName, true);
    return pField->GetValue_Float();
}
// ----------------------------------------------------
PK_String PK_DataFileRecord::GetFieldValue_String(const PK_String &sFieldName)
{
    PK_DataFileField *pField = GetField(sFieldName, true);
    return pField->GetValue_String();
}
// ----------------------------------------------------
PK_Color PK_DataFileRecord::GetFieldValue_Color(const PK_String &sFieldName)
{
    PK_DataFileField *pField = GetField(sFieldName, true);
    return pField->GetValue_Color();
}
// ----------------------------------------------------
PK_Vector3 PK_DataFileRecord::GetFieldValue_Vector3(const PK_String &sFieldName)
{
    PK_DataFileField *pField = GetField(sFieldName, true);
    return pField->GetValue_Vector3();
}
// ----------------------------------------------------
PK_Vector2 PK_DataFileRecord::GetFieldValue_Vector2(const PK_String &sFieldName)
{
    PK_DataFileField *pField = GetField(sFieldName, true);
    return pField->GetValue_Vector2();
}
// ----------------------------------------------------
PK_tSize PK_DataFileRecord::GetFieldValue_Size(const PK_String &sFieldName)
{
    PK_DataFileField *pField = GetField(sFieldName, true);
    return pField->GetValue_Size();
}
// ----------------------------------------------------
PK_tAABoundingSquare PK_DataFileRecord::GetFieldValue_AABoundingSquare(const PK_String &sFieldName)
{
    PK_DataFileField *pField = GetField(sFieldName, true);
    return pField->GetValue_AABoundingSquare();
}
// ----------------------------------------------------
PK_tResolution PK_DataFileRecord::GetFieldValue_Resolution(const PK_String &sFieldName)
{
    PK_DataFileField *pField = GetField(sFieldName, true);
    return pField->GetValue_Resolution();
}

// ----------------------------------------------------
int PK_DataFileRecord::GetFieldValue_Int(const PK_String &sFieldName, const int defaultValue)
{
    PK_DataFileField *pField = GetField(sFieldName);
    if (pField == NULL)
    {
        return defaultValue;
    }
    return pField->GetValue_Int();
}
// ----------------------------------------------------
bool PK_DataFileRecord::GetFieldValue_Bool(const PK_String &sFieldName, const bool defaultValue)
{
    PK_DataFileField *pField = GetField(sFieldName);
    if (pField == NULL)
    {
        return defaultValue;
    }
    return pField->GetValue_Bool();
}
// ----------------------------------------------------
float PK_DataFileRecord::GetFieldValue_Float(const PK_String &sFieldName, const float defaultValue)
{
    PK_DataFileField *pField = GetField(sFieldName);
    if (pField == NULL)
    {
        return defaultValue;
    }
    return pField->GetValue_Float();
}
// ----------------------------------------------------
PK_String PK_DataFileRecord::GetFieldValue_String(const PK_String &sFieldName, const PK_String &defaultValue)
{
    PK_DataFileField *pField = GetField(sFieldName);
    if (pField == NULL)
    {
        return defaultValue;
    }
    return pField->GetValue_String();
}
// ----------------------------------------------------
PK_Color PK_DataFileRecord::GetFieldValue_Color(const PK_String &sFieldName, const PK_Color &defaultValue)
{
    PK_DataFileField *pField = GetField(sFieldName);
    if (pField == NULL)
    {
        return defaultValue;
    }
    return pField->GetValue_Color();
}
// ----------------------------------------------------
PK_Vector3 PK_DataFileRecord::GetFieldValue_Vector3(const PK_String &sFieldName, const PK_Vector3 &defaultValue)
{
    PK_DataFileField *pField = GetField(sFieldName);
    if (pField == NULL)
    {
        return defaultValue;
    }
    return pField->GetValue_Vector3();
}
// ----------------------------------------------------
PK_Vector2 PK_DataFileRecord::GetFieldValue_Vector2(const PK_String &sFieldName, const PK_Vector2 &defaultValue)
{
    PK_DataFileField *pField = GetField(sFieldName);
    if (pField == NULL)
    {
        return defaultValue;
    }
    return pField->GetValue_Vector2();
}
// ----------------------------------------------------
PK_tSize PK_DataFileRecord::GetFieldValue_Size(const PK_String &sFieldName, const PK_tSize &defaultValue)
{
    PK_DataFileField *pField = GetField(sFieldName);
    if (pField == NULL)
    {
        return defaultValue;
    }
    return pField->GetValue_Size();
}
// ----------------------------------------------------
PK_tAABoundingSquare PK_DataFileRecord::GetFieldValue_AABoundingSquare(const PK_String &sFieldName, const PK_tAABoundingSquare &defaultValue)
{
    PK_DataFileField *pField = GetField(sFieldName);
    if (pField == NULL)
    {
        return defaultValue;
    }
    return pField->GetValue_AABoundingSquare();
}
// ----------------------------------------------------
PK_tResolution PK_DataFileRecord::GetFieldValue_Resolution(const PK_String &sFieldName, const PK_tResolution &defaultValue)
{
    PK_DataFileField *pField = GetField(sFieldName);
    if (pField == NULL)
    {
        return defaultValue;
    }
    return pField->GetValue_Resolution();
}

// ----------------------------------------------------
int PK_DataFileRecord::GetChildRecordFieldValue_Int(const PK_String &sChildRecordName, const PK_String &sFieldName)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName, true);
  return pChildRec->GetFieldValue_Int(sFieldName);
}
// ----------------------------------------------------
bool PK_DataFileRecord::GetChildRecordFieldValue_Bool(const PK_String &sChildRecordName, const PK_String &sFieldName)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName, true);
  return pChildRec->GetFieldValue_Bool(sFieldName);
}
// ----------------------------------------------------
float PK_DataFileRecord::GetChildRecordFieldValue_Float(const PK_String &sChildRecordName, const PK_String &sFieldName)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName, true);
  return pChildRec->GetFieldValue_Float(sFieldName);
}
// ----------------------------------------------------
PK_String PK_DataFileRecord::GetChildRecordFieldValue_String(const PK_String &sChildRecordName, const PK_String &sFieldName)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName, true);
  return pChildRec->GetFieldValue_String(sFieldName);
}
// ----------------------------------------------------
PK_Color PK_DataFileRecord::GetChildRecordFieldValue_Color(const PK_String &sChildRecordName, const PK_String &sFieldName)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName, true);
  return pChildRec->GetFieldValue_Color(sFieldName);
}
// ----------------------------------------------------
PK_Vector3 PK_DataFileRecord::GetChildRecordFieldValue_Vector3(const PK_String &sChildRecordName, const PK_String &sFieldName)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName, true);
  return pChildRec->GetFieldValue_Vector3(sFieldName);
}
// ----------------------------------------------------
PK_Vector2 PK_DataFileRecord::GetChildRecordFieldValue_Vector2(const PK_String &sChildRecordName, const PK_String &sFieldName)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName, true);
  return pChildRec->GetFieldValue_Vector2(sFieldName);
}
// ----------------------------------------------------
PK_tSize PK_DataFileRecord::GetChildRecordFieldValue_Size(const PK_String &sChildRecordName, const PK_String &sFieldName)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName, true);
  return pChildRec->GetFieldValue_Size(sFieldName);
}
// ----------------------------------------------------
PK_tAABoundingSquare PK_DataFileRecord::GetChildRecordFieldValue_AABoundingSquare(const PK_String &sChildRecordName, const PK_String &sFieldName)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName, true);
  return pChildRec->GetFieldValue_AABoundingSquare(sFieldName);
}

// ----------------------------------------------------
PK_tResolution PK_DataFileRecord::GetChildRecordFieldValue_Resolution(const PK_String &sChildRecordName, const PK_String &sFieldName)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName, true);
  return pChildRec->GetFieldValue_Resolution(sFieldName);
}

// ----------------------------------------------------
int PK_DataFileRecord::GetChildRecordFieldValue_Int(const PK_String &sChildRecordName, const PK_String &sFieldName, const int &defaultValue)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName);
  if (pChildRec == NULL)
  {
     return defaultValue;
  }
  return pChildRec->GetFieldValue_Int(sFieldName, defaultValue);    
}
// ----------------------------------------------------
bool PK_DataFileRecord::GetChildRecordFieldValue_Bool(const PK_String &sChildRecordName, const PK_String &sFieldName, const bool &defaultValue)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName);
  if (pChildRec == NULL)
  {
     return defaultValue;
  }
  return pChildRec->GetFieldValue_Bool(sFieldName, defaultValue);    
}
// ----------------------------------------------------
float PK_DataFileRecord::GetChildRecordFieldValue_Float(const PK_String &sChildRecordName, const PK_String &sFieldName, const float &defaultValue)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName);
  if (pChildRec == NULL)
  {
     return defaultValue;
  }
  return pChildRec->GetFieldValue_Float(sFieldName, defaultValue);    
}
// ----------------------------------------------------
PK_String PK_DataFileRecord::GetChildRecordFieldValue_String(const PK_String &sChildRecordName, const PK_String &sFieldName, const PK_String &defaultValue)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName);
  if (pChildRec == NULL)
  {
     return defaultValue;
  }
  return pChildRec->GetFieldValue_String(sFieldName, defaultValue);    
}
// ----------------------------------------------------
PK_Color PK_DataFileRecord::GetChildRecordFieldValue_Color(const PK_String &sChildRecordName, const PK_String &sFieldName, const PK_Color &defaultValue)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName);
  if (pChildRec == NULL)
  {
     return defaultValue;
  }
  return pChildRec->GetFieldValue_Color(sFieldName, defaultValue);    
}
// ----------------------------------------------------
PK_Vector3 PK_DataFileRecord::GetChildRecordFieldValue_Vector3(const PK_String &sChildRecordName, const PK_String &sFieldName, const PK_Vector3 &defaultValue)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName);
  if (pChildRec == NULL)
  {
     return defaultValue;
  }
  return pChildRec->GetFieldValue_Vector3(sFieldName, defaultValue);    
}
// ----------------------------------------------------
PK_Vector2 PK_DataFileRecord::GetChildRecordFieldValue_Vector2(const PK_String &sChildRecordName, const PK_String &sFieldName, const PK_Vector2 &defaultValue)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName);
  if (pChildRec == NULL)
  {
     return defaultValue;
  }
  return pChildRec->GetFieldValue_Vector2(sFieldName, defaultValue);    
}
// ----------------------------------------------------
PK_tSize PK_DataFileRecord::GetChildRecordFieldValue_Size(const PK_String &sChildRecordName, const PK_String &sFieldName, const PK_tSize &defaultValue)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName);
  if (pChildRec == NULL)
  {
     return defaultValue;
  }
  return pChildRec->GetFieldValue_Size(sFieldName, defaultValue);    
}
// ----------------------------------------------------
PK_tAABoundingSquare PK_DataFileRecord::GetChildRecordFieldValue_AABoundingSquare(const PK_String &sChildRecordName, const PK_String &sFieldName, const PK_tAABoundingSquare &defaultValue)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName);
  if (pChildRec == NULL)
  {
     return defaultValue;
  }
  return pChildRec->GetFieldValue_AABoundingSquare(sFieldName, defaultValue);    
}
// ----------------------------------------------------
PK_tResolution PK_DataFileRecord::GetChildRecordFieldValue_Resolution(const PK_String &sChildRecordName, const PK_String &sFieldName, const PK_tResolution &defaultValue)
{
  PK_DataFileRecord *pChildRec = GetChildRecord(sChildRecordName);
  if (pChildRec == NULL)
  {
     return defaultValue;
  }
  return pChildRec->GetFieldValue_Resolution(sFieldName, defaultValue);    
}

// static - Cria um DataFileRecord a partir de um XMLElement
PK_DataFileRecord * PK_DataFileRecord::CreateFromXML(tinyxml2::XMLElement * pElem)
{
    if (pElem == NULL)
    {
        throw PK_NullArgumentException("pElem", __FILE__, __LINE__);
    }
    
    PK_DataFileRecord * pRecord = new PK_DataFileRecord();
    if (pRecord == NULL)
    {
        throw PK_OutOfMemoryException("PK_DataFileRecord", sizeof(PK_DataFileRecord), __FILE__, __LINE__);
    }
    
    pRecord->InitializeFromXML(pElem);
    return pRecord;
}


// tokens:
// platform    (nome)
// resolution  (nome da resolucao e nao X,X)
// &
// |
// Exemplo:
// "platform=Android"
// "platform=iOS&resolution=iPad"
// "platform=iOS|platform=Android"

// OPTIMIZATION:As variaveis podem ser pre-calculadas, no switch (STATE_VALUE)
bool PK_DataFileRecord::EvaluateCondition(const PK_String &sCondition)
{
    if (sCondition.length() == 0)
    {
        return true;
    }
    
    int iCurrentOper = OPER_OR;     // Comeca com OR por causa da condicao inicial
    bool bRetVal = false;           // Comeca com false por causa da condicao inicial
    int iState = STATE_VARIABLE;    // Estado da maquina de estados
    int iVariable = VARIABLE_CODE_UNK;
    char * ptr = (char *)sCondition.c_str();


    do
    {
        switch(iState)
        {
            case STATE_VARIABLE:
                {
                    iVariable = GetVariable(ptr, &ptr);
                    if (iVariable == VARIABLE_CODE_UNK)
                    {
                        throw PK_SystemException("Error parsing condition '%s'. Invalid variable.", __FILE__, __LINE__, ptr);
                    }
                    iState = STATE_COMPARER;
                }
                break;

            case STATE_COMPARER:
                {
                    if (ptr[0] != '=')
                    {
                        throw PK_SystemException("Error parsing condition '%s'. Expected token '='.", __FILE__, __LINE__, ptr);
                    }
                    ptr++;
                    iState = 2;
                }
                break;

            case STATE_VALUE:
                {
                    int len;
                    char * szVal = GetValue(ptr, &len, &ptr);
                    bool bResult;
                    switch(iVariable)
                    {
                        case VARIABLE_CODE_PLATFORM:
                            {
                                bResult = (memcmp(PK_TypeConverters::PlatformTypeToStr(PK_Environment::GetPlatform()).c_str(), szVal, len) == 0);
                            }
                            break;

                        case VARIABLE_CODE_BUILD:
                            {
                                PK_String sBuildStr = PK_TypeConverters::BuildTypeToStr(PK_Environment::GetBuildType());
#ifdef POKE_DEBUG
                                if (sBuildStr != PK_TypeConverters::BuildTypeToStr(BuildType_Debug) &&
                                    sBuildStr != PK_TypeConverters::BuildTypeToStr(BuildType_Release))
                                {
                                    throw PK_SystemException("Invalid build type '%s'.", __FILE__, __LINE__, sBuildStr.c_str());
                                }
#endif
                                bResult = (memcmp(sBuildStr.c_str(), szVal, len) == 0);
                            }
                            break;
                        default:
                            throw PK_SystemException("Error parsing condition '%s'. Invalid variable type '%d'", __FILE__, __LINE__, iVariable);
                    }
                    if (iCurrentOper == OPER_OR) // or
                    {
                        bRetVal = (bRetVal | bResult);
                    }
                    else // and
                    {
                        bRetVal = (bRetVal & bResult);
                    }
                    iState = 3;
                }
                break;

            case STATE_OPERATION:
                switch(ptr[0])
                {
                    case '&':
                    case '|':
                        {
                            iCurrentOper = (ptr[0]=='&'? OPER_AND : OPER_OR);
                            iState = 0;
                            ptr++;
                            break;
                        }
                    default:
                        throw PK_SystemException("Error parsing condition '%s'. Expected '&' or '|'.", __FILE__, __LINE__);
                }
                break;
        }
    }
    while(ptr[0] != '\0');

    return bRetVal;
}

//
int PK_DataFileRecord::GetVariable(char * strCode, char ** strRet)
{
    if (memcmp(strCode, "platform", 8) == 0)
    {
        *strRet = strCode + 8;
        return VARIABLE_CODE_PLATFORM;
    }

    if (memcmp(strCode, "build", 5) == 0)
    {
        *strRet = strCode + 5;
        return VARIABLE_CODE_BUILD;
    }
  
    return VARIABLE_CODE_UNK;
}

//
char * PK_DataFileRecord::GetValue(char * strCode, int *iLen, char ** strRet)
{
    int i;
    for(i = 0; ; i++)
    {
        if (strCode[i] == '\0' ||
            strCode[i] == '&' ||
            strCode[i] == '|')
        {
            break;
        }
    }

    *iLen = i;
    *strRet = strCode + i;
    return strCode;
}

}
