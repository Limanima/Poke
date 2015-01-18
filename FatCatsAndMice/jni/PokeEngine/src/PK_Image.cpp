#include "PK_Consts.h"
#include "PK_Globals.h"
#include "PK_Image.h"

namespace PK {

PK_Image::PK_Image(const PK_String &sName) :
    PK_2DSceneControl(sName)
{
	SetTypeName("PK_Image");
    m_pTexture = NULL;
}

PK_Image::~PK_Image()
{
    OnUnload();
}

//
void PK_Image::InitFromDataFileRecord(PK_DataFileRecord &record)
{
    PK_2DSceneControl::InitFromDataFileRecord(record);
}

void PK_Image::OnLoad()
{ 
    if (m_sTextureAssetName.length() > 0)
    {
        PK_String sContainerName = GetAssetContainerName();
        SetTexture(PokeEngine.GetAssetManager().LoadTexture(m_sTextureAssetName, sContainerName));
    }
}

//
void PK_Image::OnUnload()
{
    SetTexture(NULL);
}

//
void PK_Image::OnDraw()
{
    if (m_pTexture == NULL)
    {
        return;
    }
    PokeEngine.GetRenderManager().RenderImage(GetClientRect(), m_pTexture, GetColor());
}
    
//
void PK_Image::SetTexture(PK_TextureAsset *pTexture)
{
    if (m_pTexture != NULL)
    {
        m_pTexture->Release();
    }

    m_pTexture = pTexture;
    if (m_pTexture != NULL)
    {
        m_pTexture->Grab(); 
        // Ajustar o tamanho do controlo a textura
        SetSize(m_pTexture->GetSize());
    }

}

} // namespace
