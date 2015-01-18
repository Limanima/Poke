#ifndef _PK_DATAFILE_H_
#define _PK_DATAFILE_H_

#include "PK_String.h"
#include "PK_Object.h"
#include "PK_DataFileRecord.h"
#include "PK_DataFileField.h"

namespace PK {
    
class PK_DataFile : public PK_Object
{
private:
	PK_DataFileRecord * m_pRoot;

public:
	PK_DataFile();
    ~PK_DataFile();
    void FreeResources();
	void SetRoot(PK_DataFileRecord * pRecord);
	void SaveAsXML(const PK_String &sFilename);
	void LoadFromXML(const PK_String &sFilename);   
    PK_DataFileRecord * LoadFromXML(const PK_String &sFilename, const PK_String &sRootName);
    PK_DataFileRecord * SelectRecord(const PK_String &sName);
    inline PK_DataFileRecord * GetRoot()
	{
		return m_pRoot;
	}
    inline static PK_String GetPathDelimiter() { return "/"; }

};

}

#endif
