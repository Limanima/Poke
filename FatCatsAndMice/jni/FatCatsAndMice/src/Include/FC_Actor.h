#ifndef _FCAM_ACTOR_H_
#define _FCAM_ACTOR_H_

#include <PokeEngine.h>
#include "FC_Types.h"
#include "FC_Consts.h"

class FC_Actor: public PK::PK_Sprite
{ 
private:
    FC_eActorType        m_ActorType;
    FC_eActorState       m_State;
    FC_eActorCommand     m_PlayerCommand;
    bool                 m_bCanBeControlled;
    float                m_fAirResistance;

    PK::PK_String		 m_sBodySpriteAssetName;

public:
    PK::PK_Callback<PK::PK_IObjectCallback> OnKilled; // Quando morre
 
public:
    FC_Actor(FC_eActorType type);
    void Copy(PK::PK_SceneControl &copyFrom);
    void OnLoad();
    void OnUpdate(const PK::PK_GameTimer &time);
    void OnMessageReceived(PK::PK_tMessage1 &msg);
    virtual void OnKill() { };
    void ProcessFalling(const PK::PK_GameTimer &time);
    void ProcessGoingLeft(const PK::PK_GameTimer &time);
    void ProcessGoingRight(const PK::PK_GameTimer &time);    
    void MoveLeft();
    void MoveRight();
    void Kill(bool bPlaySound);
    void Kill(int iJumpDirection, bool playSound);
    void SetToFalling(float fAirResistance);
    bool CanBeControlled();
    virtual void SetWithShirt(bool bWithShirt) {}

private:
    void SetupPhysics();

public:
    inline bool IsCat() { return (m_ActorType == ActorType_Cat); }
    inline bool IsDog() { return (m_ActorType == ActorType_Dog); }
    inline bool IsMouse() { return (m_ActorType == ActorType_Mouse); }
    inline bool IsObject() { return (m_ActorType == ActorType_Object); }
    
    inline FC_eActorType GetActorType() const { return m_ActorType; }
    inline bool IsFalling() { return (m_State == ActorState_Falling); }
    inline bool IsDead() { return (m_State == ActorState_Killed); }

	inline void SetBodySpriteAssetName(const PK::PK_String &sName) { m_sBodySpriteAssetName = sName; }
    virtual inline bool CanWearShirt() { return false; }

    static unsigned int GetActorCollisionBit(FC_eActorType actorType);

};

#endif
