#ifndef _PK_DATAFILEASSET_H_
#define _PK_DATAFILEASSET_H_

#include "PK_Asset.h"
#include "PK_DataFiles.h"

namespace PK {
    
class PK_DataFileAsset : public PK_Asset
{
private:
    PK_DataFileRecord * m_pRootRecord;
    PK_String           m_sAssetExtension;
    
public:
    PK_DataFileAsset(PK_eAssetType type, PK_AssetContainer &assetContainer, const PK_String &sExtension);
    ~PK_DataFileAsset();
    void FreeResources();
    virtual void Load();
    PK_DataFileRecord * GetRecord(const PK_String &sRecord);
    inline PK_DataFileRecord * GetRootRecord() { return m_pRootRecord; }
};

} // namespace

#endif
