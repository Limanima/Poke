#include "PK_Consts.h"
#include "PK_Config.h"
#include "PK_Assert.h"
#include "PK_Globals.h"
#include "PK_Exceptions.h"
#include "PK_2DSceneControl.h"
#include "PK_Scene.h" 
#include "PK_Color.h"
#include "PK_Vector2.h" 
#include "PK_InputManager.h"
#include "PK_tAABoundingSquare.h"
#include "PK_SpriteAsset.h"
#include "PK_TypeConverters.h"
#include "PK_EffectsBlender.h"
#include "PK_Body.h"
#include "PK_PhysicsManager.h"
#include "PK_Log.h"
#include "PK_tPrimitiveData.h"

#define DEFAULT_SIZE             PK_tSize(100.0f, 100.0f)
#define DEFAULT_POSITION         PK_Vector2(0.0f, 0.0f)
#define DEFAULT_BKG_COLOR        PK_COLOR_TRANSPARENT
#define DEFAULT_ROTATION         0.0f
#define DEFAULT_SCALE            PK_Vector2(1.0f, 1.0f)
#define DEFAULT_PIVOT_POS        PK_Vector2(0.0f, 0.0f)
#define DEFAULT_PIVOT_ALIGN_STR  "None"
#define DEFAULT_PARENT_ALIGN_STR "None"
#define DEFAULT_DOCKING_STR      "None"
#define DEFAULT_VALUE_COLOR      PK_COLOR_WHITE

namespace PK {

//
PK_2DSceneControl::PK_2DSceneControl(const PK_String &sName) :
  PK_SceneControl(sName)
{
    SetTypeName("PK_2DSceneControl");
    m_p2DParent           = NULL;
    m_uiRefreshFlags      = RefreshFlags_None;
    m_uiChildRefreshFlags = RefreshFlags_None;
    m_matTransform        = PK_Matrix3(1.0f);
    m_uiDockStyle         = PK_TypeConverters::StrToControlDock(DEFAULT_DOCKING_STR);
    SetSize(DEFAULT_SIZE);
    m_vPosition           = m_vWorldPosition = DEFAULT_POSITION;
    m_BackgroundColor     = DEFAULT_BKG_COLOR;
    m_Color               = DEFAULT_VALUE_COLOR;
    m_BlendedColor        = DEFAULT_VALUE_COLOR;
    m_fRotation           = m_fWorldRotation = DEFAULT_ROTATION;
    m_vScale              = m_vWorldScale = DEFAULT_SCALE;
    m_vPivot              = DEFAULT_PIVOT_POS;
    m_uiPivotAligment     = PK_TypeConverters::StrToPivotAlignment(DEFAULT_PIVOT_ALIGN_STR);
    m_uiParentAlignment   = PK_TypeConverters::StrToParentAlignment(DEFAULT_PARENT_ALIGN_STR);
    m_pBackgroundSprite   = NULL;
	m_pClientRectRenderData= NULL;
    m_BackgroundImageFitMode = ImageSizeMode_RealSize;
    m_Padding.Set(0, 0, 0, 0);
    //Fisica
    m_pAttachedBody = NULL;
    m_bWithPhysics = false;
    m_bSuppressBodyTransformUpdates = false;
}

//
PK_2DSceneControl::~PK_2DSceneControl()
{
  if (WithPhysics())
  {
    DettachFromBody();
  }

  if (m_pClientRectRenderData != NULL)
  {
	delete m_pClientRectRenderData; 
  }
}


//
void PK_2DSceneControl::InitFromDataFileRecord(PK_DataFileRecord &record)
{
    PK_SceneControl::InitFromDataFileRecord(record);

    SetSize             (record.GetChildRecordFieldValue_Size("size", "value", DEFAULT_SIZE));
    SetPosition         (record.GetChildRecordFieldValue_Vector2("position", "value", DEFAULT_POSITION));
    SetBackgroundColor  (record.GetChildRecordFieldValue_Color("backgroundColor", "value", DEFAULT_BKG_COLOR));
    SetRotation         (record.GetChildRecordFieldValue_Float("rotation", "value", DEFAULT_ROTATION));
    SetScale            (record.GetChildRecordFieldValue_Vector2("scale", "value", DEFAULT_SCALE));
    SetPivot            (record.GetChildRecordFieldValue_Vector2("pivotPos", "value", DEFAULT_PIVOT_POS));

    // Pivot aligment
    PK_String sPivoAligmnent = record.GetChildRecordFieldValue_String("pivotAlignment", "value", DEFAULT_PIVOT_ALIGN_STR);
    m_uiPivotAligment    = PK_TypeConverters::StrToPivotAlignment(sPivoAligmnent);
    // Parent aligment
    PK_String sParentAligmnent = record.GetChildRecordFieldValue_String("parentAlignment", "value", DEFAULT_PARENT_ALIGN_STR);
    m_uiParentAlignment  = PK_TypeConverters::StrToParentAlignment(sParentAligmnent);
    // Dock style
    PK_String sDockStyle = record.GetChildRecordFieldValue_String("docking", "value", DEFAULT_DOCKING_STR);
    m_uiDockStyle        = PK_TypeConverters::StrToControlDock(sDockStyle);

    SetBackgroundImage(record.GetChildRecordFieldValue_String("backgroundSprite", "value", ""));
}


//
void PK_2DSceneControl::InternalLoad()
{
    if (m_sBackgroundSpriteAssetName.length() != 0)
    {
        UpdateBackgroundImage();
    }
    PK_SceneControl::InternalLoad();
}

//
void PK_2DSceneControl::InternalUnload()
{
    SetBackgroundImage(NULL);
    PK_SceneControl::InternalUnload();
}

// Chama o Update do proprio e dos filhos
void PK_2DSceneControl::InternalUpdate(const PK_GameTimer &time)
{
    if (IsEnabled())
    {
    
        if (GetWithInput())
        {
            // Evento de clique sobre o controlo
            if (OnClick.HasCallback() && PokeEngine.GetInputManager().QueryAction(PK::InputAction_Clicked))
            {
                PK_Vector2 pos =PK::PokeEngine.GetInputManager().GetPointerPosition();
                if (GetClientRect().ContainsPoint(pos))
                {
                    GetScene()->SetClickedControl(this);
                }
            }
            else
            if (OnFlick.HasCallback() && PokeEngine.GetInputManager().QueryAction(PK::InputAction_Flick))
            {
                PK_Vector2 pos =PK::PokeEngine.GetInputManager().GetFlickStartingPoint();
                if (GetClientRect().ContainsPoint(pos))
                {
                    GetScene()->SetFlickedControl(this);
                }
            }
        }
    }

    if (WithPhysics())
    {
        PK_Vector2 vPos = m_pAttachedBody->GetPosition();
        SetPosition(vPos);
        SetRotation(m_pAttachedBody->GetRotation());
        m_bSuppressBodyTransformUpdates = true;
    }

    PK_SceneControl::InternalUpdate(time);
    m_bSuppressBodyTransformUpdates = false;
}
 
// Chama o Update do proprio e dos filhos
void PK_2DSceneControl::InternalDraw()
{

   if (m_BackgroundColor.a != 0.0)
   {
	   #ifdef PK_USEVERTEXBUFFERS
	   if (m_pClientRectRenderData != NULL)
	   {
		  PokeEngine.GetRenderManager().RenderQuad(*m_pClientRectRenderData, m_BackgroundColor, m_matTransform);
	   }	   
	   #else
       PokeEngine.GetRenderManager().RenderQuad(GetClientRect(), m_BackgroundColor);
	   #endif
   }

   if (m_pBackgroundSprite != NULL)
   {
       #ifdef PK_USEVERTEXBUFFERS
       PokeEngine.GetRenderManager().RenderSprite(*m_pBackgroundSprite, 0, GetBlendedColor(), m_matTransform);
	   #else
       PokeEngine.GetRenderManager().RenderSprite(*m_pBackgroundSprite, *GetBackgroundImageRect(), 0, GetBlendedColor());
       #endif
 }
   InternalAfterDrawBackground();
   PK_SceneControl::InternalDraw();
}

//
void PK_2DSceneControl::Copy(PK_SceneControl &copyFrom)
{
    PK_SceneControl::Copy(copyFrom);

    PK_2DSceneControl *pCopyFrom = (PK_2DSceneControl *)&copyFrom;
    SetSize(pCopyFrom->m_Size);
    SetPosition(pCopyFrom->m_vPosition);
    SetRotation(pCopyFrom->m_fRotation);
    SetScale(pCopyFrom->m_vScale);
    // Estes sao calculados automaticamente no refresh
    //m_vWorldPosition = copyFrom.m_vWorldPosition;
    //m_fWorldRotation = copyFrom.m_fWorldRotation;
    //m_vWorldScale = copyFrom.m_vWorldScale;
    //m_bsClientRect = copyFrom.m_bsClientRect;*/
    //m_matTransform = copyFrom.m_matTransform;  
    //m_uiRefreshFlags = copyFrom.m_uiRefreshFlags;
    //m_uiChildRefreshFlags = copyFrom.m_uiChildRefreshFlags;
    SetColor(pCopyFrom->m_Color);
    //m_BlendedColor = pCopyFrom->m_BlendedColor;
    SetBackgroundColor(pCopyFrom->m_BackgroundColor);
    SetPivot(pCopyFrom->m_vPivot); 
    SetPivotAligment(pCopyFrom->m_uiPivotAligment); 
    SetDockStyle(pCopyFrom->m_uiDockStyle);
    SetParentAlignment(pCopyFrom->m_uiParentAlignment);
    SetPadding(pCopyFrom->m_Padding); 
    SetBackgroundImage(pCopyFrom->m_pBackgroundSprite);
    //SetBackgroundSprite(copyFrom.m_sBackgroundSpriteAssetName;
    SetBackgroundImageFitMode(pCopyFrom->m_BackgroundImageFitMode);

    // Suporte para fisica
    SetWithPhysics(pCopyFrom->m_bWithPhysics);
    SetBodyDefinition(pCopyFrom->m_BodyDefinition);
}

//
void PK_2DSceneControl::InternalAddedToScene()
{
    if (m_bWithPhysics)
    {
       CreateBody();
    }

    PK_SceneControl::InternalAddedToScene();
}

// Seta o parent control
// FIXME: ver se e possivel verificar referencias circulares
void PK_2DSceneControl::SetParent(PK_SceneControl * pNewParent) 
{ 
    PK_SceneControl::SetParent(pNewParent);

  /*  if (m_p2DParent != NULL)
    {
        m_p2DParent->Release();
        m_p2DParent = NULL;
    }*/
    if (pNewParent != NULL)
    {
        if (pNewParent->Is2DControl())
        {
            m_p2DParent = (PK_2DSceneControl *) pNewParent;
            // Nao guardar referencias para o pai por causa de reference counting circular
      //      m_p2DParent->Grab();
        }
    }
    Invalidate();
    // Algumas properties teem que ser refrescadas (ver documento ControlLayoutUpdate.txt)
    m_uiRefreshFlags |= RefreshFlags_Dock | RefreshFlags_Position | RefreshFlags_WorldPosition |
                        RefreshFlags_WorldRotation | RefreshFlags_WorldScale;

    // remove o body
    if (HasBody())
    {
        DettachFromBody();
    }
}

//
void PK_2DSceneControl::ApplyEffects()
{
    PK_ASSERT(m_pEffectsBlender != NULL);
    
    Move(m_pEffectsBlender->GetPositionDelta().x, m_pEffectsBlender->GetPositionDelta().y);
    Rotate(m_pEffectsBlender->GetRotationDelta().z);
    Scale(m_pEffectsBlender->GetScale().x, m_pEffectsBlender->GetScale().y);
    
    SetColor(m_pEffectsBlender->GetColor());
}

//
void PK_2DSceneControl::RemoveControlImmediate(PK_SceneControl *pControl)
{
  if (HasBody())
  {
    m_pAttachedBody->RemoveFromSimulation();
    m_pAttachedBody->Release();
    m_pAttachedBody = NULL;
  }
  PK_SceneControl::RemoveControlImmediate(pControl);
}

//
void PK_2DSceneControl::AttachBody(PK_Body &body)
{
  if (GetScene() == NULL)
  {
    throw PK_SystemException("Cannot attach a body to control named '%s'. Controls can only have bodies if they are part of a scene.", __FILE__, __LINE__, GetName().c_str());
  }
  if (m_pAttachedBody != NULL)
  {
    throw PK_SystemException("Control is already attached to a body.", __FILE__, __LINE__);
  }
  m_pAttachedBody = &body;
  m_pAttachedBody->SetAttachedControl(this);
  m_pAttachedBody->Grab();
  m_bWithPhysics = true;
}

//
PK_Body * PK_2DSceneControl::CreateBody()
{
  if (GetScene() == NULL)
  {
    throw PK_SystemException("Cannot create body on control named '%s'. Controls can only have bodies if they are part of a scene.", __FILE__, __LINE__, GetName().c_str());
  }

  if (HasBody())
  {
    throw PK_SystemException("Cannot create body because control named '%s' already has a body.", __FILE__, __LINE__, GetName().c_str());
  }


  switch(m_BodyDefinition.shapeMode)
  {
        case ControlBodyShapeMode_Autoadjust:
        {
            m_BodyDefinition.bodyParts.Clear();
            PK_t2DBodyPartDefinition partDefinition;
            partDefinition.SetToBox(GetSize(), GetPivot());
            m_BodyDefinition.bodyParts.Add(partDefinition);
        }
        break;

    default:
        break;
  }

  PK_Body *pBody = GetScene()->GetPhysicsManager()->CreateBody(GetName() + "_body", GetWorldPosition(), m_BodyDefinition);
  AttachBody(*pBody);
  pBody->SetRotation(GetRotation());
  return pBody;
}


//
void PK_2DSceneControl::DettachFromBody()
{
  if (m_pAttachedBody != NULL)
  {
      m_pAttachedBody->RemoveFromSimulation();
      m_pAttachedBody->Release();
      m_pAttachedBody = NULL;
  }
  m_bWithPhysics = false;
}

//
void PK_2DSceneControl::SetWithPhysics(bool bWithPhysics, PK_eBodyType bodyType)
{
    if (m_bWithPhysics == bWithPhysics)
    {
        return;
    }

    // Se tem fisica e corpo, remover o corpo
    if (m_bWithPhysics)
    {
        if (HasBody())
        {
            DettachFromBody();
        }
    }
    else
    {
        m_BodyDefinition.bodyType = bodyType;
        // Se faz parte uma scene, criar o corpo
        if (GetScene() != NULL)
        {
            CreateBody();
        }
    }

    m_bWithPhysics = bWithPhysics;
    
}
   
//
void PK_2DSceneControl::ApplyForce(const PK_Vector2 &vForce)
{
    if (HasBody() == false)
    {
        throw PK_SystemException("Cannot apply forces to control named [%s] because it's not under physics simulation. Use AttachBody() to add physics.", __FILE__, __LINE__, GetName().c_str());
    }
    m_pAttachedBody->ApplyForce(vForce);
}
    
//
PK_PhysicsManager * PK_2DSceneControl::GetPhysicsManager()
{
    if (WithPhysics() == false)
    {
      throw PK_SystemException("Cannot get Physics Manager because control named [%s] it's not under physics simulation.", __FILE__, __LINE__, GetName().c_str());
    }
    
   
    return GetScene()->GetPhysicsManager();
}

//
void PK_2DSceneControl::SetBodyDefinition(const PK_tBodyDefinition &definition)
{
    if (HasBody())
    {
      throw PK_SystemException("Cannot set body definition because control named [%s] after attaching a body to it.", __FILE__, __LINE__, GetName().c_str());
    }
    m_BodyDefinition = definition;
}

//
void PK_2DSceneControl::SetBodyDefinition(PK_eBodyType bodyType, PK_eControlBodyShapeMode shapeMode)
{
    SetBodyDefinition(PK_tBodyDefinition(bodyType, shapeMode));
}

//
void PK_2DSceneControl::SetWorldPosition(float x, float y)
{
    if (m_vWorldPosition.x != x || m_vWorldPosition.y != y)
    {
        m_vWorldPosition = PK_Vector2(x, y);
        m_uiRefreshFlags |= RefreshFlags_TransformMatrix;
        m_uiChildRefreshFlags |= RefreshFlags_WorldPosition;
        if (HasBody() && !m_bSuppressBodyTransformUpdates)
        {
            m_pAttachedBody->SetWorldPosition(x, y);
        }
    }
}

//
void PK_2DSceneControl::SetBackgroundImage(PK_SpriteAsset *pSprite)
{
    if (pSprite == m_pBackgroundSprite)
    {
        return;
    }
    if (m_pBackgroundSprite != NULL)
    {
        m_pBackgroundSprite->Release();
    }
    m_pBackgroundSprite = pSprite;
    if (m_pBackgroundSprite != NULL)
    {
        m_pBackgroundSprite->Grab();
        m_uiRefreshFlags |= RefreshFlags_BackgroundImageRect;
        if (m_BackgroundImageFitMode == ImageSizeMode_SizeControlToImage)
        {
            m_uiRefreshFlags |= RefreshFlags_Size;
        }
    }
}

//
void PK_2DSceneControl::SetBackgroundImage(const PK_String &sAssetName)
{
    if (sAssetName != m_sBackgroundSpriteAssetName)
    {
        m_sBackgroundSpriteAssetName = sAssetName;
        m_uiRefreshFlags |= RefreshFlags_BackgroundImage;
    }
}



// Move o objecto por offset
void PK_2DSceneControl::Move(const PK_Vector2 &vOffset)
{
    PK_Vector2 v = GetPosition() + vOffset;
	SetPosition(v);
}

// Move o objecto por offset
void PK_2DSceneControl::Move(float x, float y)
{
    PK_Vector2 v = GetPosition() + PK_Vector2(x, y);
	SetPosition(v);
}

// Roda o objecto por offset
void PK_2DSceneControl::Rotate(float fOffset)
{
    SetRotation(GetRotation() + fOffset);
}

// Escala o objecto por offset
void PK_2DSceneControl::Scale(const PK_Vector2 &vOffset)
{
    SetScale(GetScale() * vOffset);
}

// Escala o objecto por offset
void PK_2DSceneControl::Scale(float x, float y)
{
    SetScale(GetScale() * PK_Vector2(x, y));
}

// 
void PK_2DSceneControl::UpdateLayout()
{
#ifdef POKE_DEBUG
    int iLoopCount = 0; // Prevenir loops infinitos, indica bug no engine!
#endif
    // Temos um loop porque o refresh de cada propriedade pode forcar refresh de outras
    // propriedades, isto podia impedir o refres de properiedades que tivessem o if antes
    while (m_uiRefreshFlags != RefreshFlags_None)
    {
        // Background image
        if (m_uiRefreshFlags & RefreshFlags_BackgroundImage)
        {
            UpdateBackgroundImage();
        }
        
        // Background image rect
        if (m_uiRefreshFlags & RefreshFlags_BackgroundImageRect)
        {
            UpdateBackgroundImageRect();
        }

        // Size
        if (m_uiRefreshFlags & RefreshFlags_Size)
        {
            UpdateSize();
        }

        // Physics body
        if (m_uiRefreshFlags & RefreshFlags_PhysicsBody)
        {
            UpdatePhysicsBody();
        }

        
        // Alignment
        if (m_uiRefreshFlags & RefreshFlags_Alignment)
        {
            if (GetParentAlignment() != ParentAlignment_None)
            {
                m_uiRefreshFlags |= RefreshFlags_Position;
            }
            m_uiRefreshFlags &= ~RefreshFlags_Alignment;
        }

        // Color
        if (m_uiRefreshFlags & RefreshFlags_BlendedColor)
        {
            UpdateBlendedColor();
        }

        // Position
        if (m_uiRefreshFlags & RefreshFlags_Position)
        {
            UpdatePosition();
        }

        // World position
        if (m_uiRefreshFlags & RefreshFlags_WorldPosition)
        {
            UpdateWorldPosition();
        }
        
        // World rotation
        if (m_uiRefreshFlags & RefreshFlags_WorldRotation)
        {
            UpdateWorldRotation();
        }
        
        // World scale
        if (m_uiRefreshFlags & RefreshFlags_WorldScale)
        {
            UpdateWorldScale();
        }
        
        // Pivot
        if (m_uiRefreshFlags & RefreshFlags_Pivot)
        {
            UpdatePivot();
        }
        
        // Transform matrix
        if (m_uiRefreshFlags & RefreshFlags_TransformMatrix)
        {
            UpdateTransformMatrix();
        }
        
        // Client rect
        if (m_uiRefreshFlags & RefreshFlags_ClientRect)
        {
            UpdateClientRect();
        }

		 // Client rect primitive data, usado para pintar o background
        if (m_uiRefreshFlags & RefreshFlags_CliRectPrimitiveData)
        {
			UpdateClientRectPrimitiveData();
        }

        // Child docks
        if (m_uiRefreshFlags & RefreshFlags_ChildDocks)
        {
            UpdateChildsDock();
        }
   
#ifdef POKE_DEBUG
        if (++iLoopCount >=  10) 
        {
            throw PK_SystemException("Control update layout with bug! Infinite loop detected. Control name '%s', refresh flags='%s'",
                    __FILE__, __LINE__, GetName().c_str(), PK_TypeConverters::SceneControlRefreshFlagsToStr((PK_eSceneControlRefreshFlags)m_uiRefreshFlags).c_str());
    /*        int a = 1;
            a++;
            PK_Log::WriteInfo(PK_LOG_TAG, PK_TypeConverters::SceneControlRefreshFlagsToStr((PK_eSceneControlRefreshFlags)m_uiRefreshFlags));*/
        }
#endif
    } //  while

    if (m_uiChildRefreshFlags != RefreshFlags_None)
    {
        if (WithChilds())
        {
            InvalidateChilds(m_uiChildRefreshFlags);
        }
        m_uiChildRefreshFlags = RefreshFlags_None;
    }
    
}

//
void PK_2DSceneControl::UpdatePosition()
{
    if (m_uiParentAlignment != ParentAlignment_None)
    {
        AlignToParent();
    }
    m_uiRefreshFlags &= ~RefreshFlags_Position;
}

//
void PK_2DSceneControl::AlignToParent()
{
    if (m_p2DParent == NULL)
    {
        return;
    }

    PK_tSize size = GetSize();
    PK_tSize parentSize = m_p2DParent->GetSize();
    // Alinhamento horizontal
    if ((m_uiParentAlignment & ParentAlignment_Horizontaly))
    {
        SetPosition(-GetPivot().x + m_p2DParent->GetPivot().x, m_vPosition.y);
    }
    // Alinhamento vertical
    if ((m_uiParentAlignment & ParentAlignment_Verticaly))
    {
        SetPosition(m_vPosition.x, -GetPivot().y + m_p2DParent->GetPivot().y);
    }
    // Alinhamento a esquerda
    if ((m_uiParentAlignment & ParentAlignment_Left))
    {
        SetPosition((-parentSize.w / 2) + (size.w / 2) - GetPivot().x + m_p2DParent->GetPivot().x + GetPadding().left,
                    m_vPosition.y);
    }
    // Alinhamento acima
    if ((m_uiParentAlignment & ParentAlignment_Top))
    {
        SetPosition(m_vPosition.x,
                    (parentSize.h / 2) - (size.h / 2) - GetPivot().y + m_p2DParent->GetPivot().y - GetPadding().top);
    }
    // Alinhamento a direita
    if (m_uiParentAlignment & ParentAlignment_Right)
    {
        SetPosition((parentSize.w / 2) -(size.w / 2) - GetPivot().x + m_p2DParent->GetPivot().x - GetPadding().right, 
                       m_vPosition.y);
    }
    // Alinhamento abaixo
    if (m_uiParentAlignment & ParentAlignment_Bottom)
    {
        SetPosition(m_vPosition.x, (-parentSize.h / 2) + (size.h / 2) - GetPivot().y + m_p2DParent->GetPivot().y + GetPadding().bottom);
    }
}

// Faz dock a bs passada
// Devolve a bs original - a bs final do controlo
void PK_2DSceneControl::DockToRect(const PK_tAABoundingSquare &aabs, PK_tAABoundingSquare &retBs)
{
    PK_tSize size = m_SizeBeforeDock;
    PK_tSize parentSize = aabs.size;
    switch(m_uiDockStyle)
    {
        case DockStyle_Left:
            SetSize(size.w, aabs.size.h);
            SetPosition(aabs.vPosition.x + (size.w / 2) - GetPivot().x,
                        aabs.vPosition.y - (aabs.size.h / 2) - GetPivot().y);
            retBs.Set(aabs.vPosition.x + size.w, aabs.vPosition.y, aabs.size.w - size.w, aabs.size.h);
            break;
            
        case DockStyle_Top:
            SetSize(aabs.size.w, size.h);
            SetPosition(aabs.vPosition.x + (aabs.size.w / 2) - GetPivot().x,
                        aabs.vPosition.y - (size.h / 2) - GetPivot().y);
            retBs.Set(aabs.vPosition.x, aabs.vPosition.y - size.h, aabs.size.w, aabs.size.h - size.h);
            break;
            
        case DockStyle_Right:
            SetSize(size.w, aabs.size.h);
            SetPosition(aabs.vPosition.x + parentSize.w -  (size.w / 2) - GetPivot().x,
                        aabs.vPosition.y - (aabs.size.h / 2) - GetPivot().y);
            retBs.Set(aabs.vPosition.x, aabs.vPosition.y, aabs.size.w - size.w, aabs.size.h);
            break;
            
        case DockStyle_Bottom:
            SetSize(aabs.size.w, size.h);
            SetPosition(aabs.vPosition.x + (aabs.size.w / 2) - GetPivot().x,
                        aabs.vPosition.y - parentSize.h + (size.h / 2) - GetPivot().y);
            retBs.Set(aabs.vPosition.x, aabs.vPosition.y, aabs.size.w, aabs.size.h - size.h);
            break;
            
        case DockStyle_Fill:
            SetSize(aabs.size.w, aabs.size.h);
            SetPosition(aabs.vPosition.x + (aabs.size.w / 2) - GetPivot().x,
                        aabs.vPosition.y - (aabs.size.h / 2) - GetPivot().y);
            retBs.Set(0,0,0,0);
            break;
            
        default:
            retBs.Set(0,0,0,0);
            break;
    }
    // Necessario porque o SetSize() faz invalidate ao Dock
    // FIXME: Esta flag devia ser Dock
    m_uiRefreshFlags &= ~RefreshFlags_Position;
}

// Actualiza a matrix de transformacao do objecto
void PK_2DSceneControl::UpdateTransformMatrix()
{
    m_matTransform = PK_Matrix3(1.0f);
   
    if (m_fRotation != 0.0f)
    {
      m_matTransform *= glm::translate(GetPosition() + GetPivot()) * glm::rotate(-GetRotation()) ;
    }
    else
    {
      m_matTransform *= glm::translate(GetPosition() + GetPivot());
    } 

    // N tenho a certeza se o scale deve ser aplicado antes ou depois da rotacao, nao testado!
    if (m_vScale.x != 1.0f || m_vScale.y != 1.0f)
    {
        m_matTransform *=glm::scale(m_vScale);
    }

    if (m_p2DParent != NULL)
    {
        m_matTransform = *m_p2DParent->GetTransformMatrix() * m_matTransform;
    }

    m_uiRefreshFlags &= ~RefreshFlags_TransformMatrix;
    m_uiRefreshFlags |= RefreshFlags_ClientRect;
    InvalidateChilds(RefreshFlags_TransformMatrix | RefreshFlags_ClientRect);
}
    
// Actualiza o client rect a partir da matrix de transformacao
void PK_2DSceneControl::UpdateClientRect()
{
    PK_tSize size = GetSize();
    m_bsClientRect.Set(-(size.w / 2.0f) - GetPivot().x, -(size.h / 2.0f) - GetPivot().y, (float)size.w, (float)size.h);
    m_bsClientRect.TransformInPlace(*GetTransformMatrix());
    
    m_uiChildRefreshFlags |= RefreshFlags_Dock | RefreshFlags_Alignment; 
    m_uiRefreshFlags &= ~RefreshFlags_ClientRect;
    m_uiRefreshFlags |= RefreshFlags_BackgroundImageRect | RefreshFlags_CliRectPrimitiveData;

}

//
void PK_2DSceneControl::UpdateClientRectPrimitiveData()   
{
	if (GetBackgroundColor().a != 0.0f)
	{
		if (m_pClientRectRenderData != NULL)
		{
			delete m_pClientRectRenderData; 
		}
		PK_tSize size = GetSize();
		PK_tBoundingSquare bs;
		bs.Set(-(size.w / 2.0f) - GetPivot().x, -(size.h / 2.0f) - GetPivot().y, (float)size.w, (float)size.h);
#if defined(PK_USEVERTEXBUFFERS)
		m_pClientRectRenderData = &PokeEngine.GetRenderManager().CreateColorShaderPrimitiveData(bs);
#endif
	}
	m_uiRefreshFlags &= ~RefreshFlags_CliRectPrimitiveData;
}


//
void PK_2DSceneControl::UpdateWorldPosition()
{
    PK_Vector2 vWorldPos = GetPosition();
    if (m_p2DParent != NULL)
    {
        vWorldPos += m_p2DParent->GetWorldPosition();
    }
    SetWorldPosition(vWorldPos.x, vWorldPos.y);
    m_uiRefreshFlags &= ~RefreshFlags_WorldPosition;
}
    
//
void PK_2DSceneControl::UpdateWorldRotation()
{
    float fWorldRotation = GetRotation();
    if (m_p2DParent != NULL)
    {
        fWorldRotation += m_p2DParent->GetWorldRotation();
    }
    SetWorldRotation(fWorldRotation);
    m_uiRefreshFlags &= ~RefreshFlags_WorldRotation;
}
    
//
void PK_2DSceneControl::UpdateWorldScale()
{
    PK_Vector2 vWorldScale = GetScale();
    if (m_p2DParent != NULL)
    {
        vWorldScale *= m_p2DParent->GetWorldScale();
    }
    SetWorldScale(vWorldScale);
    m_uiRefreshFlags &= ~RefreshFlags_WorldScale;
}

//
void PK_2DSceneControl::UpdateBackgroundImage()
{ 
    m_uiRefreshFlags &= ~RefreshFlags_BackgroundImage;
    if (m_sBackgroundSpriteAssetName.length() == 0)
    {
        SetBackgroundImage(NULL);
        return;
    }

    SetBackgroundImage(PokeEngine.GetAssetManager().LoadSprite(m_sBackgroundSpriteAssetName, GetAssetContainerName()));
}
    
//
void PK_2DSceneControl::UpdateBackgroundImageRect()
{
    if (m_pBackgroundSprite != NULL)
    {
        switch(m_BackgroundImageFitMode)
        {
            case ImageSizeMode_Fit:
            {
                m_bsBackgroundImage = GetClientRect();
                break;
            }
            
            case ImageSizeMode_RealSize:
            {
                PK_tSize size = m_pBackgroundSprite->GetSize();
                m_bsBackgroundImage.Set(-(size.w / 2.0f) - GetPivot().x,
                                        -(size.h / 2.0f) - GetPivot().y, (float)size.w, (float)size.h);
                m_bsBackgroundImage.TransformInPlace(*GetTransformMatrix());
                break;
            }
            
            case ImageSizeMode_SizeControlToImage:
            {
                PK_tSize size = m_pBackgroundSprite->GetSize();
                m_bsBackgroundImage.Set(-(size.w / 2.0f) - GetPivot().x,
                                        -(size.h / 2.0f) - GetPivot().y, (float)size.w, (float)size.h);
                m_bsBackgroundImage.TransformInPlace(*GetTransformMatrix());
                m_uiRefreshFlags |= RefreshFlags_Size;
                break;
            }
                
            case ImageSizeMode_FitBigger:
                break;
        }


    }
    m_uiRefreshFlags &= ~RefreshFlags_BackgroundImageRect;
}

//
void PK_2DSceneControl::UpdateSize()
{ 
    m_uiRefreshFlags &= ~RefreshFlags_Size;
    if (m_BackgroundImageFitMode == ImageSizeMode_SizeControlToImage &&
        m_pBackgroundSprite != NULL)
    {
        SetSize(m_pBackgroundSprite->GetSize());
    }
}

//
void PK_2DSceneControl::UpdatePhysicsBody()
{
    m_uiRefreshFlags &= ~RefreshFlags_PhysicsBody;
    if (WithPhysics())
    {
        if (HasBody())
        {
            DettachFromBody();
        }
        CreateBody();
    }

}

       
//
void PK_2DSceneControl::UpdateChildsDock()
{
    m_uiRefreshFlags &= ~RefreshFlags_ChildDocks;
    // Dock so funciona para controlos axis oriented
    if (!m_bsClientRect.IsAxisOriented())
    {
        return;
    }
    if (WithChilds() == false)
    {
        return;
    }
    
    // Comecamos com um rect do tamanho do client rect
    // Depois a medida que vamos "dockando" os clientes, o rect vai diminuindo e utilizamos esse rect para o proximo cliente
    PK_tAABoundingSquare bsRect;
    PK_tAABoundingSquare bsRet;
    GetClientRect().ToAABoundingSquare(bsRect);
    bsRect.Translate(-GetPosition() + PK_Vector2(GetPadding().left, -GetPadding().top));
    bsRect.size.Set(bsRect.size.w - GetPadding().left - GetPadding().right,
                    bsRect.size.h - GetPadding().top - GetPadding().bottom);
    
    for(PK_ListIterator(PK_SceneControl *) itor = GetControls().Begin(); itor != GetControls().End(); itor++)
    {
        if (!(*itor)->Is2DControl())
        {
            continue;
        }
        PK_2DSceneControl *pClient = (PK_2DSceneControl *)(*itor);
        // Ignorar clientes sem dock
        if (pClient->GetDockStyle() == DockStyle_None)
        {
            continue;
        }
        pClient->DockToRect(bsRect, bsRet);
        bsRect = bsRet;
        switch(pClient->GetDockStyle())
        {
            case DockStyle_Top:
                bsRect.vPosition += PK_Vector2(0.0f, -GetPadding().top);
                bsRect.size.Set(bsRect.size.w, bsRect.size.h - GetPadding().top);
                break;
                
            case DockStyle_Bottom:
                bsRect.size.Set(bsRect.size.w, bsRect.size.h - GetPadding().bottom);
                break;
                
            case DockStyle_Left:
                bsRect.vPosition += PK_Vector2(GetPadding().left, 0.0f);
                bsRect.size.Set(bsRect.size.w - GetPadding().left, bsRect.size.h);
                break;
                
            case DockStyle_Right:
                bsRect.size.Set(bsRect.size.w - GetPadding().right, bsRect.size.h);
                break;
        }
    }
}

//
void PK_2DSceneControl::UpdatePivot()
{
    switch(GetPivotAligment())
    {
        case PivotAlignment_Center:
            SetPivot(0.0f, 0.0f);
            break;
        case PivotAlignment_TopLeft:
            SetPivot(-(GetSize().w / 2), (GetSize().h / 2));
            break;
        case PivotAlignment_Top:
            SetPivot(0.0f, (GetSize().h / 2));
            break;
        case PivotAlignment_TopRight:
            SetPivot((GetSize().w / 2), (GetSize().h / 2));
            break;
        case PivotAlignment_Right:
            SetPivot((GetSize().w / 2), 0.0f);
            break;
        case PivotAlignment_BottomRight:
            SetPivot((GetSize().w / 2), -(GetSize().h / 2));
            break;
        case PivotAlignment_Bottom:
            SetPivot(0.0f, -(GetSize().w / 2));
            break;
        case PivotAlignment_BottomLeft:
            SetPivot(-(GetSize().w / 2), -(GetSize().h / 2));
            break;
        case PivotAlignment_Left:
            SetPivot(-(GetSize().w / 2), 0.0f);
            break;
        case PivotAlignment_None:
            break;
    }
    
    m_uiRefreshFlags &= ~RefreshFlags_Pivot;
}

//
void PK_2DSceneControl::UpdateBlendedColor()
{
    if (m_p2DParent != NULL)
    {
        m_BlendedColor = m_p2DParent->GetBlendedColor() * GetColor();
    }
    else
    {
        m_BlendedColor = m_Color;
    }
    m_uiRefreshFlags &= ~RefreshFlags_BlendedColor;
}

//
void PK_2DSceneControl::InvalidateChilds(unsigned int uiFlags)
{
    for(PK_ListIterator(PK_SceneControl *) itor = GetControls().Begin(); itor != GetControls().End(); itor++)
    {
        if (!(*itor)->Is2DControl())
        {
            continue;
        }
        PK_2DSceneControl * pControl = (PK_2DSceneControl *)(*itor);
        pControl->Invalidate(uiFlags);
        if (pControl->WithChilds())
        {
            pControl->InvalidateChilds(uiFlags);
        }
    }
}

// Transform matrix
PK_Matrix3 * PK_2DSceneControl::GetTransformMatrix()
{
    if (m_uiRefreshFlags & RefreshFlags_TransformMatrix)
    {
        UpdateTransformMatrix();
    }
    return &m_matTransform;
}
    
// 
PK_tBoundingSquare * PK_2DSceneControl::GetBackgroundImageRect()
{
    if (m_uiRefreshFlags & RefreshFlags_BackgroundImageRect)
    {
        UpdateBackgroundImageRect();
    }
    return &m_bsBackgroundImage;
}
    
//
void PK_2DSceneControl::InvalidateDock()
{
    if (m_uiDockStyle != DockStyle_None)
    {
        if (m_p2DParent != NULL)
        {
            m_p2DParent->InvalidateChildDocks();
        }
    }
    InvalidateChildDocks();
}

//
void PK_2DSceneControl::SetSize(float w, float h)
{
    if (m_Size.w != w ||
        m_Size.h != h)
    {
        m_Size.Set(w, h);
        m_uiRefreshFlags |= RefreshFlags_ClientRect | RefreshFlags_Position | RefreshFlags_TransformMatrix | RefreshFlags_PhysicsBody;
        InvalidateDock();
        if (GetDockStyle() != DockStyle_None)
        {
            switch(GetDockStyle())
            {
                case DockStyle_Left:
                case DockStyle_Right:
                    m_SizeBeforeDock.Set(w, m_SizeBeforeDock.h);
                    break;
                    
                case DockStyle_Top:
                case DockStyle_Bottom:
                    m_SizeBeforeDock.Set(m_SizeBeforeDock.w, h);
                    break;
            }
        }

    }
}
    
} // namespace
