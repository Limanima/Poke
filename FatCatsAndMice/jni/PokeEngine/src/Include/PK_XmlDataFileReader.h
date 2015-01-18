#ifndef _XMLDATAFILEREADER_H_
#define _XMLDATAFILEREADER_H_

#include "PK_DataFile.h"
#include "tinyxml2.h"

namespace PK {

class PK_XmlDataFileReader : PK_Object
{
public:
	static void Load(PK_DataFile &dataFile, const PK_String &sFilename);
	static PK_DataFileRecord * CreateRecordFromXML(tinyxml2::XMLElement * pElem);
};

}

#endif
