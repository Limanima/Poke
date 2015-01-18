#ifndef _FCAM_CONSTS_H
#define _FCAM_CONSTS_H

#define FCAM_SETTINGS_FILE "res/game-settings"

// Numero total de animais na especie
#define FCAM_TOTAL_CATS      3
#define FCAM_TOTAL_MICE      3
#define FCAM_TOTAL_INANIMATE 4

// Inanimate objects
#define FCAM_FRIDGE   0
#define FCAM_CHEESE   1
#define FCAM_ELEPHANT 2
#define FCAM_FISH     3

// Sprite assets
#define FCAM_SPRITESET_BACKGROUND         "res/sprites/sprites-3/Background"
#define FCAM_SPRITESET_TITLE              "res/sprites/sprites-4/Title"
#define FCAM_SPRITE_FENCE                 "res/sprites/sprites-4/Fence"
#define FCAM_SPRITE_SCOREBOARD            "res/sprites/sprites-4/ScoreBoard"
#define FCAM_SPRITE_SNAILS_PAID_AD        "res/sprites/sprites-6/SnailsPaid"
#define FCAM_SPRITE_SNAILS_FREE_AD        "res/sprites/sprites-6/SnailsFree"
#define FCAM_SPRITE_LIMANIMA_AD           "res/sprites/sprites-1/AdBanner"

// Cat
#define FCAM_SPRITESET_CAT_FALLING        "res/sprites/sprites-1/CatFalling%d"
#define FCAM_SPRITESET_CAT_SAD_HEAD       "res/sprites/sprites-1/Cat%dSadHead"
#define FCAM_SPRITESET_CAT_HAPPY_HEAD     "res/sprites/sprites-1/Cat%dHappyHead"
// Mouse
#define FCAM_SPRITESET_MOUSE_FALLING      "res/sprites/sprites-2/MouseFalling%d"
#define FCAM_SPRITESET_MOUSE_SAD_HEAD     "res/sprites/sprites-2/Mouse%dSadHead"
#define FCAM_SPRITESET_MOUSE_HAPPY_HEAD   "res/sprites/sprites-2/Mouse%dHappyHead"
// Dog
#define FCAM_SPRITESET_DOG_BODY           "res/sprites/sprites-2/DogBody"
#define FCAM_SPRITESET_DOG_SAD_HEAD       "res/sprites/sprites-2/DogSadHead"
#define FCAM_SPRITESET_DOG_HAPPY_HEAD     "res/sprites/sprites-2/DogMadHead"
// Signs
#define FCAM_SPRITESET_CAT_SIGN           "res/sprites/sprites-3/CatSign"
#define FCAM_SPRITESET_MOUSE_SIGN         "res/sprites/sprites-3/MouseSign"
#define FCAM_SPRITESET_PLAY_SIGN          "res/sprites/sprites-3/PlaySign"
#define FCAM_SPRITESET_BOARDS_SIGN        "res/sprites/sprites-3/LeaderboardsSign"
#define FCAM_SPRITESET_LEFT_HAND          "res/sprites/sprites-3/LeftHand"
#define FCAM_SPRITESET_RIGHT_HAND         "res/sprites/sprites-3/RightHand"

// Objects inanimados
#define FCAM_SPRITE_FRIDGE         "res/sprites/sprites-5/Fridge"
#define FCAM_SPRITE_CHEESE         "res/sprites/sprites-5/Cheese"
#define FCAM_SPRITE_ELEPHANT       "res/sprites/sprites-5/Elephant"
#define FCAM_SPRITE_FISH           "res/sprites/sprites-5/Fish"

// Global hud
#define FCAM_SPRITE_SOUNDBTN         "res/sprites/sprites-2/SoundButton"
#define FCAM_SPRITE_LOGINBTN         "res/sprites/sprites-2/LoginButton"

#define FCAM_SPRITE_MOUSE_SHIRT     "res/sprites/sprites-1/MouseShirt"
#define FCAM_SPRITE_CAT_SHIRT       "res/sprites/sprites-1/CatShirt"


#define FCAM_SPRITE_MOUSE_STAR            "res/sprites/sprites-5/Star1"
#define FCAM_SPRITE_CAT_STAR              "res/sprites/sprites-5/Star2"

// Tutorial sprites
#define FCAM_SPRITE_TUT_LEFT_HAND       "res/sprites/sprites-1/LeftHand"
#define FCAM_SPRITE_TUT_RIGHT_HAND      "res/sprites/sprites-1/RightHand"
#define FCAM_SPRITE_TUT_MOUSE           "res/sprites/sprites-2/TutorialMouse"
#define FCAM_SPRITE_TUT_CAT             "res/sprites/sprites-2/TutorialCat"

// Sounds
#define FCAMP_SND_1POINTS             "res/sounds/points1.ogg"
#define FCAMP_SND_2POINTS             "res/sounds/points2.ogg"
#define FCAMP_SND_3POINTS             "res/sounds/points3.ogg"
#define FCAMP_SND_TITLE_ENTRANCE      "res/sounds/title_entrance.ogg"
#define FCAMP_SND_WRONG_ANIMAL        "res/sounds/wrong_animal.ogg"
#define FCAMP_SND_CAT_DEATH           "res/sounds/cat_death.ogg"
#define FCAMP_SND_MOUSE_DEATH         "res/sounds/mouse_death.ogg"
#define FCAMP_SND_TITLE_EXIT          "res/sounds/title_exit.ogg"
#define FCAMP_SND_BOARD_SHOW          "res/sounds/board_show.ogg"
#define FCAMP_SND_BOARD_HIDE          "res/sounds/board_hide.ogg"
#define FCAMP_SND_ACTOR_MOVE          "res/sounds/actor_move.ogg"

// Musics
#define FCAMP_MUSIC_MENU              "res/sounds/main_menu_music.ogg"

// Sound library indexes
#define FCAMP_SOUND_1POINTS_IDX         0
#define FCAMP_SOUND_2POINTS_IDX         1
#define FCAMP_SOUND_3POINTS_IDX         2
#define FCAMP_SND_TITLE_ENTRANCE_IDX    3
#define FCAMP_SND_WRONG_ANIMAL_IDX      4
#define FCAMP_SND_CAT_DEATH_IDX         5
#define FCAMP_SND_MOUSE_DEATH_IDX       6
#define FCAMP_SND_TITLE_EXIT_IDX        7
#define FCAMP_SND_BOARD_SHOW_IDX        8
#define FCAMP_SND_BOARD_HIDE_IDX        9
#define FCAMP_SND_ACTOR_MOVE_IDX        10

// Scripts
#define FCAM_SCRIPT_SHOW_LEFT_SIGN        "res/scripts/left-sign-show"
#define FCAM_SCRIPT_SHOW_RIGHT_SIGN       "res/scripts/right-sign-show"
#define FCAM_SCRIPT_CHANGE_LEFT_SIGN      "res/scripts/left-sign-switch"
#define FCAM_SCRIPT_CHANGE_RIGHT_SIGN     "res/scripts/right-sign-switch"
#define FCAM_SCRIPT_HIDE_LEFT_SIGN        "res/scripts/left-sign-hide"
#define FCAM_SCRIPT_HIDE_RIGHT_SIGN       "res/scripts/right-sign-hide"
#define FCAM_SCRIPT_IDLE_SIGN             "res/scripts/sign-idle"
#define FCAM_SCRIPT_TUTORIAL              "res/scripts/tutorial"

// Font assets
#define FCAM_ASSET_FONT_DEFAULT           "res/fonts/main-font"
#define FCAM_ASSET_FONT_BIG               "res/fonts/main-font-big"


// Textos
#define FCAM_TEXT_RATE      "Rate"
#define FCAM_TEXT_GAMEOVER  "Gameover"
#define FCAM_TEXT_LEVEL     "Level"
#define FCAM_TEXT_SCORE     "Final Score"
#define FCAM_TEXT_RETRY     "Retry"
#define FCAM_TEXT_NEW_HIGHSCORE "New highScore!"
#define FCAM_TEXT_HIGHSCORE "HighScore"
#define FCAM_TEXT_TAP_TO_START "Tap to start"

// Navegacoes de scenes
#define FCAM_NAVIGATION_GAMEPLAY "gameplay"
#define FCAM_NAVIGATION_MAINMENU "mainMenu"
#define FCAM_NAVIGATION_GAMEOVER "gameover"

#define FCAM_INITIAL_LEVEL  1
#define FCAM_MAX_ACTOR_SIZE 3

#define FCAM_INITIAL_FALL_SPEED         1.0f
#define FCAM_MAX_FALL_SPEED             5.0f
#define FCAM_MIN_RELEASE_TIME           500
#define FCAM_MAX_LEVEL                  20
#define FCAM_INITIAL_ACTOR_RELEASE_TIME 1000
#define FCAM_STEP_CLOSE_DOOR_PERC       5.0f

#define FCAM_LEADERBOARDS_NAME "leaderboards"
#define FCAM_LEADERBOARDS_ID_GAME_CENTER "TopFatCatsAndMice"
#define FCAM_LEADERBOARDS_ID_GOOGLE_PLAY "CgkIl_m4tKAEEAIQAQ"

#define FCAM_ADBANNER_NAME "adBanner"
#define FCAM_ADBANNER_ID "ca-app-pub-4808839020566742/5296631918"

#define FCAM_JUMP_DIRECTION_LEFT  -1
#define FCAM_JUMP_DIRECTION_RIGHT  1
#define FCAM_JUMP_DIRECTION_RANDOM 0
  

// Collision bits
#define FCAMP_COLLISIONBIT_CAT        0x01
#define FCAMP_COLLISIONBIT_MOUSE      0x02
#define FCAMP_COLLISIONBIT_DOG        0x04
#define FCAMP_COLLISIONBIT_OBJECT     0x08

#define FCAMP_COLLISIONBIT_ANIMALS    FCAMP_COLLISIONBIT_CAT | FCAMP_COLLISIONBIT_MOUSE | FCAMP_COLLISIONBIT_DOG

// Library item indexes
#define FCAM_LIB_ITEM_CAT_IDX      0 // 0- CAT1, 1-CAT2, 2-CAT3
#define FCAM_LIB_ITEM_MOUSE_IDX    FCAM_LIB_ITEM_CAT_IDX + FCAM_TOTAL_CATS // 3- MOUSE1, 4-MOUSE2, 5-MOUSE3
#define FCAM_LIB_ITEM_DOG_IDX      FCAM_LIB_ITEM_MOUSE_IDX + FCAM_TOTAL_MICE + 1
#define FCAM_LIB_ITEM_OBJECT_IDX   FCAM_LIB_ITEM_DOG_IDX + 1

#define FCAM_SHADOW_COLOR PK_Color(0.0f, 0.0f, 0.0f, 0.5f)

// Mensagens
#define FCAM_MSG_GAMEOVER 1

#define FCAM_LOG_TAG  (char *)"FC"

#define FCAM_SNAILS_APP_ID "863322227"
#define FCAM_SNAILS_FREE_APP_ID "863369542"
#define FCAM_LIMANIMA_URL "http://www.limanima.com"
#endif
