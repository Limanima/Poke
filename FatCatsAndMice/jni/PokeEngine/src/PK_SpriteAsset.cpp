#include "PK_Consts.h"
#include "PK_Exceptions.h"
#include "PK_SpriteAsset.h"
#include "PK_SpriteSetAsset.h"
#include "PK_TextureAsset.h"

// Formato DataFile
//
//<Sprite Name="Apple" Fps="12" OffsetX="23" OffsetY="23" Width="45" Height="45" ParentAnimationId="">
//  <Frames>
//    <Frame Rect="0, 0, 45, 45" PlayTime="0" OffsetX="0" OffsetY="0" Rotation="0" PivotX="0" PivotY="0" />
//    <Frame Rect="45, 0, 45, 45" PlayTime="0" OffsetX="0" OffsetY="0" Rotation="0" PivotX="0" PivotY="0" />
//  </Frames>
//</Sprite>

namespace PK {

PK_SpriteAsset::PK_SpriteAsset(PK_AssetContainer &assetContainer, PK_SpriteSetAsset &spriteSet):
	PK_Asset(AssetType_Sprite, assetContainer)
{
    SetTypeName("PK_SpriteAsset");
	m_uiFps = 12;
    m_pSpriteSet = &spriteSet;
    m_pSpriteSet->Grab();
}

PK_SpriteAsset::~PK_SpriteAsset()
{
	Unload();
}

// Libertar todos os recursos 
void PK_SpriteAsset::Unload()
{
    m_Frames.Clear();
    m_CollisionBoxes.Clear();
    if (m_pSpriteSet != NULL)
    {
        m_pSpriteSet->Release();
        m_pSpriteSet = NULL;
    }
}

//
void PK_SpriteAsset::Load()
{
    for(int i = 0; i < m_Frames.GetCount(); i++)
    {
        m_Frames[i].InitializeTextureCoords(GetTexture()->GetSize());
    }
}
    
// Inicializa um Sprite a partir de um DataFile
void PK_SpriteAsset::InitFromDataFileRecord(PK_DataFileRecord & record)
{
    SetName(record.GetFieldValue_String("Name"));
    m_uiFps = record.GetFieldValue_Int("Fps");
    m_Size = record.GetFieldValue_Size("Size");
    m_vPivot = record.GetFieldValue_Vector2("Pivot", PK_Vector2(0.0f, 0.0f));

    // Frames
    PK_List<PK_DataFileRecord *> frameRecords;
    record.SelectRecords("Frames/Frame", frameRecords, false);
    if (frameRecords.GetCount() > 0)
    {
        m_Frames.Clear();
        m_Frames.SetSize(frameRecords.GetCount());
        int i = 0;
       	for(PK_ListIterator(PK_DataFileRecord *) itor = frameRecords.Begin(); itor != frameRecords.End(); itor++)
        {
            PK_tSpriteFrame frm;
            frm.InitFromDataFileRecord(*(*itor));
            m_Frames[i] = frm;
            i++;
        }
    }
    // BoundingSquares
    PK_List<PK_DataFileRecord *> collisionBoxRecords;
    record.SelectRecords("ColisionZones/BoundingBox", collisionBoxRecords, false);
    if (collisionBoxRecords.GetCount() > 0)
    {
        m_CollisionBoxes.Clear();
        m_CollisionBoxes.SetSize(collisionBoxRecords.GetCount());
        int i = 0;
       	for(PK_ListIterator(PK_DataFileRecord *) itor = collisionBoxRecords.Begin(); itor != collisionBoxRecords.End(); itor++)
        {
            m_CollisionBoxes[i] = (*itor)->GetFieldValue_AABoundingSquare("Rect");
            i++;
        }
    }
}

//
PK_tAABoundingSquare PK_SpriteAsset::GetCollisionBox(unsigned int idx)
{
    if (m_CollisionBoxes.GetCount() <= (int)idx)
    {
        throw PK_SystemException("Cannot retrieve collision box with index '%d' from Sprite Asset named '%s' because it's out of the bounds of the collision box array.", 
            __FILE__, __LINE__, idx, GetName().c_str());
    }
    return m_CollisionBoxes[idx];
}
    
} // namespace
