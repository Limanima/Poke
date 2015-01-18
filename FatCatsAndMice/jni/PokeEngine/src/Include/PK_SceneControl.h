#ifndef _PK_SCENECONTROL_H_
#define _PK_SCENECONTROL_H_

#include "PK_Consts.h"
#include "PK_LoadableObject.h"
#include "PK_List.h"
#include "PK_tBoundingSquare.h"
#include "PK_Types.h"
#include "PK_ObjectCallback.h"
#include "PK_ObjectLoader.h"
#include "PK_ParameterizedCallback.h"
#include "PK_Effect.h"
#include "PK_Effect.h"
#include "PK_Callback.h"
#include "PK_MessageReceiver.h"

namespace PK {
class PK_Scene;
struct PK_tScriptValue1;
class PK_EffectsBlender;
    
class PK_SceneControl : public PK_LoadableObject, public PK_MessageReceiver
{
private:
    PK_String          m_sAssetContainerName;
    PK_List<PK_SceneControl *> m_Controls;
    PK_SceneControl   *m_pParent;
    bool               m_bEnabled;
    bool               m_bVisible;
    bool               m_bUpdateWhenHidden;
    bool               m_bWithInput;
    bool               m_bRemovedFromScene;
    PK_tSceneControlUserData m_userData;
    PK_Effect         *m_pShowEffect;

public:
    // Callbacks
    PK_Callback<PK::PK_IObjectCallback> OnClick;
    PK_Callback<PK::PK_IObjectCallback> OnFlick;
    PK_Callback<PK::PK_IObjectCallback> OnFlickEnded;

protected:
    PK_EffectsBlender *m_pEffectsBlender;

public:
    PK_tSceneControlUserData UserData;

public:
    PK_SceneControl(const PK_String &sName = "");

public:
    ~PK_SceneControl();
    virtual void FreeResources();
    void Load(); // PK_LoadableObject
    void InitFromDataFileRecord(PK_DataFileRecord &record);

protected:
    void InitChildsDataFileRecord(PK_DataFileRecord &record);
    
public:
    virtual void InternalLoad();
    virtual void InternalInitialize();
    virtual void InternalUpdate(const PK_GameTimer &time);
    virtual void InternalDraw();
    virtual void InternalUnload();
    virtual void InternalAddedToScene();
    void AddToLoadingQueue(PK_ObjectLoader &loader);

    // Metodos virtuais, podem ser overriden pelos filhos
    virtual void OnInitialize() {}
    virtual void OnLoad()  {}
    virtual void OnUpdate(const PK_GameTimer &time)  {}
    virtual void OnDraw()  {}
    virtual void OnUnload()  {}
    virtual void UpdateLayout() {}
    virtual void Invalidate() {}
    virtual void Copy(PK_SceneControl & copyFrom);
    virtual void OnMessageReceived(PK_tMessage1 &msg) { }
  
    virtual void AddControl(PK_SceneControl *pControl);
    void RemoveControl(PK_SceneControl *pControl);
    void RemoveAllControls();
    virtual void RemoveControlImmediate(PK_SceneControl *pControl);
    virtual PK_Scene * GetScene();
    PK_SceneControl * GetControl(const PK_String &sName);
    void BringToFront();
    void SendToBack();
    void BringChildToFront(PK_SceneControl &control);
    void SendChildToBack(PK_SceneControl &control);
    virtual void ApplyEffects() { }
    void AddEffect(PK_Effect &effect);
    void RemoveFromScene();
    virtual void InternalControlClicked();
    void SetShowEffect(PK_Effect *pEffect);
    void ActivateShowEffect();
    // Scripting
	virtual void SetCustomAttribute(const PK_String &sName, PK_tScriptValue1 &var) { }

public:
    inline bool WithChilds() { return (m_Controls.GetCount() > 0); }
    
    // AssetContainerName
    inline PK_String GetAssetContainerName() { return m_sAssetContainerName; }
    inline void SetAssetContainerName(PK_String &sName) { m_sAssetContainerName = sName; }

    // Controls
    inline PK_List<PK_SceneControl *> & GetControls() { return m_Controls; }

    // Parent
    inline PK_SceneControl * GetParent() { return m_pParent; }
    virtual void SetParent(PK_SceneControl * pNewParent);

    // Accepts input
    inline bool GetWithInput()
    {
        if (IsVisible() == false)
        {
            return false;
        }
        if (m_pParent == NULL)
        {
            return m_bWithInput;
        }
        if (!m_bWithInput)
        {
            return false;
        }
        
        return m_pParent->GetWithInput();
    }
    inline void SetWithInput(bool bWithInput) { m_bWithInput = bWithInput; }

    // Visible
    inline bool IsVisible() { return m_bVisible; }
    virtual void SetVisible(bool bVisible);

    // Enabled
    inline bool IsEnabled() { return m_bEnabled; }
    virtual inline void SetEnabled(bool bEnabled) { m_bEnabled = bEnabled;}

    inline bool ShouldUpdateWhenHidden() { return m_bUpdateWhenHidden; }
    virtual inline void SetUpdateWhenHidden(bool bValue) { m_bUpdateWhenHidden = bValue; }

    virtual inline bool Is2DControl() { return false; }
    static PK_SceneControl * CreateFromDataFileRecord(PK_DataFileRecord &record);

    inline void SetRemovedFromScene(bool bRemoved) { m_bRemovedFromScene = bRemoved; }
    
    // Callbacks
    virtual void InvokeOnClick()
    {
        if (OnClick.HasCallback())
        {
            OnClick->Execute(*this);
        }
    }
    
    void InvokeOnFlick()
    {
        if (OnFlick.HasCallback())
        {
            OnFlick->Execute(*this);
        }
    }

    void InvokeOnFlickEnded()
    {
        if (OnFlickEnded.HasCallback())
        {
            OnFlickEnded->Execute(*this);
        }
    }

protected:
    void SetCallback(PK_IObjectCallback *pCallback, PK_IObjectCallback **pCallbackToSet);
};

}
#endif
