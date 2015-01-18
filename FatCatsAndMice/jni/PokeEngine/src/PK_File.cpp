#include <sdl.h>
#include "PK_File.h"
#include "PK_Path.h"
#include "PK_Exceptions.h"

#if defined POKE_WINDOWS
    #define WINDOWS_MEAN_AND_LEAN
    #include <Windows.h>
#endif

#define PK_FILE_WILDCARD_CHAR "*"

namespace PK
{

// static 
bool PK_File::Exists(const PK_String & sfile)
{
    SDL_RWops * file = SDL_RWFromFile(sfile.c_str(), "rb");
    if (file == NULL)
    {
        return false;
    }
    
    SDL_RWclose(file);
    return true;
}

// static 
bool PK_File::ContainsWildcards(const PK_String & sSourceFilename)
{
    return (sSourceFilename.Contains(PK_FILE_WILDCARD_CHAR));
}

// static
void PK_File::Copy(const PK_String & sSourceFilename, const PK_String & sDestFilename, bool bOverwrite)
{
#if defined POKE_WINDOWS
    int rc = CopyFile(PK_Path::NormalizePath(sSourceFilename).c_str(), PK_Path::NormalizePath(sDestFilename).c_str(), !bOverwrite);
    if (rc == 0)
    {
        // FIXME - mostrar a mensagem de erro do windows e nao apenas o codigo
        throw PK_SystemException("Error copying file '%s' to file '%s', error code was '%d'", 
            __FILE__, __LINE__, sSourceFilename.c_str(), sDestFilename.c_str(), rc);
    }
#else
    throw PK_NotImplementedException("PK_File::Copy()" , __FILE__, __LINE__);
#endif
}

// static 
void PK_File::CopyMultiple(PK_String sSourceFolder, PK_String sDestFolder, const PK_String & sFileSpec, 
                           bool bCopyTree, bool bOverwrite, PK_Callback<PK_IFileCopyCallback> *pCopyCallback)
{
    if (!PK_Path::Exists(sDestFolder))
    {
        throw PK_SystemException("Destination folder '%s' does not exists.", __FILE__, __LINE__, sDestFolder.c_str());
    }

    PK_List<PK_String> files;
    PK_Path::GetFiles(files, sSourceFolder, sFileSpec);
    for(PK_ListIterator(PK_String) itor = files.Begin(); itor != files.End(); itor++)
    {
        PK_String sourceFile = PK_Path::Combine(sSourceFolder, (*itor));
        PK_String destFile = PK_Path::Combine(sDestFolder, (*itor));
        if (pCopyCallback != NULL)
        {
            if ((*pCopyCallback)->Execute(sourceFile, destFile, false) == false)
            {
                continue;
            }
        }
        PK_File::Copy(sourceFile, destFile);
    }

    // Folders
    PK_List<PK_String> folders;
    PK_Path::GetFolders(folders, sSourceFolder);
    for(PK_ListIterator(PK_String) itor = folders.Begin(); itor != folders.End(); itor++)
    {
        PK_String sSourceFolder2 = PK_Path::Combine(sSourceFolder,(*itor));
        PK_String sDestFolder2 = PK_Path::Combine(sDestFolder, (*itor));
        if ((*pCopyCallback)->Execute(sSourceFolder2, sDestFolder2, true) == false)
        {
            continue;
        }
        if (!PK_Path::Exists(sDestFolder2))
        {
            PK_Path::CreateFolder(sDestFolder2);
        }
        PK_File::CopyMultiple(sSourceFolder2, 
                              sDestFolder2, 
                              sFileSpec,
                              bCopyTree, bOverwrite, pCopyCallback);
    }
}

} // namespace
