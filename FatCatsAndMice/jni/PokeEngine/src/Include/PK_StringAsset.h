#ifndef _PK_STRINGASSET_H_
#define _PK_STRINGASSET_H_

#include "PK_Asset.h"
#include "PK_Dictionary.h"


namespace PK {

// 
class PK_StringAsset : public PK_Asset
{
protected:
	PK_Dictionary<PK_String, PK_String> m_strings;

public:
	PK_StringAsset(PK_AssetContainer &assetContainer);
	~PK_StringAsset();
    void Load();
	void Unload();
    void InitFromDataFileRecord(PK_DataFileRecord & record);
    PK_String GetString(const PK_String &stringId);
};

} // namespace

#endif