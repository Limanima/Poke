#ifndef _PK_LABEL_H_
#define _PK_LABEL_H_

#include "PK_String.h"
#include "PK_2DSceneControl.h"
#include "PK_FontAsset.h"

namespace PK {

enum PK_eLabelRefreshFlags
{
    LabelRefreshFlags_None = 0x00,
    LabelRefreshFlags_Font = 0x01,
    LabelRefreshFlags_Size = 0x02
};
    
class PK_Label : public PK_2DSceneControl
{

private:
    PK_String     m_sText;
    PK_String     m_sFontAssetName;
    PK_FontAsset *m_pFont;
    int           m_RefreshFlags;
    PK_tSize      m_textSize;
    bool          m_bAutosize;
    PK_tMargins   m_Border; // espaco de borda a aplicar quando ha autosize

public:
    PK_Label(const PK_String &sName = "");
    PK_Label(const PK_String &sName, const PK_String &sText);
    ~PK_Label();
    void FreeResources();

private:
    void InitializeInstance(const PK_String &sText);

public:
    void InitFromDataFileRecord(PK_DataFileRecord &record);
    void InternalLoad();
    void InternalDraw();
    void InternalUnload();
    void UpdateLayout();
    void LoadFont();
    void UpdateFont();
    void UpdateSize();
    virtual void SetCustomAttribute(const PK_String &sName, PK_tScriptValue1 &var);


public:
    // Font
    void SetFont(const PK_String &sAssetName);
    void SetFont(PK_FontAsset *pFont);     // Aceita nulo, para remover a font
    PK_FontAsset * GetFont();
    
    // Texto
    void SetText(const PK_String &sText);
    void SetText(int iText);
    
    // Border
    inline PK_tMargins GetBorder() { return m_Border; }
    inline void SetBorder(float border)
    {
        SetBorder(PK_tMargins(border, border, border, border));
    }
    inline void SetBorder(float left, float top, float right, float bottom)
    {
        SetBorder(PK_tMargins(left, top, right, bottom));
    }
    inline void SetBorder(const PK_tMargins &border)
    {
        if (m_Border != border)
        {
            m_Border = border;
            m_RefreshFlags |= LabelRefreshFlags_Size;
        }
    }

    inline PK_String GetText() { return m_sText; }
    inline void SetAutoSize(bool bAutosize) { m_bAutosize = bAutosize; } 
    inline bool GetAutoSize() { return m_bAutosize; }
};

}

#endif
