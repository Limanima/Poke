#ifndef _XMLDATAFILEWRITER_H_
#define _XMLDATAFILEWRITER_H_

#include "tinyxml2.h"
#include "PK_DataFile.h"

namespace PK {

class PK_XmlDataFileWriter : PK_Object
{
public:
	PK_XmlDataFileWriter();

	void Write(PK_DataFile &dataFile, const PK_String &sFilename);

private:
	tinyxml2::XMLElement * SerializeRecord(PK_DataFileRecord &record, tinyxml2::XMLDocument &xmlDoc);
};

}

#endif
