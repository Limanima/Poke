#include <algorithm>
#include "PK_Path.h"
#include "PK_Consts.h"
#include "PK_Exceptions.h"
#include "PK_Log.h"

#if defined POKE_WINDOWS
    #define WINDOWS_MEAN_AND_LEAN
    #include <Windows.h>
#endif

#define PK_PATH_SEPARATOR          "/"
#define PK_EXTENSION_SEPARATOR     "."
#define PK_FILE_WILDCARD_CHAR      "*"

namespace PK
{
    
// Devolve o nome do ficheiro: AAAAAAA/BBBBBB/CCCCCCC devolve CCCCCCC
PK_String PK_Path::GetFileName(const PK_String & sPath)
{
    PK_String sFilename = sPath;
    PK_String sNormalized = NormalizePath(sPath);
    char * ptr = (char*) sNormalized.c_str();
    for(int i = (int)sPath.length() - 1; i >=0; i--)
    {
        if (ptr[i] == PK_PATH_SEPARATOR[0] && sPath.length() > 1)
        {
            sFilename.assign(&ptr[i + 1]);
            break;
        }
    }
    
    return sFilename;
}
    

// Devolve a path: AAAAAAA/BBBBBB/CCCCCCC devolve AAAAAAA/BBBBBB
PK_String PK_Path::GetPathName(const PK_String & sPath)
{
    PK_String sPathName = sPath;
    PK_String sNormalized = NormalizePath(sPath);
    char * ptr = (char *)sNormalized.c_str();
    for(int i = (int)sPath.length() - 1; i >=0; i--)
    {
        if (ptr[i] == PK_PATH_SEPARATOR[0])
        {
            ptr[i] = '\0';
            sPathName.assign(ptr);
            break;
        }
    }
    
    return sPathName;
}

// Normaliza a path
PK_String PK_Path::NormalizePath(const PK_String & sPath)
{
    PK_String sAuxPath = sPath;
    
    std::replace(sAuxPath.begin(), sAuxPath.end(), '\\', PK_PATH_SEPARATOR[0]);
    std::replace(sAuxPath.begin(), sAuxPath.end(), '/', PK_PATH_SEPARATOR[0]);
    
    return sAuxPath;
}

// Adiciona uma extensao a um nome de um ficheiro (o nome do ficheiro pode conter a path)
PK_String PK_Path::CombineExtension(const PK_String & sFilename, const PK_String & sExtension)
{
    PK_String sRet;
    
    return sFilename + PK_EXTENSION_SEPARATOR + sExtension;
}
    
// Verifica se uma path/nome de ficheiro contem extensao
bool PK_Path::ContainsExtension(const PK_String & sPath)
{
	return (sPath.find(".") != std::string::npos);
}

// Concatecna uma path com um filename
PK_String PK_Path::Combine(const PK_String & sPath, const PK_String & sFilename)
{
    PK_String sRet = PK_Path::NormalizePath(sPath);
    if (sRet[sRet.length()- 1] != PK_PATH_SEPARATOR[0])
    {
        sRet += PK_PATH_SEPARATOR;
    }
    sRet += sFilename;

    return sRet;
    
}

// static 
// Cria uma folder, ou a path completa de folders
void PK_Path::CreateFolder(const PK_String &sPath)
{
    if (sPath.length() == 0)
    {
        throw PK_SystemException("Directory to be created cannot be and empty string.", __FILE__, __LINE__);
    }
#if defined POKE_WINDOWS
    PK_List<PK_String> notExistingFolders;
    PK_String auxPath = sPath;
    while(auxPath.length() != 0)
    {
        if (!PK_Path::Exists(auxPath))
        {
            notExistingFolders.Add(PK_String(auxPath));
        }
        else
        {
            break;
        }
        auxPath.ExtractLastWord(PK_PATH_SEPARATOR);
    }

    for(PK_ListIterator(PK_String) itor = notExistingFolders.End(); itor != notExistingFolders.Begin(); )
    {
        --itor;
        int rc = CreateDirectory((*itor).c_str(), NULL);
        if (rc == 0)
        {
            // FIXME - mostrar a mensagem de erro do windows e nao apenas o codigo
            throw PK_SystemException("Error creating folder '%s', error code was '%d'", 
                            __FILE__, __LINE__, sPath.c_str(), GetLastError());
        }
    }

#else
    throw PK_NotImplementedException("PK_Path::CreateFolder()" , __FILE__, __LINE__);
#endif
}
 
// static
void PK_Path::GetFiles(PK_List<PK_String> &retFiles, PK_String sPath, PK_String sFilespec, bool bSubfolders, bool bFullpath, bool bClearList)
{
    sPath = NormalizePath(sPath);
    if (bClearList)
    {
        retFiles.Clear();
    }

#if defined POKE_WINDOWS
    if (sFilespec == "")
    {
        sFilespec = "*";
    }

    WIN32_FIND_DATA ffd;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError=0;

    hFind = FindFirstFile(PK_Path::Combine(sPath, sFilespec).c_str(), &ffd);
    if (INVALID_HANDLE_VALUE == hFind) 
    {
        return;
    } 
   
    do
    {
        if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            PK_String filename = ffd.cFileName;
            if (bFullpath)
            {
                filename = PK_Path::Combine(sPath, filename);
            }
            retFiles.Add(filename);
        }
    }
    while (FindNextFile(hFind, &ffd) != 0);
 
    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES) 
    {
        PK_Log::WriteInfo(PK_LOG_TAG, "Error in FindNextFile() GetLastError()=%d.", GetLastError());
    }

    FindClose(hFind);

    if (bSubfolders)
    {
        PK_List<PK_String> folders;
        PK_Path::GetFolders(folders, sPath);
        for(PK_ListIterator(PK_String) itor = folders.Begin(); itor != folders.End(); itor++)
        {
            PK_String subFolder = PK_Path::Combine(sPath, (*itor));
            GetFiles(retFiles, subFolder, sFilespec, bSubfolders, bFullpath, false);
        }
    }

#else
    throw PK_NotImplementedException("PK_Path::GetFiles()" , __FILE__, __LINE__);
#endif
}

// static
void PK_Path::GetFolders(PK_List<PK_String> &retFolders, PK_String sPath)
{
    sPath = PK_Path::Combine(NormalizePath(sPath), "*.*");
    
    retFolders.Clear();

#if defined POKE_WINDOWS
    WIN32_FIND_DATA ffd;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError=0;

    hFind = FindFirstFile(sPath.c_str(), &ffd);
    if (INVALID_HANDLE_VALUE == hFind) 
    {
        return;
    } 
   
    do
    {
        if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            if (strcmp(ffd.cFileName, ".") &&
                strcmp(ffd.cFileName, ".."))
            {
                retFolders.Add(ffd.cFileName);
            }
        }
    }
    while (FindNextFile(hFind, &ffd) != 0);
 
    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES) 
    {
        PK_Log::WriteInfo(PK_LOG_TAG, "Error in FindNextFile() GetLastError()=%d.", GetLastError());
    }

    FindClose(hFind);
#else
    throw PK_NotImplementedException("PK_Path::GetFiles()" , __FILE__, __LINE__);
#endif
}
//static 
bool PK_Path::Exists(const PK_String & sPath)
{
#if defined POKE_WINDOWS
    DWORD dwAttrib = GetFileAttributes(NormalizePath(sPath).c_str());

  return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
         (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#else
    throw PK_NotImplementedException("PK_Path::Exists()" , __FILE__, __LINE__);
#endif
}

// static 
PK_String PK_Path::GetPathDelimiter()
{
    return PK_PATH_SEPARATOR;
}

} // namespace
