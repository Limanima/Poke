#ifndef _PK_FILEWRITER_H_
#define _PK_FILEWRITER_H_

#include "PK_Object.h"
#include "PK_String.h"
#include "PK_MemoryBuffer.h"
#include "PK_Types.h"

namespace PK {

// Interface para leitura de ficheiros
// Deve ser implementado para cada plataforma
class PK_FileWriter : public PK_Object
{
    
public:
    PK_FileWriter(const PK_String &sName = "");

    // Deve ler o conteudo de um ficheiro para o buffer
    virtual void WriteFile(const PK_String &sFilename, PK_MemoryBuffer &memBuffer, PK_eFileWriteOpenMode mode);
    virtual void WriteFile(const PK_String &sFilename, const PK_String &sText, PK_eFileWriteOpenMode mode);
    virtual void WriteFile(const PK_String &sFilename, void *pData, unsigned long lSize, PK_eFileWriteOpenMode mode);

};

} // Namespace

#endif
