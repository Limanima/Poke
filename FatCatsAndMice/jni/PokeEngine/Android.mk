
LOCAL_PATH := $(call my-dir)

 
include $(CLEAR_VARS)

LOCAL_MODULE := PokeEngine
 
POKE_ENGINE_PATH := ./src

LOCAL_C_INCLUDES := $(LOCAL_PATH)/src/include \
                    $(NDK_ROOT)/sources/cxx-stl/stlport/stlport \
                    $(LOCAL_PATH)/../SDL_net/ \
                    $(LOCAL_PATH)/../SDL/ \
                    $(LOCAL_PATH)/../SDL2_mixer/ \
                    $(LOCAL_PATH)/src \
                    $(LOCAL_PATH)/../Box2D/src
                    
					 
# Add your application source files here...
LOCAL_SRC_FILES := $(POKE_ENGINE_PATH)/Android/PK_JNIInterface.cpp \
				   $(POKE_ENGINE_PATH)/PK_2DSceneControl.cpp \
				   $(POKE_ENGINE_PATH)/PK_AdBanner.cpp \
                   $(POKE_ENGINE_PATH)/PK_AdManager.cpp \
                   $(POKE_ENGINE_PATH)/PK_AppStore.cpp \
                   $(POKE_ENGINE_PATH)/PK_AndroidActivity.cpp \
                   $(POKE_ENGINE_PATH)/PK_AndroidAdBanner.cpp \
                   $(POKE_ENGINE_PATH)/PK_AndroidAppStore.cpp \
                   $(POKE_ENGINE_PATH)/PK_AndroidLeaderboard.cpp \
                   $(POKE_ENGINE_PATH)/PK_AndroidMessageBox.cpp \
                   $(POKE_ENGINE_PATH)/PK_AndroidPlayer.cpp \
                   $(POKE_ENGINE_PATH)/PK_AndroidWeb.cpp \
                   $(POKE_ENGINE_PATH)/PK_ArgumentOutOfRangeException.cpp \
                   $(POKE_ENGINE_PATH)/PK_Asset.cpp \
                   $(POKE_ENGINE_PATH)/PK_AssetContainer.cpp \
                   $(POKE_ENGINE_PATH)/PK_AssetManager.cpp \
                   $(POKE_ENGINE_PATH)/PK_AssetManagerProfilerItem.cpp \
                   $(POKE_ENGINE_PATH)/PK_AudioManager.cpp \
                   $(POKE_ENGINE_PATH)/PK_AudioManagerSettings.cpp \
                   $(POKE_ENGINE_PATH)/PK_App.cpp \
                   $(POKE_ENGINE_PATH)/PK_Body.cpp \
                   $(POKE_ENGINE_PATH)/PK_Box2DBody.cpp \
				   $(POKE_ENGINE_PATH)/PK_Box2DContactListener.cpp \
                   $(POKE_ENGINE_PATH)/PK_Box2DPhysicsManager.cpp \
                   $(POKE_ENGINE_PATH)/PK_Box2DRenderer.cpp \
                   $(POKE_ENGINE_PATH)/PK_Button.cpp \
                   $(POKE_ENGINE_PATH)/PK_ButtonPressEffect.cpp \
				   $(POKE_ENGINE_PATH)/PK_Camera.cpp \
				   $(POKE_ENGINE_PATH)/PK_ClassFactory.cpp \
				   $(POKE_ENGINE_PATH)/PK_ColorEffect.cpp \
				   $(POKE_ENGINE_PATH)/PK_CommandAttributes.cpp \
				   $(POKE_ENGINE_PATH)/PK_Component.cpp \
				   $(POKE_ENGINE_PATH)/PK_Console.cpp \
				   $(POKE_ENGINE_PATH)/PK_ConsoleApp.cpp \
				   $(POKE_ENGINE_PATH)/PK_DataFieldFormatException.cpp \
				   $(POKE_ENGINE_PATH)/PK_DataFile.cpp \
				   $(POKE_ENGINE_PATH)/PK_DataFileAsset.cpp \
				   $(POKE_ENGINE_PATH)/PK_DataFileField.cpp \
				   $(POKE_ENGINE_PATH)/PK_DataFileRecord.cpp \
				   $(POKE_ENGINE_PATH)/PK_DrawableComponent.cpp \
				   $(POKE_ENGINE_PATH)/PK_Effect.cpp \
				   $(POKE_ENGINE_PATH)/PK_EffectsBlender.cpp \
				   $(POKE_ENGINE_PATH)/PK_Environment.cpp \
				   $(POKE_ENGINE_PATH)/PK_EventManager.cpp \
				   $(POKE_ENGINE_PATH)/PK_Exception.cpp \
				   $(POKE_ENGINE_PATH)/PK_File.cpp \
				   $(POKE_ENGINE_PATH)/PK_FileAsset.cpp \
				   $(POKE_ENGINE_PATH)/PK_FileReader.cpp \
				   $(POKE_ENGINE_PATH)/PK_FileWriter.cpp \
				   $(POKE_ENGINE_PATH)/PK_FileNotFoundException.cpp \
				   $(POKE_ENGINE_PATH)/PK_FontAsset.cpp \
				   $(POKE_ENGINE_PATH)/PK_FPSCounterProfilerItem.cpp \
				   $(POKE_ENGINE_PATH)/PK_Game.cpp \
				   $(POKE_ENGINE_PATH)/PK_GameException.cpp \
				   $(POKE_ENGINE_PATH)/PK_GLESBasicShader.cpp \
				   $(POKE_ENGINE_PATH)/PK_GLESException.cpp \
				   $(POKE_ENGINE_PATH)/PK_GLESRenderManager.cpp \
				   $(POKE_ENGINE_PATH)/PK_GLESShader.cpp \
				   $(POKE_ENGINE_PATH)/PK_GLESTextureShader.cpp \
				   $(POKE_ENGINE_PATH)/PK_GravityEffect.cpp \
				   $(POKE_ENGINE_PATH)/PK_Image.cpp \
				   $(POKE_ENGINE_PATH)/PK_InputManager.cpp \
				   $(POKE_ENGINE_PATH)/PK_InvalidObjectException.cpp \
				   $(POKE_ENGINE_PATH)/PK_JNIException.cpp \
				   $(POKE_ENGINE_PATH)/PK_Label.cpp \
				   $(POKE_ENGINE_PATH)/PK_LabelCmd.cpp \
				   $(POKE_ENGINE_PATH)/PK_Leaderboard.cpp \
				   $(POKE_ENGINE_PATH)/PK_Library.cpp \
				   $(POKE_ENGINE_PATH)/PK_LibraryItem.cpp \
				   $(POKE_ENGINE_PATH)/PK_LinearMoveEffect.cpp \
				   $(POKE_ENGINE_PATH)/PK_LoadableObject.cpp \
				   $(POKE_ENGINE_PATH)/PK_LoadedObjsProfilerItem.cpp \
				   $(POKE_ENGINE_PATH)/PK_Log.cpp \
				   $(POKE_ENGINE_PATH)/PK_LoopCmd.cpp \
				   $(POKE_ENGINE_PATH)/PK_MathHelper.cpp \
				   $(POKE_ENGINE_PATH)/PK_MemoryBuffer.cpp \
				   $(POKE_ENGINE_PATH)/PK_MemoryBufferReader.cpp \
				   $(POKE_ENGINE_PATH)/PK_MessageBox.cpp \
				   $(POKE_ENGINE_PATH)/PK_MotionEffect.cpp \
				   $(POKE_ENGINE_PATH)/PK_MoveCmd.cpp \
				   $(POKE_ENGINE_PATH)/PK_Mutex.cpp \
				   $(POKE_ENGINE_PATH)/PK_NotImplementedException.cpp \
				   $(POKE_ENGINE_PATH)/PK_NullArgumentException.cpp \
				   $(POKE_ENGINE_PATH)/PK_Object.cpp \
				   $(POKE_ENGINE_PATH)/PK_ObjectLoader.cpp \
				   $(POKE_ENGINE_PATH)/PK_ObjectPropertiesAsset.cpp \
				   $(POKE_ENGINE_PATH)/PK_OfflineAdBanner.cpp \
				   $(POKE_ENGINE_PATH)/PK_OutOfMemoryException.cpp \
				   $(POKE_ENGINE_PATH)/PK_OverflowException.cpp \
				   $(POKE_ENGINE_PATH)/PK_Panel.cpp \
				   $(POKE_ENGINE_PATH)/PK_Path.cpp \
				   $(POKE_ENGINE_PATH)/PK_PauseCmd.cpp \
				   $(POKE_ENGINE_PATH)/PK_PhysicsManager.cpp \
				   $(POKE_ENGINE_PATH)/PK_PhysicsManagerSettings.cpp \
				   $(POKE_ENGINE_PATH)/PK_Player.cpp \
				   $(POKE_ENGINE_PATH)/PK_PlaySoundCmd.cpp \
				   $(POKE_ENGINE_PATH)/PK_PointerInfoProfilerItem.cpp \
				   $(POKE_ENGINE_PATH)/PK_PokeEngine.cpp \
				   $(POKE_ENGINE_PATH)/PK_PokeGameData.cpp \
				   $(POKE_ENGINE_PATH)/PK_PokeSettings.cpp \
				   $(POKE_ENGINE_PATH)/PK_PopUpEffect.cpp \
				   $(POKE_ENGINE_PATH)/PK_Profiler.cpp \
				   $(POKE_ENGINE_PATH)/PK_ProfilerItem.cpp \
				   $(POKE_ENGINE_PATH)/PK_ProfilerMenu.cpp \
				   $(POKE_ENGINE_PATH)/PK_ProfilerSettings.cpp \
				   $(POKE_ENGINE_PATH)/PK_RandomGenerator.cpp \
				   $(POKE_ENGINE_PATH)/PK_Rate.cpp \
				   $(POKE_ENGINE_PATH)/PK_RemoteDebuggerClient.cpp \
				   $(POKE_ENGINE_PATH)/PK_RenderManager.cpp \
				   $(POKE_ENGINE_PATH)/PK_RotateCmd.cpp \
				   $(POKE_ENGINE_PATH)/PK_Scene.cpp \
				   $(POKE_ENGINE_PATH)/PK_SceneControl.cpp \
				   $(POKE_ENGINE_PATH)/PK_SceneManager.cpp \
				   $(POKE_ENGINE_PATH)/PK_SceneManagerSettings.cpp \
				   $(POKE_ENGINE_PATH)/PK_SceneRoot.cpp \
				   $(POKE_ENGINE_PATH)/PK_SceneTransition.cpp \
				   $(POKE_ENGINE_PATH)/PK_Script.cpp \
				   $(POKE_ENGINE_PATH)/PK_ScriptAsset.cpp \
				   $(POKE_ENGINE_PATH)/PK_ScriptCommand.cpp \
				   $(POKE_ENGINE_PATH)/PK_ScriptCompiler.cpp \
				   $(POKE_ENGINE_PATH)/PK_StringAsset.cpp \
				   $(POKE_ENGINE_PATH)/PK_SDLAudioManager.cpp \
				   $(POKE_ENGINE_PATH)/PK_SDLException.cpp \
				   $(POKE_ENGINE_PATH)/PK_SDLInputManager.cpp \
				   $(POKE_ENGINE_PATH)/PK_SDLManager.cpp \
				   $(POKE_ENGINE_PATH)/PK_SDLMusicAsset.cpp \
				   $(POKE_ENGINE_PATH)/PK_SDLRenderManager.cpp \
				   $(POKE_ENGINE_PATH)/PK_SDLSoundAsset.cpp \
				   $(POKE_ENGINE_PATH)/PK_SDLTCPSocket.cpp \
				   $(POKE_ENGINE_PATH)/PK_SDLTextureAsset.cpp \
				   $(POKE_ENGINE_PATH)/PK_SelectCmd.cpp \
				   $(POKE_ENGINE_PATH)/PK_SetAttributeCmd.cpp \
				   $(POKE_ENGINE_PATH)/PK_Settings.cpp \
				   $(POKE_ENGINE_PATH)/PK_SplashScene.cpp \
				   $(POKE_ENGINE_PATH)/PK_Sprite.cpp \
			       $(POKE_ENGINE_PATH)/PK_SpriteAsset.cpp \
			       $(POKE_ENGINE_PATH)/PK_SpriteSetAsset.cpp \
				   $(POKE_ENGINE_PATH)/PK_SystemException.cpp \
				   $(POKE_ENGINE_PATH)/PK_tAABoundingSquare.cpp \
				   $(POKE_ENGINE_PATH)/PK_tBoundingCircle.cpp \
				   $(POKE_ENGINE_PATH)/PK_tBoundingSquare.cpp \
				   $(POKE_ENGINE_PATH)/PK_TCPClient.cpp \
				   $(POKE_ENGINE_PATH)/PK_TCPServer.cpp \
				   $(POKE_ENGINE_PATH)/PK_tDateTime.cpp \
				   $(POKE_ENGINE_PATH)/PK_Thread.cpp \
				   $(POKE_ENGINE_PATH)/PK_Timer.cpp \
				   $(POKE_ENGINE_PATH)/PK_TimerControl.cpp \
				   $(POKE_ENGINE_PATH)/PK_tScriptValue.cpp \
				   $(POKE_ENGINE_PATH)/PK_tSize.cpp \
				   $(POKE_ENGINE_PATH)/PK_tSpriteFrame.cpp \
				   $(POKE_ENGINE_PATH)/PK_tTimeSpan.cpp \
				   $(POKE_ENGINE_PATH)/PK_tViewport.cpp \
				   $(POKE_ENGINE_PATH)/PK_TypeConverters.cpp \
				   $(POKE_ENGINE_PATH)/PK_Types.cpp \
				   $(POKE_ENGINE_PATH)/PK_Web.cpp \
				   $(POKE_ENGINE_PATH)/PK_XmlDataFileReader.cpp \
				   $(POKE_ENGINE_PATH)/PK_XmlDataFileWriter.cpp \
	               $(POKE_ENGINE_PATH)/tinyxml2.cpp 
	                              
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer Box2D SDL2_net

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

LOCAL_CFLAGS += -D_STLP_USE_NEWALLOC -DPOKE_ANDROID -DPOKE_DEBUG -fexceptions

APP_CFLAGS += -g -ggdb 

include $(BUILD_SHARED_LIBRARY)
