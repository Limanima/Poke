#include "PK_Globals.h"
#include "PK_Consts.h"
#include "PK_Config.h"
#include "PK_Exceptions.h"
#include "PK_TextureAsset.h"
#include "PK_FontAsset.h"
#include "PK_DataFiles.h"
#include "PK_Path.h"
#include "PK_Log.h"

// <Font ImageId="images/fonts-1">
//   <Characters SpaceWidth="8" BetweenCharsWidth="-2" LineHeight="45">
//     <Character CharMap="!" Rect="10, 582, 7, 21" Spacing="0" SpacingAfter="0" />
//     <Character CharMap="&quot;" Rect="10, 582, 7, 21" Spacing="0" SpacingAfter="0" />
//     <Character CharMap="#" Rect="10, 582, 7, 21" Spacing="0" SpacingAfter="0" />
//     <Character CharMap="$" Rect="10, 582, 7, 21" Spacing="0" SpacingAfter="0" />
// ...
// </Font>

namespace PK {

PK_FontAsset::PK_FontAsset(PK_AssetContainer &assetContainer):
	PK_Asset(AssetType_Font, assetContainer)
{
    SetTypeName("PK_FontAsset");
    m_pTexture = NULL;
    m_pChars = NULL;
}

PK_FontAsset::~PK_FontAsset()
{
  Unload();
}

//
void PK_FontAsset::Unload()
{
  if (m_pTexture != NULL)
  {
    m_pTexture->Release();
    m_pTexture = NULL;
  }

  if (m_pChars != NULL)
  {
    delete [] m_pChars;
    m_pChars = NULL;
  }
  m_bLoaded = false;
}
    
//
void PK_FontAsset::Load()
{
if (m_bLoaded)
    {
        throw PK_SystemException("Asset named '%s' is already loaded.", __FILE__, __LINE__, GetName().c_str());
    }

    PK_String sFilename = GetAssetName();
    if (!PK_Path::ContainsExtension(sFilename))
    {
        sFilename = PK_Path::CombineExtension(GetAssetName(), PK_FONT_EXTENSION);
    }
    
    PK_DataFile df;
    df.LoadFromXML(sFilename);
    PK_DataFileRecord *pRoot = df.GetRoot();
    if (pRoot == NULL)
    {
        throw PK_SystemException("Could not load Font named %s because there's no root record.", __FILE__, __LINE__, sFilename.c_str());
    }
    InitFromDataFileRecord(*pRoot);
    m_bLoaded = true;
}
     
// 
void PK_FontAsset::InitFromDataFileRecord(PK_DataFileRecord & record)
{
    Unload();
    m_pChars = new PK_tFontChar[NUM_CHARS];
    for (int i = 0; i < NUM_CHARS; i++)
    {
        m_pChars[i].chChar = (char)i;
        m_pChars[i].frame.bsRect.Set(0, 0, 0, 0);
        memset(m_pChars[i].frame.textCoords, 0, sizeof(m_pChars[i].frame.textCoords));
        m_pChars[i].iSpacing = 0;
        m_pChars[i].iSpacingAfter = 0;
        m_pChars[i].size.Set(0,0);
    }
    
    SetName(record.GetFieldValue_String("Name"));
    m_iSpaceWidth = record.GetFieldValue_Int("SpaceWidth");
    m_iSpacing = record.GetFieldValue_Int("Spacing");

    // Textura
    m_sImageAssetName = record.GetFieldValue_String("ImageId");
    m_pTexture = PokeEngine.GetAssetManager().LoadTexture(m_sImageAssetName, m_pAssetContainer->GetName());
    m_pTexture->Grab();

    // Chars
    PK_List<PK_DataFileRecord *> charRecs;
    record.SelectRecords("Characters/Character", charRecs, false);
    
     for(PK_ListIterator(PK_DataFileRecord *) itor = charRecs.Begin(); itor != charRecs.End(); itor++)
    {
      PK_DataFileRecord *pCharRec = (*itor);
      PK_String ch = pCharRec->GetFieldValue_String("CharMap");

      if (ch.length() > 0 && (int)ch[0] < NUM_CHARS)
      {
          unsigned char k = (int)ch[0];
          m_pChars[k].chChar = k;
          m_pChars[k].frame.bsRect = pCharRec->GetFieldValue_AABoundingSquare("Rect").ToBoundingSquare();
          m_pChars[k].iSpacing = pCharRec->GetFieldValue_Int("Spacing");
          m_pChars[k].iSpacingAfter = pCharRec->GetFieldValue_Int("SpacingAfter");
          m_pChars[k].size.Set(m_pChars[k].frame.bsRect.GetWidth(), m_pChars[k].frame.bsRect.GetHeight());
          m_pChars[k].frame.bsRect.ToTextureCoords(m_pTexture->GetSize(), m_pChars[k].frame.textCoords);

		  #if defined(PK_USEVERTEXBUFFERS)
		  m_pChars[k].frame.FrameRenderData = &PokeEngine.GetRenderManager().CreateTextureShaderPrimitiveData(m_pChars[k].frame.bsRect, m_pChars[k].frame.textCoords);
		  #endif
      }

    }
}
    
//
PK_tSize PK_FontAsset::MeasureString(const PK_String &sText)
{
    float w = 0, h = 0;
    
    for(unsigned int i= 0; i < sText.length(); i++)
    {
        if (sText[i] != ' ')
        {
            PK_tFontChar *pChar = &m_pChars[sText[i]];
            w += pChar->size.w;
            if (pChar->size.h > h)
            {
                h = pChar->size.h;
            }
            if (i == sText.length() - 1)
            {
                break;
            }
            w += pChar->iSpacing +GetSpacing();
        }
        else
        {
             w += GetSpaceWidth();
        }
    }
    
    return PK_tSize(w, h);
}
    
} // namespace
