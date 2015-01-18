#ifndef _PK_ASSET_H_
#define _PK_ASSET_H_

#include "PK_String.h"
#include "PK_Object.h"
#include "PK_Types.h"

namespace PK {
    
class PK_AssetContainer;
    
// Classe base para um asset: textura, sprite, font, etc
class PK_Asset : public PK_Object
{
private:
	PK_eAssetType    m_Type;
    PK_String        m_sAssetName;
    
protected:
    PK_AssetContainer   *m_pAssetContainer;
    bool                 m_bLoaded;

public:
	PK_Asset(PK_eAssetType type, PK_AssetContainer &assetContainer);
	~PK_Asset();

    // Load e chamado apos o preload a partir da queue de loading
	virtual void Load() = 0;
    virtual void Unload() {};
	inline PK_eAssetType GetAssetType() { return m_Type; }
    inline bool IsLoaded() const { return m_bLoaded; }
    inline void SetAssetName(const PK_String &sName) { m_sAssetName = sName; }
    inline PK_String GetAssetName() { return m_sAssetName; }
};

} // namespace

#endif