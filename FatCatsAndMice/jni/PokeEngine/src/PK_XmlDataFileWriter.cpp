#include <fstream>  
#include "PK_Consts.h"
#include "PK_XmlDataFileWriter.h"
#include "PK_List.h"
#include "PK_ClassFactory.h"
#include "PK_FileWriter.h"
#include "PK_TypeConverters.h"

namespace PK {

using namespace tinyxml2;

PK_XmlDataFileWriter::PK_XmlDataFileWriter()
{
	SetTypeName("PK_XmlDataFileWriter");
}

void PK_XmlDataFileWriter::Write(PK_DataFile &dataFile, const PK_String &sFilename)
{
	XMLDocument xmlDoc;
	PK_DataFileRecord * pRootRec = dataFile.GetRoot();
	if (pRootRec != NULL)
	{
		xmlDoc.InsertEndChild(SerializeRecord(*pRootRec, xmlDoc));
	}
    
    XMLPrinter printer;
    xmlDoc.Accept(&printer);
    
    PK_FileWriter writer;
    writer.WriteFile(sFilename, printer.CStr(), FileWriteOpenMode_CreateAlways);
}


XMLElement * PK_XmlDataFileWriter::SerializeRecord(PK_DataFileRecord &record, XMLDocument &xmlDoc)
{
	XMLElement * pRecElem = xmlDoc.NewElement(record.GetName().c_str());
	
	// Campos
	PK_List<PK_DataFileField *> * pFields = record.GetFields();
	for(PK_ListIterator(PK_DataFileField  *) itor = pFields->Begin(); itor != pFields->End(); itor++)
	{
		PK_DataFileField * pField = (*itor);
		switch(pField->GetDataFieldType())
		{
			case DataFieldType_Int:
				pRecElem->SetAttribute(pField->GetName().c_str(), pField->GetValue_Int());
				break;
			case DataFieldType_Str:
				pRecElem->SetAttribute(pField->GetName().c_str(), pField->GetValue_String().c_str());
				break;
            case DataFieldType_Bool:
				pRecElem->SetAttribute(pField->GetName().c_str(), PK_TypeConverters::BoolToStr(pField->GetValue_Bool()).c_str());
				break;
            case DataFieldType_Float:
				pRecElem->SetAttribute(pField->GetName().c_str(), pField->GetValue_Float());
				break;
            default:
                throw PK_SystemException("Cannot serialize data file field named '%s' because serialization of type '%s' is not supported. ",
                    __FILE__, __LINE__, pField->GetName().c_str(), PK_TypeConverters::DataFieldTypeToStr(pField->GetDataFieldType()).c_str());
		}
	}

	// Records filhos
	PK_List<PK_DataFileRecord *> * pRecords = record.GetRecords();
	for(PK_ListIterator(PK_DataFileRecord  *) itor = pRecords->Begin(); itor != pRecords->End(); itor++)
	{
		pRecElem->InsertEndChild(SerializeRecord(*(*itor), xmlDoc));
	}

	return pRecElem;
}

}
