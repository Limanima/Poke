#ifndef _PK_FONTASSET_H_
#define _PK_FONTASSET_H_

#include "PK_DataFileAsset.h"
#include "PK_Array.h"
#include "PK_tBoundingSquare.h"
#include "PK_Types.h"

namespace PK {
    
class PK_DataFileRecord;
class PK_TextureAsset;

struct PK_tFontChar
{
    char     chChar;
    short    iSpacing;
    short    iSpacingAfter;
    PK_tSize size; // Guardar logo o size no loading, como nao muda mais vale ter isto pre-calculado para nao fazer contas
    PK_tTextureFrame frame;
};

class PK_FontAsset : public PK_Asset
{

private:
    static const int NUM_CHARS = 256;
    PK_String              m_sImageAssetName;
    PK_TextureAsset      * m_pTexture;
    PK_tFontChar         * m_pChars;
    int                    m_iSpaceWidth;
    int                    m_iSpacing;

public:
    PK_FontAsset(PK_AssetContainer &assetContainer);
    ~PK_FontAsset();
    void Unload();
    void Load();
    
private:
    void InitFromDataFileRecord(PK_DataFileRecord & record);

public:
    PK_tSize MeasureString(const PK_String &text);
    // Textura
    inline PK_TextureAsset * GetTexture() { return m_pTexture; }
    // Char array
    inline PK_tFontChar * GetChars() { return m_pChars; }
    // Single char
    inline PK_tFontChar * GetChar(char ch) { return &m_pChars[ch]; }
    // Space width
    inline int GetSpaceWidth() { return m_iSpaceWidth; }
    // Spacing
    inline int GetSpacing() { return m_iSpacing; }
};

} // namespace

#endif
