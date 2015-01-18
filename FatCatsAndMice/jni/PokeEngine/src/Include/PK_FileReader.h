#ifndef _PK_FILEREADER_H_
#define _PK_FILEREADER_H_

#include "PK_Object.h"
#include "PK_String.h"
#include "PK_MemoryBuffer.h"

namespace PK {

// Interface para leitura de ficheiros
// Deve ser implementado para cada plataforma
class PK_FileReader : public PK_Object
{
    
public:
    PK_FileReader(const PK_String &sName = "");

    // Deve ler o conteudo de um ficheiro para o buffer
    virtual void ReadFile(const PK_String &sFilename, PK_MemoryBuffer &memBuffer);
};

} // Namespace

#endif
