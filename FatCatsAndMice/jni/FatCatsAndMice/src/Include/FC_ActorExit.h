#ifndef _FCAM_ACTOREXIT_H_
#define _FCAM_ACTOREXIT_H_

#include <PokeEngine.h>
#include "FC_Types.h"
#include "FC_Actor.h"

class FC_ActorExit: public PK::PK_2DSceneControl
{ 
private:
    PK::PK_Panel   *m_pPnlBound;
    PK::PK_Panel   *m_pPnlExit;
    FC_eActorType   m_ActorAccepted;
    FC_eSide        m_Side;
    FC_Actor       *m_pLastActorToExit;

public:
    PK::PK_Callback<PK::PK_IObjectCallback> OnActorExited;  // Quando um actor sai pela saida

public:
    FC_ActorExit(const PK::PK_String &sName, FC_eSide side);
    void OnInitialize();

private:
    void Bound_Collision(PK::PK_Body &body);
    void Exit_Collision(PK::PK_Body &body);

public:
    void SetActorAccepted(FC_eActorType actorAccepted); 
    inline FC_Actor * GetLastActorToExit() { return m_pLastActorToExit; }
    inline FC_eActorType GetActorType() { return m_ActorAccepted; }
    inline FC_eSide GetSide() { return m_Side; }
};

#endif
