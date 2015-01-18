#include "PK_DataFile.h"
#include "PK_Exceptions.h"
#include "tinyxml2.h"
#include "PK_MemoryBuffer.h"
#include "PK_FileReader.h"
#include "PK_ClassFactory.h"



namespace PK {

PK_DataFile::PK_DataFile()
{ 
	SetTypeName("PK_DataFile");
	m_pRoot = NULL; 
}

PK_DataFile::~PK_DataFile()
{
    FreeResources();
}
    
// Libertar todos os resources utilizados
void PK_DataFile::FreeResources()
{
 	if (m_pRoot != NULL)
	{
		m_pRoot->Release();
		m_pRoot = NULL;
	}
    
}
    
// Seta a raiz do DataFile
// Se ja tem raiz e necessario libertar o DataFileRecord anterior
// Aceita NULL, que faz remover a raíz
void PK_DataFile::SetRoot(PK_DataFileRecord * pRecord)
{ 
	if (m_pRoot != NULL)
	{
		m_pRoot->Release();
	}
	m_pRoot = pRecord; 
	if (m_pRoot != NULL)
	{
		m_pRoot->Grab();
	}
}

// Grava DataFile em formato XML
void PK_DataFile::SaveAsXML(const PK_String &sFilename)
{
	
}

// Carrega o DataFile a partir de um ficheiro em formato XML e devolve a root
PK_DataFileRecord * PK_DataFile::LoadFromXML(const PK_String &sFilename, const PK_String &sRootName)
{
    FreeResources();
    
    PK_MemoryBuffer memBuffer;
    PK_FileReader file;
    file.ReadFile(sFilename, memBuffer); 
    tinyxml2::XMLDocument xmlDoc;
    
    if (xmlDoc.Parse(memBuffer.GetAsStr()) != tinyxml2::XML_SUCCESS)
	{
		throw PK_SystemException("Filename %s does is not a valid XML document.", __FILE__, __LINE__, sFilename.c_str());
	}
    if (xmlDoc.FirstChild() == NULL)
    {
        throw PK_SystemException("Cannot load DataFile from file %s. XML file does not have a root.", __FILE__, __LINE__, sFilename.c_str());
    }
    
    m_pRoot = PK_DataFileRecord::CreateFromXML(xmlDoc.FirstChildElement());
      if (sRootName.length() > 0)
    {
        if (m_pRoot->GetName() != sRootName)
        {
            throw PK_SystemException("Settings file is invalid. Couldn't find root record '%s' in file %s.", __FILE__, __LINE__, 
			            sRootName.c_str(), sFilename.c_str());
        }
    }

    m_pRoot->Grab();
    return m_pRoot;
}

// Carrega o DataFile a partir de um ficheiro em formato XML
void PK_DataFile::LoadFromXML(const PK_String &sFilename)
{
    LoadFromXML(sFilename, "");
}
    
//
PK_DataFileRecord * PK_DataFile::SelectRecord(const PK_String &sName)
{
    if (m_pRoot == NULL)
    {
       return NULL;
    }
    PK_String sPath = sName;
    PK_String sRootName = sPath.ExtractWord(PK_DataFile::GetPathDelimiter().c_str());
    if (m_pRoot->GetName() != sRootName)
    {
        return NULL;
    }
    if (sPath.length() == 0)
    {
        return m_pRoot;
    }
        
    
    return m_pRoot->SelectRecord(sPath);
}
    
}