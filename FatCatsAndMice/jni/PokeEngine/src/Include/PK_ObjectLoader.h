#ifndef _PK_OBJECTLOADER_H_
#define _PK_OBJECTLOADER_H_

#include "PK_Object.h"
#include "PK_LoadableObject.h"
#include "PK_List.h"
#include "PK_GameTimer.h"
namespace PK {

class PK_LoadingIcon;

// Classe que mantem uma queue para fazer leitura de objectos que suportem PK_LoadableObject
// Esta classe le um objecto de cada vez da queue de leitura (atraves do metodo Load() de PK_LoadableObject
class PK_ObjectLoader : public PK_Object
{
protected:
    bool                         m_bIsLoading;
    PK_LoadingIcon              *m_pLoadingIcon;
    PK_List<PK_LoadableObject *> m_LoadingQueue;

public:
    PK_ObjectLoader();
    ~PK_ObjectLoader();
    void OnUpdate(const PK_GameTimer &time);
    void OnDraw();
    void OnUnload();
    void StartLoading();
    void EndLoading();
    inline bool IsLoading() { return m_bIsLoading; }
    void SetLoadingIcon(PK_LoadingIcon *pIcon);
    void AddToQueue(PK_LoadableObject &obj);
    void ClearQueue();
    void LoadQueuedObject();
    inline bool IsQueueEmpty() { return m_LoadingQueue.GetCount() == 0; }
};
    
} // namespace

#endif
