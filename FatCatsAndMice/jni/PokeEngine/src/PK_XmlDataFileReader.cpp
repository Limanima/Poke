#include "PK_SystemException.h"
#include "PK_DataFile.h"
#include "PK_XmlDataFileReader.h"
#include "tinyxml2.h"
#include "PK_FileReader.h"
#include "PK_ClassFactory.h"

namespace PK {

// Faz o load do ficheiro para um DataFile
void PK_XmlDataFileReader::Load(PK_DataFile &dataFile, const PK_String &sFilename)
{
    PK_FileReader reader;
    PK_MemoryBuffer buffer;
    reader.ReadFile(sFilename, buffer);

	tinyxml2::XMLDocument xmlDoc;
    
    if (xmlDoc.Parse(buffer.GetAsStr()) != tinyxml2::XML_SUCCESS)
	{
		throw PK_SystemException(PK_String("Could not open file.") + sFilename, __FILE__, __LINE__);
	}
     

	tinyxml2::XMLElement * pRootElem = xmlDoc.FirstChildElement();
	// XML vazio, limpa o datafile e sai
	if (pRootElem == NULL)
	{
		dataFile.SetRoot(NULL);
		return;
	}

	PK_DataFileRecord * pRootRec = CreateRecordFromXML(pRootElem);
	dataFile.SetRoot(pRootRec);
}

// Cria um DataFileRecord a partir de um XMLElement
PK_DataFileRecord * PK_XmlDataFileReader::CreateRecordFromXML(tinyxml2::XMLElement * pElem)
{
	PK_DataFileRecord * pRecord = new PK_DataFileRecord(pElem->Name());

	// Campos
	const tinyxml2::XMLAttribute * pAttrib = pElem->FirstAttribute();
	if (pAttrib != NULL)
	{
		do
		{
			PK_DataFileField * pField = new PK_DataFileField(pAttrib->Name());
			pRecord->AddField(*pField);
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
			pRecord->AddRecord(*CreateRecordFromXML(pChildElem));
		}
		while((pChildElem = pElem->NextSiblingElement()) != NULL);
	}
	return pRecord;
}

}
