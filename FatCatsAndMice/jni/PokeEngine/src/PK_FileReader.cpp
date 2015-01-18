#include <sdl.h>
#include "PK_FileReader.h"
#include "PK_Exceptions.h"

namespace PK
{

     
PK_FileReader::PK_FileReader(const PK_String &sName) :
  PK_Object(sName)
{
  SetTypeName("PK_FileReader");
}
    
// Le o conteudo do ficheiro para dentro do buffer
void PK_FileReader::ReadFile(const PK_String &sFilename, PK_MemoryBuffer &memBuffer)
{    
    SDL_RWops * file = SDL_RWFromFile(sFilename.c_str(), "rb");
    if (file == NULL)
    {
        throw PK_SDLException(__FILE__, __LINE__);
    }
    // Determinar tamanho do ficheiro
    unsigned int iFileLength = (unsigned int)SDL_RWseek(file, 0, SEEK_END);
    
    // Recolocar o pointer no inicio
    SDL_RWseek(file, 0, RW_SEEK_SET);
    
    // Setar o tamanho do buffer
    memBuffer.SetSize(iFileLength, false, false);
 
    // Ler os dados para o buffer
    SDL_RWread(file, memBuffer.GetData(), iFileLength, 1);
    memBuffer.SetLength(iFileLength);
    SDL_RWclose(file);

}
    
} // namespace
