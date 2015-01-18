#ifndef _PK_SETTINGSASSET_H_
#define _PK_SETTINGSASSET_H_

#include "PK_ObjectPropertiesAsset.h"

namespace PK {
    
// Guarda uma textura
class PK_SettingsAsset : public PK_ObjectPropertiesAsset
{
public:
    PK_SettingsAsset(PK_AssetContainer &assetContainer) :
      PK_ObjectPropertiesAsset(assetContainer, PK_SETTINGS_EXTENSION)
    {
    }
};

} // namespace

#endif