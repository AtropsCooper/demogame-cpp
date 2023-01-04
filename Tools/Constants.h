#pragma once
#include "SDL.h"

const static char GAME_TITLE[] = "Dino Dungeon";

const static int WINDOW_WIDTH = 1024;
const static int WINDOW_HEIGHT = 768;

const static int UI_BUTTON_WIDTH = 180;
const static int UI_BUTTON_HEIGHT = 88;
const static int UI_HUD_WIDTH = 110;
const static int UI_HUD_HEIGHT = 48;
const static int UI_HUD_HEART_WIDTH = 26;
const static int UI_HUD_HEART_HEIGHT = 24;
const static int UI_HUD_HEART_X_1 = 12;
const static int UI_HUD_HEART_X_2 = 42;
const static int UI_HUD_HEART_X_3 = 72;
const static int UI_HUD_HEART_Y = 14;

const static float ANIM_FRAMERATE = 0.15f;
const static int MAPSIZE = 128;

const static float HEALTH_PLAYER = 6.0f;
const static float HEALTH_SKELET = 5.0f;
const static float HEALTH_GOBLIN = 15.0f;
const static float HEALTH_DEMON = 25.0f;
const static float HEALTH_BOSS = 250.0f;

const static float ENEMY_SPAWN_RANGE = 10.0f;
const static float ENEMY_SPAWN_RATE = 0.3f;
const static float ENEMY_SPAWN_INTERVAL = 1.0f;


// 0x72_DungeonTilesetII_v1.4.png
const static SDL_Rect SRRITE_BOW = {325, 180, 7, 25};
const static SDL_Rect SPRITE_ARROW = {308, 186, 7, 21};

const static SDL_Rect PLAYER_IDLE_ANIM = {128, 196, 16, 28};
const static int PLAYER_IDLE_LENGTH = 4;
const static SDL_Rect PLAYER_RUN_ANIM = {192, 196, 16, 28};
const static int PLAYER_RUN_LENGTH = 4;
const static SDL_Rect PLAYER_HIT_ANIM = {256, 196, 16, 28};  
const static int PLAYER_HIT_LENGTH = 2;

const static SDL_Rect SKELET_IDLE_ANIM = {368, 80, 16, 16};
const static int SKELET_IDLE_LENGTH = 4;
const static SDL_Rect SKELET_RUN_ANIM = {432, 80, 16, 16};
const static int SKELET_RUN_LENGTH = 4;
const static SDL_Rect SKELET_HIT_ANIM = {480, 80, 16, 16};
const static int SKELET_HIT_LENGTH = 2;

const static SDL_Rect GOBLIN_IDLE_ANIM = {368, 204, 16, 20};
const static int GOBLIN_IDLE_LENGTH = 4;
const static SDL_Rect GOBLIN_RUN_ANIM = {432, 204, 16, 20};
const static int GOBLIN_RUN_LENGTH = 4;
const static SDL_Rect GOBLIN_HIT_ANIM = {480, 204, 16, 20};
const static int GOBLIN_HIT_LENGTH = 2;

const static SDL_Rect DEMON_IDLE_ANIM = {368, 328, 16, 24};
const static int DEMON_IDLE_LENGTH = 4;
const static SDL_Rect DEMON_RUN_ANIM = {432, 328, 16, 24};
const static int DEMON_RUN_LENGTH = 4;
const static SDL_Rect DEMON_HIT_ANIM = {480, 328, 16, 24};
const static int DEMON_HIT_LENGTH = 2;

const static SDL_Rect BOSS_IDLE_ANIM = {16, 364, 32, 36};
const static int BOSS_IDLE_LENGTH = 4;
const static SDL_Rect BOSS_RUN_ANIM = {144, 364, 32, 36};
const static int BOSS_RUN_LENGTH = 4;
const static SDL_Rect BOSS_HIT_ANIM = {240, 364, 32, 36};
const static int BOSS_HIT_LENGTH = 2;


// UI.png
const static SDL_Rect UI_MENU_BG = {56, 0, 78, 85};
const static SDL_Rect UI_BUTTON_OFF = {0, 36, 45, 22};
const static SDL_Rect UI_BUTTON_ON = {0, 59, 45, 22};
const static SDL_Rect UI_HUD_BG = {0, 0, 55, 24};
const static SDL_Rect UI_HUD_HEART = {0, 24, 13, 12};
const static SDL_Rect UI_HUD_HALF_HEART = {15, 24, 13, 12};
const static SDL_Rect UI_HUD_EMPTY_HEART = {30, 24, 13, 12};