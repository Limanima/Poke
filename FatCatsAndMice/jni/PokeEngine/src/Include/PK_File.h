#ifndef __PK_FILE_H__
#define __PK_FILE_H__

#include "PK_String.h"
#include "PK_FileCopyCallback.h"

namespace PK {

class PK_File
{
public:
    static bool Exists(const PK_String & sfile);
    static bool ContainsWildcards(const PK_String & sSourceFilename);
    static void Copy(const PK_String & sSourceFilename, const PK_String & sDestFilename, bool bOverwrite=false);
    static void CopyMultiple(PK_String sSourceFolder, PK_String sDestFolder, const PK_String & sFileSpec, bool bCopyTree=true, bool bOverwrite=false, PK_Callback<PK_IFileCopyCallback> *pCopyCallback = NULL);
};

} // Namespace
#endif
