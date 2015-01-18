#ifndef _PK_SETTINGS_H_
#define _PK_SETTINGS_H_

#include "PK_Object.h"
#include "PK_String.h"
#include "PK_tSize.h"
#include "PK_DataFiles.h"

namespace PK {

class PK_DataFileField;
class PK_DataFileRecord;
    
class PK_Settings : public PK_Object
{
private:
    PK_String			 m_sRootName;
    bool                 m_bLoaded;
    PK_DataFileRecord	*m_pRootRecord;
    PK_String            m_sFilename;
    bool                 m_bLoadFailsIfNotExists;
    
public:
    PK_Settings(const PK_String &sName, const PK_String &sRootName);
    ~PK_Settings();
    
    void Load(const PK_String &sFilename);
    void Save(const PK_String &sFilename);
    void Load();
    void Save();    

protected:
    void SelectRecords(const PK_String &sName, PK_List<PK_DataFileRecord *> &retList);
    PK_DataFileRecord * GetRecord(const PK_String &sRecord);

    //
    int GetParameterValue_Int(const PK_String &sParamName);
    bool GetParameterValue_Bool(const PK_String &sParamName);
    float GetParameterValue_Float(const PK_String &sParamName);
    PK_String GetParameterValue_String(const PK_String &sParamName);
    PK_Color GetParameterValue_Color(const PK_String &sParamName);
    PK_Vector3 GetParameterValue_Vector3(const PK_String &sParamName);
    PK_Vector2 GetParameterValue_Vector2(const PK_String &sParamName);
    PK_tSize GetParameterValue_Size(const PK_String &sParamName);
    PK_tAABoundingSquare GetParameterValue_AABoundingSquare(const PK_String &sParamName);
    PK_tResolution GetParameterValue_Resolution(const PK_String &sParamName);
    
    bool GetParameterValue_Bool(const PK_String &sPath, const PK_String &sParamName);
    bool GetParameterValue_Bool(const PK_String &sPath, const PK_String &sParamName, bool bDefault);
    int GetParameterValue_Int(const PK_String &sPath, const PK_String &sParamName);
    int GetParameterValue_Int(const PK_String &sPath, const PK_String &sParamName, int iDefault);
    PK_String GetParameterValue_String(const PK_String &sPath, const PK_String &sParamName);
    PK_String GetParameterValue_String(const PK_String &sPath, const PK_String &sParamName, const PK_String & sDefault);
    PK_Color GetParameterValue_Color(const PK_String &sPath, const PK_String &sParamName);
    PK_Color GetParameterValue_Color(const PK_String &sPath, const PK_String &sParamName, const PK_Color & defaultVal);

    PK_DataFileField * CreateField(const PK_String &sPath, const PK_String &sParamName);

    // Seters
    void SetParameterValue_Int(const PK_String &sPath, const PK_String &sParamName, int iValue);
    void SetParameterValue_Bool(const PK_String &sPath, const PK_String &sParamName, bool bValue);
    void SetParameterValue_Str(const PK_String &sPath, const PK_String &sParamName, const PK_String &sValue);

    void CreateRoot();
    
    //
    template<typename T> T GetEnumParameterValue(const PK_String &sParamName)
    {
        PK_DataFileField * pField = GetField(sParamName);
        return pField->GetEnumValue<T>();
    }
    
    inline PK_DataFileRecord * GetRootRecord() { return m_pRootRecord; }

    virtual void OnLoad() { }
    virtual void OnSave() { }
    inline void SetFilename(const PK_String &sFilename) { m_sFilename = sFilename; }

public:
    inline PK_String GetFilename() { return m_sFilename; }

    inline void SetLoadFailsIfNotExists(bool bFails) { m_bLoadFailsIfNotExists = bFails; }
    inline bool GetLoadFailsIfNotExists() { return m_bLoadFailsIfNotExists; }

private:
    PK_DataFileField * GetField(const PK_String &sParamName);    
    PK_DataFileField * GetField(const PK_String &sPath, const PK_String &sParamName, bool bMandatory = true);

};

}
#endif
