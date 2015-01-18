#ifndef _FCAM_TYPES_H_
#define _FCAM_TYPES_H_

enum FC_eMainMenuType
{
    MainMenuType_Intro,
    MainMenuType_GameOver,
};

enum FC_eSide
{
    Side_Left,
    Side_Right,
};


enum FC_eActorType
{
    ActorType_Cat,
    ActorType_Mouse,
    ActorType_Dog,
    ActorType_Object
};

enum FC_eObjectActorType
{
	ObjectActorType_None,
    ObjectActorType_Fridge,
    ObjectActorType_Microwave,
    ObjectActorType_Pizza
};

enum FC_eSignType
{
    SignType_Cat,
    SignType_Mouse,
    SignType_Play,
    SignType_Leaderboards
};


enum FC_eActorState
{
    ActorState_None,
    ActorState_Falling,
    ActorState_GoingLeft,
    ActorState_GoingRight,
    ActorState_Killed
};

enum FC_eActorCommand
{
    ActorCommand_None,
    ActorCommand_GoLeft,
    ActorCommand_GoRight,
    ActorCommand_WaitForNextActor,
};

enum FC_eGameplayState
{
    GameplayState_StartingUp,
    GameplayState_NotStarted,
    GameplayState_StartNew,
    GameplayState_Running,
    GameplayState_Tutorial,
    GameplayState_Gameover
};

enum FC_eObjectType
{
    ObjectType_Actor,
    ObjectType_Fire
};


enum FC_eButtonType
{
    ButtonType_Play,
    ButtonType_Leaderboards
};

enum FC_eDoorState 
{
    DoorState_Idle,
    DoorState_Closing,
    DoorState_Opening
};

enum FC_eTimmingLevel
{
  TimmingLevel_Mouse2,
  TimmingLevel_Mouse3,
  TimmingLevel_Cat2,
  TimmingLevel_Cat3,
  TimmingLevel_Dog,
  TimmingLevel_Inanimate,
  TimmingLevel_Shirts
};

struct FC_tTimmingEntry
{
    FC_eTimmingLevel _level;
    int _iTimeInMsecs;
};
#endif
