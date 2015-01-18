
LOCAL_PATH := $(call my-dir)
 

include $(CLEAR_VARS)

LOCAL_MODULE := FatCatsAndMice

PROJ_SOURCE_PATH := ./src
SDL_PATH:=../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/src/include \
					$(LOCAL_PATH)/../PokeEngine/src/include \
                    $(NDK_ROOT)/sources/cxx-stl/stlport/stlport

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
                   $(PROJ_SOURCE_PATH)/FC_Actor.cpp \
                   $(PROJ_SOURCE_PATH)/FC_ActorExit.cpp \
                   $(PROJ_SOURCE_PATH)/FC_AnimalActor.cpp \
                   $(PROJ_SOURCE_PATH)/FC_BaseScene.cpp \
                   $(PROJ_SOURCE_PATH)/FC_Button.cpp \
                   $(PROJ_SOURCE_PATH)/FC_CatActor.cpp \
   			       $(PROJ_SOURCE_PATH)/FC_DogActor.cpp \
				   $(PROJ_SOURCE_PATH)/FC_Fire.cpp \
                   $(PROJ_SOURCE_PATH)/FC_Game.cpp \
				   $(PROJ_SOURCE_PATH)/FC_GameMain.c \
				   $(PROJ_SOURCE_PATH)/FC_GameplayScene.cpp \
				   $(PROJ_SOURCE_PATH)/FC_GameSession.cpp \
				   $(PROJ_SOURCE_PATH)/FC_GameSettings.cpp \
				   $(PROJ_SOURCE_PATH)/FC_GlobalHUD.cpp \
				   $(PROJ_SOURCE_PATH)/FC_Hud.cpp \
				   $(PROJ_SOURCE_PATH)/FC_InanimateActor.cpp \
				   $(PROJ_SOURCE_PATH)/FC_MainMenuScene.cpp \
				   $(PROJ_SOURCE_PATH)/FC_MouseActor.cpp \
				   $(PROJ_SOURCE_PATH)/FC_ObjectActor.cpp \
				   $(PROJ_SOURCE_PATH)/FC_Player.cpp \
				   $(PROJ_SOURCE_PATH)/FC_ScoreBoard.cpp \
				   $(PROJ_SOURCE_PATH)/FC_ScorePoint.cpp \
				   $(PROJ_SOURCE_PATH)/FC_Sign.cpp \
				   $(PROJ_SOURCE_PATH)/FC_Stars.cpp \
				   $(PROJ_SOURCE_PATH)/FC_Title.cpp \
				   $(PROJ_SOURCE_PATH)/FC_Tutorial.cpp \
				   $(PROJ_SOURCE_PATH)/FC_TypeConverters.cpp 

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image Box2D SDL2_net PokeEngine

LOCAL_LDLIBS := -lGLESv1_CM -llog

LOCAL_CFLAGS += -D_STLP_USE_NEWALLOC -DPOKE_DEBUG -fexceptions

APP_CFLAGS += -g

include $(BUILD_SHARED_LIBRARY)
