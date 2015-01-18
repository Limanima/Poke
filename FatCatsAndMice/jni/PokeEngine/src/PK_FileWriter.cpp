#include <sdl.h>
#include "PK_FileWriter.h"
#include "PK_Exceptions.h"

namespace PK
{
    
PK_FileWriter::PK_FileWriter(const PK_String &sName) :
  PK_Object(sName)
{
  SetTypeName("PK_SDLFileWriter");
}
    
// Le o conteudo do ficheiro para dentro do buffer
void PK_FileWriter::WriteFile(const PK_String &sFilename, PK_MemoryBuffer &memBuffer, PK_eFileWriteOpenMode mode)
{    
    WriteFile(sFilename, memBuffer.GetData(), memBuffer.GetLength(), mode);
}

//
void PK_FileWriter::WriteFile(const PK_String &sFilename, const PK_String &sText, PK_eFileWriteOpenMode mode)
{
    WriteFile(sFilename, (void*)sText.data(), sText.length(), mode);
}

//
void PK_FileWriter::WriteFile(const PK_String &sFilename, void *pData, unsigned long lSize, PK_eFileWriteOpenMode mode)
{
    PK_String sMode;
    switch(mode)
    {
      case FileWriteOpenMode_CreateAlways:
        sMode = "w";
	    break;

      case FileWriteOpenMode_Append:
        sMode = "a";
	    break;

      default:
        throw new PK_SystemException("Invalid file mode '%d'", __FILE__, __LINE__, (int)mode);

    }
    
    SDL_RWops * file = SDL_RWFromFile(sFilename.c_str(), sMode.c_str());
    if (file == NULL)
    {
        throw PK_SDLException(__FILE__, __LINE__);
    }
    SDL_RWwrite(file, pData,  lSize, 1);
    SDL_RWclose(file);
}

} // namespace
