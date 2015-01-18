#ifndef _PK_SCENE_H_
#define _PK_SCENE_H_

#include "PK_Consts.h"
#include "PK_LoadableObject.h"
#include "PK_SceneRoot.h"
#include "PK_SceneControl.h"
#include "PK_ObjectCallback.h"
#include "PK_ObjectLoader.h"
#include "PK_DataFiles.h"

namespace PK {

// Base de todas as classes do engine
// 
class PK_SceneRoot;
class PK_SceneControl;
class PK_PhysicsManager;
class PK_Component;
class PK_Camera;

class PK_Scene : public PK_LoadableObject
{
private:
    PK_SceneRoot   *m_pSceneRoot;
    bool            m_bOpened;
    bool            m_bActive;
    bool            m_bVisible;
    bool            m_bUpdateStarted;

    // Guarda o controlo que foi clicado/touchado
    // O update nos controlos corre do que est� por baixo at� ao que est� mais � frente
    // Queremos que seja lancado apenas um click (mesmo haja controlos sobrepostos) e que o click seja no controlo que esta mais
    // No update guaramos aqui o ultimo controlo que tenha sido tocado (que no final ha-de ser o que esta por cima)
    PK_SceneControl *m_pClickedControl;
    PK_SceneControl *m_pFlickedControl;
   // PK_List<PK_SceneControl *>  m_ControlsToRemove;
    PK_List<PK_Component *>     m_Components;
    PK_PhysicsManager          *m_pPhysicsManager;
    PK_Camera                  *m_pCamera;

	// Messaging
    PK_List<PK_tMessage> m_PostUpdateMessages; // Mensagens a serem processadas apos o update
    PK_List<PK_tMessage1> m_BroadcastMessages; // 

public:
    PK_Scene(const PK_String &sName);
    ~PK_Scene();

    void Load(); // PK_LoadableObject
    virtual void InitFromDataFileRecord(PK_DataFileRecord &record);
    
    // Metodos internos, supostamente s�o para uso interno do engine. Problema: os jogos tamb�m os v�em...
    void InternalInitialize();
    void InternalLoad();
    void InternalLoad(PK_ObjectLoader &loader);
    void InternalUpdate(const PK_GameTimer &time);
    void InternalDraw();
    void InternalOpen();
    void InternalClose();
    void InternalUnload();
    void AddToLoadingQueue(PK_ObjectLoader &loader);
    virtual void OnInitialize() { }
    virtual void OnLoad() { }
    virtual void OnOpen() { }
    virtual void OnUpdate(const PK_GameTimer &time) { }
    virtual void OnDraw() { }
    virtual void OnClose() { }
    virtual void OnUnload() { }
    virtual void OnOpenTrasitionEnded() { }
    void AddControl(PK_SceneControl * pControl);
    void RemoveControl(PK_SceneControl *pControl);
    // Procura controlo por nome, lanca excepcao se nao encontrar
    PK_SceneControl & GetControl(const PK_String &sName);
    // Faz o mesmo que GetControl() mas n lanca excepcao se nao encontrar
    PK_SceneControl * FindControl(const PK_String &sName);
    void AddComponent(PK_Component &component);
    void SetWithPhysics(bool bWithPhysics);

    // Click callback
    void SetOnClickCallback(PK_IObjectCallback *pCallback);

    // Suporte para imagem de background
    void SetBackgroundImage(PK_SpriteAsset *pSprite);
    void SetBackgroundImage(const PK_String &sAssetName); 

    // Messaging
    void AddPostUpdateMessage(const PK_tMessage & message);
    void ProcessPostUpdateMessages();
	void BroadcastMessage(unsigned int uiMsg, unsigned int uiCode = 0, unsigned long ulParam = 0);

	PK_String GetAssetContainerName();

private:
	void SendBroadcastMessages();
	void SendBroadcastMessages(PK_SceneControl &currentControl);

public:
    inline bool WithPhysics() { return (m_pPhysicsManager != NULL); }
    inline PK_PhysicsManager * GetPhysicsManager() { return m_pPhysicsManager; }
    inline bool IsClosed() { return !m_bOpened; }
    inline bool IsOpen() { return m_bOpened; }
    inline bool IsActive() { return m_bActive; }
    inline void SetActive(bool bActive) { m_bActive = bActive; }
    inline bool IsVisible() { return m_bVisible; }
    inline void SetVisible(bool bVisible) { m_bVisible = bVisible; }
    inline void SetWithInput(bool bWithInput) { m_pSceneRoot->SetWithInput(bWithInput); }
    inline void DisableInput() { m_pSceneRoot->SetWithInput(false); }
    inline void EnableInput() { m_pSceneRoot->SetWithInput(true); }
    inline void SetClickedControl(PK_SceneControl *pControl) { m_pClickedControl = pControl; }
    inline void SetFlickedControl(PK_SceneControl *pControl) { m_pFlickedControl = pControl; }
  
    inline void SetBackgroundColor(const PK_Color &color)
    {
        m_pSceneRoot->SetBackgroundColor(color);
    }

    PK_Camera & GetCamera();
    void SetCamera(PK_Camera * pCamera);

    PK_String GetFilename();

private:
 //   void PurgeRemovedControls();
    void UpdateComponents(const PK_GameTimer &time);
    void DrawComponents();
};

}

#endif
