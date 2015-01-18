#include "PK_Globals.h"
#include "PK_Settings.h"
#include "PK_DataFiles.h"
#include "PK_Exceptions.h"
#include "PK_TypeConverters.h"
#include "PK_File.h"

namespace PK {

PK_Settings::PK_Settings(const PK_String &sName, const PK_String & sRootName) :
        PK_Object(sName)
{
	m_sRootName = sRootName;
	m_pRootRecord = NULL;
    m_bLoaded = false;
    SetLoadFailsIfNotExists(true);
}

PK_Settings::~PK_Settings()
{
	if (m_pRootRecord != NULL)
	{
		m_pRootRecord->Release();
		m_pRootRecord = NULL;
	}
}

// Carrega os settings do disco
void PK_Settings::Load(const PK_String &sFilename)
{
    if (m_bLoaded)
    {
        throw PK_SystemException("Settings file named '%s' has already been loaded.", __FILE__, __LINE__, sFilename.c_str());
    }
    
    if (!PK_File::Exists(sFilename))
    {
        if (GetLoadFailsIfNotExists() == false)
        {
            CreateRoot();
            return;
        }
    }
 
    PK_DataFile dataFile;
	dataFile.LoadFromXML(sFilename);
    m_pRootRecord = dataFile.SelectRecord(m_sRootName);
    if (m_pRootRecord == NULL)
	{
		throw PK_SystemException("Settings file is invalid. Couldn't find record '%s' in file %s.", __FILE__, __LINE__, 
			m_sRootName.c_str(), sFilename.c_str());
	}
    m_pRootRecord->Grab();
    m_bLoaded = true;
    SetFilename(sFilename);
    OnLoad();
}
    
//
void PK_Settings::Save(const PK_String &sFilename)
{
    if (!m_bLoaded)
    {
        m_pRootRecord = new PK_DataFileRecord(m_sRootName);
        m_pRootRecord->Grab();
        m_bLoaded = true;
    }
    SetFilename(sFilename);
    OnSave();
    PK::PK_DataFile file;
    file.SetRoot(m_pRootRecord);
    PK::PK_XmlDataFileWriter writer;
    writer.Write(file, sFilename);
}

//
void PK_Settings::Load()
{
    if (GetFilename() == "")
    {
        throw PK_SystemException("Cannot load settings file because the filename was not set. Use SetFilename().", __FILE__, __LINE__);
    }
    
    Load(GetFilename());
}

//
void PK_Settings::Save()
{
    if (GetFilename() == "")
    {
        throw PK_SystemException("Cannot load settings file because the filename was not set. Use SetFilename().", __FILE__, __LINE__);
    }
    Save(GetFilename());
}

//
void PK_Settings::SelectRecords(const PK_String &sName, PK_List<PK_DataFileRecord *> &retList)
{
    m_pRootRecord->SelectRecords(sName, retList, false);
}

//
PK_DataFileRecord * PK_Settings::GetRecord(const PK_String &sRecord)
{
    if (!m_bLoaded)
    {
        throw PK_SystemException("Cannot obtain record name '%s' because the settings file has not been loaded.", __FILE__, __LINE__, sRecord.c_str());
    }
    PK_DataFileRecord * pRec = m_pRootRecord->SelectRecord(sRecord);
    return pRec;
}

PK_DataFileField * PK_Settings::GetField(const PK_String &sParamName)
{
    if (!m_bLoaded)
    {
        throw PK_SystemException("Cannot obtain parameter named '%s' because the settings file has not been loaded.", __FILE__, __LINE__, sParamName.c_str());
    }

    return m_pRootRecord->GetConditionalChildRecordField(sParamName, "value");
}

//
PK_DataFileField * PK_Settings::GetField(const PK_String &sPath, const PK_String &sParamName, bool bMandatory)
{
    PK_DataFileRecord * pRecord = GetRecord(sPath);
    if (pRecord == NULL)
    {
        if (!bMandatory)
        {
            return NULL;
        }
        
        throw PK_SystemException("Cannot obtain parameter named '%s' because the record named '%s' does not exist.", __FILE__, __LINE__, sParamName.c_str(), sPath.c_str());
    }
    return pRecord->GetConditionalChildRecordField(sParamName, "value", bMandatory);
}

//
int PK_Settings::GetParameterValue_Int(const PK_String &sParamName)
{
  PK_DataFileField * pField = GetField(sParamName);
  return pField->GetValue_Int();
}

//
bool PK_Settings::GetParameterValue_Bool(const PK_String &sParamName)
{
  PK_DataFileField * pField = GetField(sParamName);
  return pField->GetValue_Bool();
}
//
float PK_Settings::GetParameterValue_Float(const PK_String &sParamName)
{
  PK_DataFileField * pField = GetField(sParamName);
  return pField->GetValue_Float();
}

//------------------------------------------------------------------
PK_tResolution PK_Settings::GetParameterValue_Resolution(const PK_String &sParamName)
{
  PK_DataFileField * pField = GetField(sParamName);
  return pField->GetValue_Resolution();
}

//
PK_String PK_Settings::GetParameterValue_String(const PK_String &sParamName)
{
  PK_DataFileField * pField = GetField(sParamName);
  return pField->GetValue_String();
}

//
PK_Color PK_Settings::GetParameterValue_Color(const PK_String &sParamName)
{
  PK_DataFileField * pField = GetField(sParamName);
  return pField->GetValue_Color();
}

//
PK_Vector3 PK_Settings::GetParameterValue_Vector3(const PK_String &sParamName)
{
  PK_DataFileField * pField = GetField(sParamName);
  return pField->GetValue_Vector3();
}

//
PK_Vector2 PK_Settings::GetParameterValue_Vector2(const PK_String &sParamName)
{
  PK_DataFileField * pField = GetField(sParamName);
  return pField->GetValue_Vector2();
}

//
PK_tSize PK_Settings::GetParameterValue_Size(const PK_String &sParamName)
{
  PK_DataFileField * pField = GetField(sParamName);
  return pField->GetValue_Size();
}

//
PK_tAABoundingSquare PK_Settings::GetParameterValue_AABoundingSquare(const PK_String &sParamName)
{
  PK_DataFileField * pField = GetField(sParamName);
  return pField->GetValue_AABoundingSquare();
}

//
bool PK_Settings::GetParameterValue_Bool(const PK_String &sPath, const PK_String &sParamName)
{
  PK_DataFileField * pField = GetField(sPath, sParamName);
  return pField->GetValue_Bool();
}
    
//
bool PK_Settings::GetParameterValue_Bool(const PK_String &sPath, const PK_String &sParamName, bool bDefault)
{
    PK_DataFileField * pField = GetField(sPath, sParamName, false);
    if (pField == NULL)
    {
        return bDefault;
    }
    return pField->GetValue_Bool();
}

//
int PK_Settings::GetParameterValue_Int(const PK_String &sPath, const PK_String &sParamName)
{
  PK_DataFileField * pField = GetField(sPath, sParamName);

  return pField->GetValue_Int();
}
    
//
int PK_Settings::GetParameterValue_Int(const PK_String &sPath, const PK_String &sParamName, int iDefault)
{
    PK_DataFileField * pField = GetField(sPath, sParamName, false);
    if (pField == NULL)
    {
        return iDefault;
    }
    return pField->GetValue_Int();
}
    
//
PK_String PK_Settings::GetParameterValue_String(const PK_String &sPath, const PK_String &sParamName)
{
  PK_DataFileField * pField = GetField(sPath, sParamName);
  return pField->GetValue_String();
}
    
//
PK_String PK_Settings::GetParameterValue_String(const PK_String &sPath, const PK_String &sParamName, const PK_String & sDefault)
{
    PK_DataFileField * pField = GetField(sPath, sParamName, false);
    if (pField == NULL)
    {
        return sDefault;
    }
    return pField->GetValue_String();
}

//
PK_Color PK_Settings::GetParameterValue_Color(const PK_String &sPath, const PK_String &sParamName)
{
  PK_DataFileField * pField = GetField(sPath, sParamName);
  return pField->GetValue_Color();
}
    
//
PK_Color PK_Settings::GetParameterValue_Color(const PK_String &sPath, const PK_String &sParamName, const PK_Color & defaultVal)
{
    PK_DataFileField * pField = GetField(sPath, sParamName, false);
    if (pField == NULL)
    {
        return defaultVal;
    }
    return pField->GetValue_Color();
}

//
PK_DataFileField * PK_Settings::CreateField(const PK_String &sPath, const PK_String &sParamName)
{  
    PK_String sFullPath = sPath + PK_DataFile::GetPathDelimiter() + sParamName; 
    m_pRootRecord->CreatePath(sFullPath);
    PK_DataFileRecord *pRec = m_pRootRecord->SelectRecord(sFullPath); 
     return pRec->AddField("value", "");
}

//
void PK_Settings::SetParameterValue_Int(const PK_String &sPath, const PK_String &sParamName, int iValue)
{
    PK_DataFileField * pField = GetField(sPath, sParamName, false);
    if (pField == NULL)
    {
        pField = CreateField(sPath, sParamName);
    }
    pField->SetValue_Int(iValue);
}
    
//
void PK_Settings::SetParameterValue_Bool(const PK_String &sPath, const PK_String &sParamName, bool bValue)
{
    PK_DataFileField * pField = GetField(sPath, sParamName, false);
    if (pField == NULL)
    {
        pField = CreateField(sPath, sParamName);
    }
    pField->SetValue_Bool(bValue);
}
    
//
void PK_Settings::SetParameterValue_Str(const PK_String &sPath, const PK_String &sParamName, const PK_String &sValue)
{
    PK_DataFileField * pField = GetField(sPath, sParamName, false);
    if (pField == NULL)
    {
        pField = CreateField(sPath, sParamName);
    }
    pField->SetValue_Str(sValue);
}

//
void PK_Settings::CreateRoot()
{
    if (m_pRootRecord != NULL)
    {
        m_pRootRecord->Release();
    }
    m_pRootRecord = new PK_DataFileRecord(m_sRootName);
    m_pRootRecord->Grab();
    m_bLoaded = true;
    
}
    
}