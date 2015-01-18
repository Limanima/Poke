#include "PK_Consts.h"
#include "PK_Globals.h"
#include "PK_Label.h"
#include "PK_Scripting.h"
#include "PK_tScriptVariable.h"
#include "PK_Config.h"

namespace PK {

//
PK_Label::PK_Label(const PK_String &sName) :
  PK_2DSceneControl(sName)
{
    InitializeInstance("");
}

//
PK_Label::PK_Label(const PK_String &sName, const PK_String &sText) :
  PK_2DSceneControl(sName)
{
    InitializeInstance(sText);
}

//
void PK_Label::InitializeInstance(const PK_String &sText)
{
    SetTypeName("PK_Label");
    m_pFont = NULL;
    m_RefreshFlags = LabelRefreshFlags_None;
    SetText(sText);
    SetAutoSize(true);
    m_textSize.Set(0, 0);
    m_Border.Set(0, 0, 0, 0);
}

//
PK_Label::~PK_Label()
{
    FreeResources();
}

//
void PK_Label::FreeResources()
{
    if ( m_pFont != NULL)
    {
        m_pFont->Release();
        m_pFont = NULL;
    }
    m_RefreshFlags = LabelRefreshFlags_None;
}

//
void PK_Label::InitFromDataFileRecord(PK_DataFileRecord &record)
{
    PK_2DSceneControl::InitFromDataFileRecord(record);
    SetFont(record.GetChildRecordFieldValue_String("font", "value", ""));
}

//
void PK_Label::InternalLoad()
{ 
    LoadFont();
    PK_2DSceneControl::InternalLoad();
}

//
void PK_Label::InternalUnload()
{
    FreeResources();
    PK_2DSceneControl::InternalUnload();
}

//
void PK_Label::InternalDraw()
{
    PK_2DSceneControl::InternalDraw();
    if (m_pFont == NULL || m_sText.length() == 0 || m_pFont->GetTexture() == NULL)
    {
        return;
    }

    
    PK_tBoundingSquare bsDest;
    float x = -(m_textSize.w / 2);
    float y = -(m_textSize.h / 2);
    // PERFORMANCE: Isto pode ser melhorado, nao precisa de estar sempre a ser calculado
    for(int i= 0; (i < (int)m_sText.length()); i++)
    {
        if (m_sText[i] != ' ')
        {
            PK_tFontChar *pChar = m_pFont->GetChar(m_sText[i]);
            PK_Matrix3 mat = *GetTransformMatrix();
            mat *= glm::translate(-GetPivot());
#if defined (PK_USEVERTEXBUFFERS)
			PokeEngine.GetRenderManager().RenderImage(*pChar->frame.FrameRenderData, *m_pFont->GetTexture(), GetBlendedColor(), mat);
#else
            bsDest.Set(x, y, pChar->size.w, pChar->size.h);
            bsDest.TransformInPlace(mat);            
			PokeEngine.GetRenderManager().RenderImage(pChar->frame, bsDest, *m_pFont->GetTexture(), GetBlendedColor());
#endif
            x += pChar->size.w + pChar->iSpacing + m_pFont->GetSpacing();
        }
        else
        {
            x += m_pFont->GetSpaceWidth();
        }

    }
}
    
//
void PK_Label::LoadFont()
{
    if (m_sFontAssetName.length() > 0)
    {
        SetFont(PokeEngine.GetAssetManager().LoadFont(m_sFontAssetName, GetAssetContainerName()));
    }
    else
    {
        SetFont(NULL);
    }
}
    
//
void PK_Label::UpdateLayout()
{
    if (m_RefreshFlags != LabelRefreshFlags_None)
    {
        if (m_RefreshFlags & LabelRefreshFlags_Font)
        {
            UpdateFont();
        }
        
        if (m_RefreshFlags & LabelRefreshFlags_Size)
        {
            UpdateSize();
        }
        m_RefreshFlags = LabelRefreshFlags_None;
    }
    PK_2DSceneControl::UpdateLayout();
}
    
//
void PK_Label::UpdateFont()
{
    if (m_sFontAssetName.length() > 0)
    {
        LoadFont();
    }

    m_RefreshFlags &= ~LabelRefreshFlags_Font;
}
    
//
void PK_Label::UpdateSize()
{
    if (m_pFont != NULL)
    {
        // FIXME
        // Com bordas nao e bem assim. Tem que mexer com o pivot tambem
        PK_tSize size = m_textSize;
        size.w += m_Border.left + m_Border.right; 
        size.h += m_Border.top + m_Border.bottom;
        SetSize(size);
    }
    m_RefreshFlags &= ~LabelRefreshFlags_Size;
    
}   
   
//
void PK_Label::SetCustomAttribute(const PK_String &sName, PK_tScriptValue1 &var)
{
    PK_2DSceneControl::SetCustomAttribute(sName, var);
    if (sName == "text")
    {
        SetText(var.GetValue_Str());
    }
}
 
//
void PK_Label::SetFont(const PK_String &sAssetName)
{
    if (sAssetName != m_sFontAssetName)
    {
        m_sFontAssetName = sAssetName;
        m_RefreshFlags |= LabelRefreshFlags_Font;
    }
}


//
void PK_Label::SetFont(PK_FontAsset *pFont)
{
    if(pFont == m_pFont)
    {
        return;
    }

    if (m_pFont != NULL)
    {
        m_pFont->Release();
    }
    m_pFont = pFont;
    if (pFont != NULL)
    {
        m_pFont->Grab();
        m_textSize = m_pFont->MeasureString(m_sText);
    }
    if (GetAutoSize() == true)
    {
        m_RefreshFlags |=  LabelRefreshFlags_Size;
    }

}
     
//
void PK_Label::SetText(const PK_String &sText)
{
   if (m_sText != sText)
   {
       m_sText = sText;
       if (GetAutoSize())
       {
            m_RefreshFlags |=  LabelRefreshFlags_Size;
       }
       if (m_pFont != NULL)
       {
            m_textSize = m_pFont->MeasureString(m_sText);
       }
   }
}

//
void PK_Label::SetText(int iText)
{
   PK_String str;
   str.Format("%d", iText);
   SetText(str);
}
} // namespace
