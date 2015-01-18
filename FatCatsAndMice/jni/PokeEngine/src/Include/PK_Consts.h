#ifndef _PK_CONSTS_H_
#define _PK_CONSTS_H_

#ifdef _WIN32
    #ifdef POKE_EXPORT
        #define POKEENGINE_LIB __declspec(dllexport)
    #else
        #define POKEENGINE_LIB __declspec(dllimport)
    #endif
#else
    #define POKEENGINE_LIB
#endif


// Const strings
#define PK_POKE_ENGINE_NAME              "__PK_pokeEngine__"
#define PK_SCENE_ROOT_NAME               "__PK_sceneRoot__"
#define PK_SYSTEM_SCENE_NAME             "__PK_systemScene__"
#define PK_DEFAULT_2DCAMERA_NAME         "__PK_2dcamera__"
#define PK_BASIC_SHADER_NAME             "__PK_basicShader__"
#define PK_TEXTURE_SHADER_NAME           "__PK_textureShader__"
#define PK_SCENE_MANAGER_NAME            "__PK_sceneManager__"
#define PK_AD_MANAGER_NAME               "__PK_adManager__"
#define PK_LIBRARY_NAME                  "__PK_library__"
#define PK_ASSET_MANAGER_NAME            "__PK_assetManager__"
#define PK_SDL_MANAGER_NAME              "__PK_sdlManager__"
#define PK_INPUT_MANAGER_NAME            "__PK_inputManager__"
#define PK_AUDIO_MANAGER_NAME            "__PK_audioManager__"
#define PK_ASSET_CONTAINER_NAME          "__PK_globalAssetContainer__"
#define PK_OBJECT_LOADER_NAME            "__PK_objectLoader__"
#define PK_RENDER_MANAGER_NAME           "__PK_renderManager__"   
#define PK_FPS_COUNTER_NAME              "__PK_FPSCounterProfilerItem__"
#define PK_POINTER_INFO_NAME             "__PK_PointerInfoName__"
#define PK_PROFILER_NAME                 "__PK_profiler__"
#define PK_ASSET_MANAGER_PROFILER_ITEM_NAME "__PK_assetManagerProfilerItem__"
#define PK_LOADED_OBJS_PROFILER_ITEM_NAME "__PK_loadedObsProfilerItem__"
#define PK_PHYSICS_MANAGER_NAME          "__PK_physicsManager__"
#define PK_PHYSICS_MANAGER_CAMERA        "__PK_physicsManagerCamera__"
#define PK_REMOTE_DEBUGGER_NAME          "__PK_remoteDebuggerClient__"
#define PK_POKE_GAME_DATA_NAME           "__PK_pokeGameData__"
#define PK_SPLASH_SCENE_NAME             "__PK_splashScene__"
#define PK_AUDIO_MANAGER_SETTINGS_NAME   "__PK_audioManagerSettings__"
#define PK_PHYSICS_MANAGER_SETTINGS_NAME "__PK_physicsManagerSettings__"
#define PK_POKE_SETTINGS_NAME            "__PK_pokeSettings__"
#define PK_SCENE_MANAGER_SETTINGS_NAME   "__PK_sceneManagerSettings__"
#define PK_PROFILER_SETTINGS_NAME        "__PK_profilerSettings__"
#define PK_POKEGAMEDATA_NAME             "__PK_pokeGameData__"

// File extensions
#define PK_SPRITESET_EXTENSION "ss"
#define PK_FONT_EXTENSION "fnt"
#define PK_STRING_ASSET_EXTENSION "str"
#define PK_IMAGE_TYPE1_EXTENSION "png" 
#define PK_SOUND_TYPE1_EXTENSION "ogg"
#define PK_MUSIC_TYPE1_EXTENSION "ogg"
#define PK_SCENE_EXTENSION "scn"
#define PK_OBJECT_PROPS_EXTENSION "objProp"
#define PK_SETTINGS_EXTENSION "cfg"
#define PK_SCRIPT_EXTENSION "pks"

// Filenames
#define PK_POKE_SETTINGS_FILE             "res/poke/poke_engine." PK_SETTINGS_EXTENSION
#define PK_AUDIOMANAGER_SETTINGS_FILE     "res/poke/poke_engine." PK_SETTINGS_EXTENSION
#define PK_SCENEMANAGER_SETTINGS_FILE	  "res/poke/poke_engine." PK_SETTINGS_EXTENSION
#define PK_PHYISICSMANAGER_SETTINGS_FILE  "res/poke/poke_engine." PK_SETTINGS_EXTENSION
#define PK_PROFILER_SETTINGS_FILE         "res/poke/poke_engine." PK_SETTINGS_EXTENSION
#define PK_POKE_GAME_DATA_FILE            "poke_game_data." PK_SETTINGS_EXTENSION
// 
#define PK_TRUE_STR "true"
#define PK_FALSE_STR "false"

#define PK_TYPE_PREFIX "PK_"
#define PK_FONT_NAME "res/poke/poke_engine." PK_FONT_EXTENSION

#define PK_DEFAULT_GRAVITY  PK_Vector2(0.0f, -9.8f)

// Mensagens
#define PK_MSG_BODY_COLLISION    1
#define PK_MSG_REMOVE_CONTROL    2
#define PK_MSG_ADD_CONTROL       3

#define PK_TICKS_PER_DAY           864000000000L
#define PK_TICKS_PER_TENTH_SECOND  1000000L
#define PK_TICKS_PER_HOUR          36000000000L
#define PK_TICKS_PER_MILLISECOND   10000L
#define PK_TICKS_PER_SECOND        10000000L
#define PK_TICKS_PER_MINUTE        600000000L
#define PK_MAX_SECONDS             922337203685L
#define PK_MIN_SECONDS            -922337203685L
#define PK_MAX_MILLISECONDS        922337203685477L
#define PK_MIN_MILLISECONDS       -922337203685477L
#define PK_MILLISECONDS_PER_TICK   0.0001
#define PK_MILLIS_PER_DAY          86400000
#define PK_MILLIS_PER_SECOND       1000
#define PK_MILLIS_PER_MINUTE       60000
#define PK_MILLIS_PER_HOUR         3600000
#define PK_DAYS_PER_400_YEARS      146097
#define PK_DAYS_PER_100_YEARS      36524
#define PK_DAYS_PER_4_YEARS        1461
#define PK_DAYS_PER_YEAR           365
#define PK_MAX_MILLIS              315537897600000L
#define PK_MAX_TICKS               3155378975999999999L
#define PK_TICKS_MASK              4611686018427387903UL
#define PK_FLAGS_MASK              13835058055282163712UL


#define PK_LOG_TAG (char *)"PK"

#define PK_MESSAGE_NO_NET_LEADERBOARDS  "You have to be connected to the internet to access the leaderboards."
#define PK_CAPTION_NO_NET               "No Internet"

#define PK_FREE(obj) \
  if (obj != NULL) \
    { \
        obj->Release(); \
        obj = NULL; \
    }
#endif
