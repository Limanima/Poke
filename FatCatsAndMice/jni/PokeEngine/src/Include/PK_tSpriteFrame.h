#ifndef __PK_TSPRITEFRAME_H__
#define __PK_TSPRITEFRAME_H__

#include "PK_DataFileRecord.h"
#include "PK_tBoundingSquare.h"
#include "PK_Vector2.h"
#include "PK_Vector2.h"
namespace PK {

struct PK_tPrimitiveData;

// Estrutura para guardar um frame
struct PK_tSpriteFrame
{
    static const int LL_IDX = 0;
    static const int UL_IDX = 1;
    static const int UR_IDX = 2;
    static const int LR_IDX = 3;

    // FrameSource eh o frame dentro da textura
    PK_tAABoundingSquare m_bsFrameSource;
    // Frame e o frame com origem 0 no ponto LL (utilizado no render)
    PK_tBoundingSquare m_bsFrame;
    unsigned int       m_uiPlayingTime;
    // Precalcular as coordenadas de textura, utilizado no rendering
    PK_Vector2         m_vTexCoords[4];

	PK_tPrimitiveData  *m_pFrameRenderData;

    PK_tSpriteFrame();
    void InitializeTextureCoords(const PK_tSize &textureSize);
    
    void InitFromDataFileRecord(PK_DataFileRecord & record);
    PK_DataFileRecord * ToDataFileRecord();
    
    // Temos que fazer overloading do operador =
    // Isto porque temos que copiar os vertices
    PK_tSpriteFrame & operator=(const PK_tSpriteFrame & frame)
    {
        for(int i = 0; i< 4; i++)
        {
            m_vTexCoords[i] = frame.m_vTexCoords[i];
        }
        m_bsFrame = frame.m_bsFrame;
        m_bsFrameSource = frame.m_bsFrameSource;
        m_uiPlayingTime = frame.m_uiPlayingTime;
		m_pFrameRenderData = frame.m_pFrameRenderData;
        return *this;
    }
};

} // Namespace
#endif
