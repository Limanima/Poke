#ifndef __PK_PATH_H__
#define __PK_PATH_H__

#include "PK_String.h"

namespace PK {

class PK_Path
{
public:
    static PK_String GetFileName(const PK_String & sPath);
    static PK_String GetPathName(const PK_String & sPath);
    static PK_String NormalizePath(const PK_String & sPath);
    static PK_String CombineExtension(const PK_String & sFilename, const PK_String & sExtension);
    static PK_String Combine(const PK_String & sPath, const PK_String & sFilename);
    static bool ContainsExtension(const PK_String & sPath);
    static void CreateFolder(const PK_String & sPath);
    static void GetFiles(PK_List<PK_String> &retFiles, PK_String sPath, PK_String sFilespec = "", bool bSubfolders = false, bool bFullpath = false, bool bClearList = true);
    static void GetFolders(PK_List<PK_String> &retFolders, PK_String sPath);
    static bool Exists(const PK_String & sPath);
    static PK_String GetPathDelimiter(); 
};

} // Namespace
#endif
