#ifndef _PK_FILEASSET_H_
#define _PK_FILEASSET_H_

#include "PK_Asset.h"
#include "PK_String.h"
#include "PK_Array.h"
#include "PK_MemoryBuffer.h"

namespace PK {

class PK_AssetContainer;
class PK_DataFileRecord;

// 
class PK_FileAsset : public PK_Asset
{
protected:
	PK_MemoryBuffer m_data;

public:
	PK_FileAsset(PK_AssetContainer &assetContainer);
	~PK_FileAsset();
    void Load();
	void Unload();
    inline PK_MemoryBuffer & GetData() { return m_data; }
};

} // namespace

#endif