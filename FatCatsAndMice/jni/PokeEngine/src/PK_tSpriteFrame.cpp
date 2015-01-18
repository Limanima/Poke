#include "PK_tSpriteFrame.h"
#include "PK_Exceptions.h"
#include "PK_Config.h"
#include "PK_Globals.h"

// Format DataFile de tSpriteFrame
// (para jah para manter compatibilidade com o Sprite Animation Studio
// <Frame Left="360" Top="0" Width="45" Height="45" PlayTime="6000" OffsetX="0" OffsetY="0" Rotation="0" PivotX="0" PivotY="0" />
namespace PK
{
PK_tSpriteFrame::PK_tSpriteFrame()
{
	m_uiPlayingTime = 0;
	m_pFrameRenderData = NULL;
}

// Inicializa as coordenadas de textura. Estas coordenadas sao utilizados no render do frame
// representam o rect na textura a que corresponde o frame. Eh fixo, por isso pode ser preh calculado
void PK_tSpriteFrame::InitializeTextureCoords(const PK_tSize &textureSize)
{
    m_vTexCoords[LL_IDX] = PK_Vector2(m_bsFrameSource.GetLL().x / textureSize.w, m_bsFrameSource.GetLL().y / textureSize.h);
    m_vTexCoords[UL_IDX] = PK_Vector2(m_bsFrameSource.GetUL().x / textureSize.w, m_bsFrameSource.GetUL().y / textureSize.h);
    m_vTexCoords[UR_IDX] = PK_Vector2(m_bsFrameSource.GetUR().x / textureSize.w, m_bsFrameSource.GetUR().y / textureSize.h);
    m_vTexCoords[LR_IDX] = PK_Vector2(m_bsFrameSource.GetLR().x / textureSize.w, m_bsFrameSource.GetLR().y / textureSize.h);

#if defined(PK_USEVERTEXBUFFERS)
	m_pFrameRenderData = &PokeEngine.GetRenderManager().CreateTextureShaderPrimitiveData(m_bsFrame, m_vTexCoords);
#endif
}
    
//
void PK_tSpriteFrame::InitFromDataFileRecord(PK_DataFileRecord & record)
{

    // Rect dentro da textura
    m_bsFrameSource = record.GetFieldValue_AABoundingSquare("Rect");
    int w = (int)m_bsFrameSource.size.w;
    int h = (int)m_bsFrameSource.size.h;    // Rect usado no draw (origem no centro do frame)
    // Cast (float)(int) para que os frames tenham valores inteiros
    m_bsFrame.Set((float)(int)(-w / 2), (float)(int)(-h / 2), (float)w, (float)h);
    m_uiPlayingTime = record.GetFieldValue_Int("PlayTime");

}
    
//
PK_DataFileRecord * PK_tSpriteFrame::ToDataFileRecord()
{
    PK_DataFileRecord * pRecord = new PK_DataFileRecord("size");
    PK_CHECK_OBJECT_ALLOC(PK_DataFileRecord, pRecord);
    
    pRecord->AddField("Left", (int)m_bsFrame.GetX());
    pRecord->AddField("Top", (int)m_bsFrame.GetY());
    pRecord->AddField("Width", (int)m_bsFrame.GetWidth());
    pRecord->AddField("Height", (int)m_bsFrame.GetHeight());
    pRecord->AddField("PlayTime", (int)m_uiPlayingTime);
    
    return pRecord;
}

} // namespace
