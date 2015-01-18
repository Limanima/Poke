// Header que deve ser incluido nos jogos desenvolvidos com o engine
#ifndef _POKEENGINE_H_
#define _POKEENGINE_H_

#include "glm/glm.hpp"
#include "PK_Consts.h"
#include "PK_Globals.h"
#include "PK_String.h"
#include "PK_Object.h"
#include "PK_PokeEngine.h"
#include "PK_DataFile.h"
#include "PK_XmlDataFileWriter.h"
#include "PK_XmlDataFileReader.h"
#include "PK_FileWriter.h"
#include "PK_SystemException.h"
#include "PK_Environment.h"
#include "PK_Web.h"
#include "PK_Dictionary.h"
#include "PK_MemoryPool.h"

// Managers
#include "PK_RenderManager.h"
#include "PK_SceneManager.h"
#include "PK_AdManager.h"
#include "PK_InputManager.h"
#include "PK_PhysicsManager.h"
#include "PK_AudioManager.h"

#include "PK_Settings.h"
#include "PK_Game.h"
#include "PK_ConsoleApp.h"
#include "PK_GameApp.h"
#include "PK_Console.h"
#include "PK_Log.h"
#include "PK_File.h"
#include "PK_Path.h"

// Scenes & controls
#include "PK_Scene.h"
#include "PK_Sprite.h"
#include "PK_Image.h"
#include "PK_Label.h"
#include "PK_Panel.h"
#include "PK_Button.h"
#include "PK_Script.h"
#include "PK_LoadingIcon.h"
#include "PK_Sprite.h"
#include "PK_TimerControl.h"
#include "PK_OfflineAdBanner.h"
#include "PK_Player.h"

// Assets
#include "PK_SoundAsset.h"
#include "PK_MusicAsset.h"
#include "PK_ObjectPropertiesAsset.h"
#include "PK_ScriptAsset.h"
#include "PK_FileAsset.h"

// Scripting
#include "PK_tScriptVariable.h"

#include "PK_GameTimer.h"
#include "PK_RandomGenerator.h"

// Callbacks
#include "PK_Callback.h"
#include "PK_MessageBoxCallback.h"

#include "PK_Body.h"
#include "PK_Leaderboard.h"
#include "PK_ClassFactory.h"
#include "PK_AdBanner.h"
#include "PK_MessageBox.h"
#include "PK_Library.h"
#include "PK_LibraryItem.h"

// Effects
#include "PK_Effect.h"
#include "PK_ColorEffect.h"
#include "PK_ButtonPressEffect.h"
#include "PK_GravityEffect.h"
#include "PK_LinearMoveEffect.h"
#include "PK_MotionEffect.h"

#include "PK_Rate.h"

namespace PK
{
    PK_App * CreateApp();
    PK_Game * CreateGame();
}

#endif