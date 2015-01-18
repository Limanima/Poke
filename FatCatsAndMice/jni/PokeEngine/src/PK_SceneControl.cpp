#include "PK_Consts.h"
#include "PK_Globals.h"
#include "PK_Exceptions.h"
#include "PK_SceneControl.h"
#include "PK_Scene.h"
#include "PK_InputManager.h"
#include "PK_ClassFactory.h"
#include "PK_EffectsBlender.h"
#include "PK_Assert.h"

#define DEFAULT_VALUE_VISIBLE       true
#define DEFAULT_VALUE_WITH_INPUT    true
#define DEFAULT_VALUE_ENABLED       true

namespace PK {

//
PK_SceneControl::PK_SceneControl(const PK_String &sName) :
  PK_LoadableObject(sName)
{
    SetTypeName("PK_SceneControl");
    m_sAssetContainerName = PK_ASSET_CONTAINER_NAME;
    m_pParent = NULL;  // Nao usar SetParent()
    m_bWithInput = DEFAULT_VALUE_WITH_INPUT;
    m_bVisible = DEFAULT_VALUE_VISIBLE;
    m_bEnabled = DEFAULT_VALUE_ENABLED;
    m_pEffectsBlender = NULL; // Apenas e criado se necessario no AddEffect
    m_bRemovedFromScene = false;
    m_pShowEffect = NULL;
    m_bUpdateWhenHidden = true;
}

// Destrutor
PK_SceneControl::~PK_SceneControl()
{
    FreeResources();
}

// Destrutor
void PK_SceneControl::FreeResources()
{
   InternalUnload();
}

// Metodo implementado para PK_LoadableObject
void PK_SceneControl::Load()
{
    OnLoad();
}

//
void PK_SceneControl::InitFromDataFileRecord(PK_DataFileRecord &record)
{
    PK_Object::InitFromDataFileRecord(record);

    SetVisible(record.GetChildRecordFieldValue_Bool("visible", "value", DEFAULT_VALUE_VISIBLE));
    SetWithInput(record.GetChildRecordFieldValue_Bool("withInput", "value", DEFAULT_VALUE_WITH_INPUT));
    
    InitChildsDataFileRecord(record);
}

//
void PK_SceneControl::InitChildsDataFileRecord(PK_DataFileRecord &record)
{
    PK_List<PK_DataFileRecord *> controlsRec;
    record.SelectRecords("controls/control", controlsRec, false);
    for(PK_ListIterator(PK_DataFileRecord *) itor = controlsRec.Begin(); itor != controlsRec.End(); itor++)
    {
        PK_SceneControl *pControl = PK_SceneControl::CreateFromDataFileRecord(*(*itor));
        AddControl(pControl);
    }
}
    
// Chama o OnInitialize do proprio e dos filhos
void PK_SceneControl::InternalInitialize()
{

    OnInitialize();
    for(PK_ListIterator(PK_SceneControl *) itor = m_Controls.Begin(); itor != m_Controls.End(); itor++)
    {
        (*itor)->InternalInitialize();
    }
}

// Chama o Load do proprio e dos filhos
void PK_SceneControl::InternalLoad()
{
    OnLoad();
    for(PK_ListIterator(PK_SceneControl *) itor = m_Controls.Begin(); itor != m_Controls.End(); itor++)
    {
        (*itor)->InternalLoad();
    }
}
    
// Chama o Update do proprio e dos filhos
void PK_SceneControl::InternalUpdate(const PK_GameTimer &time)
{

    if (IsEnabled())
    {
        if (m_pEffectsBlender != NULL &&
            m_pEffectsBlender->WithEffects())
        {
            m_pEffectsBlender->OnUpdate(time);
        }
        OnUpdate(time);
    }

    for(PK_ListIterator(PK_SceneControl *) itor = m_Controls.Begin(); itor != m_Controls.End(); itor++)
    {
        // Este if esta aqui e nao na entrada de InternalUpdate porque o internalupdate pode estar overriden
        if ((*itor)->IsVisible() || (!(*itor)->IsVisible() && (*itor)->ShouldUpdateWhenHidden()))
        {
            (*itor)->InternalUpdate(time);
        }
    }

    // Chama sempre o UpdateLayout
    UpdateLayout();
}

// Chama o Update do proprio e dos filhos
void PK_SceneControl::InternalDraw()
{
    OnDraw();
  	for(PK_ListIterator(PK_SceneControl *) itor = m_Controls.Begin(); itor != m_Controls.End(); itor++)
    {
        if ((*itor)->IsVisible())
        {
            (*itor)->InternalDraw();
        }
    }
}
    
// Chama o OnUnload do proprio e dos filhos
void PK_SceneControl::InternalUnload()
{
    for(PK_ListIterator(PK_SceneControl *) itor = m_Controls.Begin(); itor != m_Controls.End(); itor++)
    {
        PK_SceneControl * pControl = (*itor);
        pControl->InternalUnload();
        pControl->Release();
    }
    m_Controls.Clear();
    
    if (m_pEffectsBlender != NULL)
    {
        PK_FREE(m_pEffectsBlender);
    }
    OnUnload();
}

//
void PK_SceneControl::InternalAddedToScene()
{
    if (m_pShowEffect != NULL && IsVisible())
    {
        ActivateShowEffect();
    }
   // UpdateLayout();
  
    for(PK_ListIterator(PK_SceneControl *) itor = m_Controls.Begin(); itor != m_Controls.End(); itor++)
    {
        (*itor)->InternalAddedToScene();
    }
}

//
void PK_SceneControl::Copy(PK_SceneControl &copyFrom)
{
    PK_SceneControl *pCopyFrom = (PK_SceneControl *)&copyFrom;
    m_sAssetContainerName = pCopyFrom->m_sAssetContainerName;
    SetEnabled(pCopyFrom->m_bEnabled);
    SetVisible(pCopyFrom->m_bVisible);
    SetWithInput(pCopyFrom->m_bWithInput);
//    m_bRemovedFromScene = m_bRemovedFromScene;
    //m_userData = pCopyFrom->m_userData;
   // m_pShowEffect = copyFrom.m_pShowEffect->Clone();
    // N clonar os filhos! Isto porque os filhos devem ser adicionados no construtor das classes
    //for(PK_ListIterator(PK_SceneControl *) itor = copyFrom.GetControls().Begin(); itor != copyFrom.GetControls().End(); itor++)
    //{
    //     AddControl(&(*itor)->Clone());
    //}
}

//
void PK_SceneControl::AddToLoadingQueue(PK_ObjectLoader &loader)
{
    loader.AddToQueue(*this);
    for(PK_ListIterator(PK_SceneControl *) itor = m_Controls.Begin(); itor != m_Controls.End(); itor++)
    {
        (*itor)->AddToLoadingQueue(loader);
    }
}


// Seta o parent control
void PK_SceneControl::SetParent(PK_SceneControl * pNewParent) 
{ 
  /*  // Controlo ja tem parent? Libertamos a referencia
    if (m_pParent != NULL)
    {
        m_pParent->Release();
    }*/
    // Nao fazer reference count no parent, isto porque causa referencias circulares
    m_pParent = pNewParent;
 /*   if (m_pParent != NULL)
    {
        m_pParent->Grab();
    }*/

    Invalidate();
}

// Adiciona um controlo filho
void PK_SceneControl::AddControl(PK_SceneControl *pControl)
{
    if (pControl == NULL)
    {
        throw PK_SystemException("SceneControl cannot have NULL childs.", __FILE__, __LINE__);
    }
    if (pControl->GetParent() != NULL)
    {
        throw PK_SystemException("SceneControl named '%s' cannot be added to parent '%s' because it is already added to a parent.",
                                 __FILE__, __LINE__, pControl->GetName().c_str(), GetName().c_str());
        
    }

    // Setamos self como o novo parent no controlo que estamos a adicionar
    pControl->SetParent(this);
    pControl->Grab();
    // Adicionar a lista de childs
    m_Controls.Add(pControl);
    if (GetScene() != NULL)
    {
        pControl->InternalAddedToScene();
    }
}

// Remove um controlo filho
void PK_SceneControl::RemoveControl(PK_SceneControl *pControl)
{
    if (pControl == NULL)
    {
        throw PK_SystemException("Control to be removed cannot be NULL.", __FILE__, __LINE__);
    }
    if (pControl->GetParent() != this)
    {
        throw PK_SystemException("SceneControl named '%s' cannot be removed because it's not a child of this parent.",
                                 __FILE__, __LINE__, pControl->GetName().c_str());
        
    }

    // Se o control esta adicionado a uma cena nao podemos remover logo porque pode estar a meio do loop update
    // Neste caso chamamos o metodo da scene que faz este controlo
    if (pControl->GetScene() != NULL)
    {
        GetScene()->RemoveControl(pControl);
    }
    else
    {
        RemoveControlImmediate(pControl);
    }
}

//
void PK_SceneControl::RemoveAllControls()
{
    for(PK_ListIterator(PK_SceneControl *) itor = m_Controls.Begin(); itor != m_Controls.End(); )
    {
        PK_SceneControl *pControl = (*itor);
        itor++;
        RemoveControl(pControl);
    }
}
    
//
void PK_SceneControl::RemoveControlImmediate(PK_SceneControl *pControl)
{
    pControl->SetParent(NULL);
    m_Controls.Remove(pControl);
    pControl->Release();
}

//
PK_SceneControl * PK_SceneControl::GetControl(const PK_String &sName)
{
    if (WithChilds())
    {
        for(PK_ListIterator(PK_SceneControl *) itor = m_Controls.Begin(); itor != m_Controls.End(); itor++)
        {
            if ((*itor)->GetName() == sName)
            {
                return (*itor);
            }
            if ((*itor)->WithChilds())
            {
                PK_SceneControl *pControl = (*itor)->GetControl(sName);
                if (pControl != NULL)
                {
                    return pControl;
                }
            }
        }
    }
    return NULL;
}
    
//
void PK_SceneControl::BringToFront()
{
    if (m_pParent == NULL)
    {
        return;
    }
    m_pParent->BringChildToFront(*this);
}
    
//
void PK_SceneControl::SendToBack()
{
    if (m_pParent == NULL)
    {
        return;
    }
    m_pParent->SendChildToBack(*this);
}
    
//
void PK_SceneControl::BringChildToFront(PK_SceneControl &control)
{
    if (control.GetParent() != this)
    {
        throw PK_SystemException("Cannot remove control named '%s' because it is a child of this parent." ,__FILE__, __LINE__, GetName().c_str());
    }
    m_Controls.Remove(&control);
    m_Controls.Add(&control);
    control.Invalidate();
}
    
//
void PK_SceneControl::SendChildToBack(PK_SceneControl &control)
{
    if (control.GetParent() != this)
    {
        throw PK_SystemException("Cannot remove control named '%s' because it is a child of this parent." ,__FILE__, __LINE__, GetName().c_str());
    }
    m_Controls.Remove(&control);
    m_Controls.InsertAtBeginning(&control);
    control.Invalidate();
}

//
void PK_SceneControl::AddEffect(PK_Effect &effect)
{
    if (m_pEffectsBlender == NULL)
    {
        m_pEffectsBlender = new PK_EffectsBlender(*this, GetName() + "_effectsBlender");
        m_pEffectsBlender->Grab();
    }

    m_pEffectsBlender->AddEffect(effect);
}

//
void PK_SceneControl::RemoveFromScene()
{
    if (GetScene() == NULL)
    {
        PK_Log::WriteWarning(PK_LOG_TAG, "Cannot remove control named '%s' from scene because it's not part of one.", __FILE__, __LINE__, GetName().c_str());
        return;
    }
    GetScene()->RemoveControl(this);
}

//
void PK_SceneControl::InternalControlClicked()
{
    InvokeOnClick();    
}

//
PK_Scene * PK_SceneControl::GetScene()
{
    if (m_pParent == NULL)
    {
        return NULL;
    }
    return m_pParent->GetScene();
}

//
//void PK_SceneControl::SetCallback(PK_ObjectCallback *pCallback, PK_ObjectCallback **pCallbackToSet)
void PK_SceneControl::SetCallback(PK_IObjectCallback *pCallback, PK_IObjectCallback **pCallbackToSet)
{ 
  if (*pCallbackToSet != NULL)
  {
    delete pCallbackToSet;
  }
  *pCallbackToSet = pCallback;
}

//
PK_SceneControl * PK_SceneControl::CreateFromDataFileRecord(PK_DataFileRecord &record)
{
    PK_String sType = record.GetFieldValue_String("type");
    PK_String sName = record.GetFieldValue_String("name");
    PK_SceneControl * pControl = PK_ClassFactory::CreateSceneControl(sType, sName);
    pControl->InitFromDataFileRecord(record);
    return pControl;
}

//
void PK_SceneControl::SetVisible(bool bVisible)
{
    if (m_bVisible != bVisible)
    {
        m_bVisible = bVisible;
        if (m_bVisible)
        {
            Invalidate();
            if (m_pShowEffect != NULL)
            {
               ActivateShowEffect();
            }
        }
    }
}

//
void PK_SceneControl::SetShowEffect(PK_Effect *pEffect)
{
    if (m_pShowEffect != NULL)
    {
        m_pShowEffect->RemoveFromBlender();
        m_pShowEffect->Release();
    }
    m_pShowEffect = pEffect;
    if (m_pShowEffect != NULL)
    {
        m_pShowEffect->Grab();
        m_pShowEffect->SetActive(false);
        m_pShowEffect->SetPersistent(true);
        AddEffect(*m_pShowEffect);
    }
}

//
void PK_SceneControl::ActivateShowEffect()
{
    if (m_pShowEffect != NULL && !m_pShowEffect->IsActive())
    {
        m_pShowEffect->SetActive(true);
        m_pShowEffect->InternalReset();
    }
}

} // namespace
