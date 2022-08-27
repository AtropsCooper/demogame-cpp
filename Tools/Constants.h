#pragma once
#include "SDL.h"

const float ANIM_FRAMERATE = 0.15f;
const int MAPSIZE = 128;

const float HEALTH_PLAYER = 20.0f;
const float HEALTH_SKELET = 10.0f;
const float HEALTH_GOBLIN = 15.0f;

const float ENEMY_SPAWN_RANGE = 10.0f;
const float ENEMY_SPAWN_CHANCE = 0.05f;
const float ENEMY_SPAWN_INTERVAL = 2.0f;

const SDL_Rect SRRITE_BOW = {325, 180, 7, 25};
const SDL_Rect SPRITE_ARROW = {308, 186, 7, 21};

const SDL_Rect PLAYER_IDLE_ANIM = {128, 196, 16, 28};
const int PLAYER_IDLE_LENGTH = 4;
const SDL_Rect PLAYER_RUN_ANIM = {192, 196, 16, 28};
const int PLAYER_RUN_LENGTH = 4;
const SDL_Rect PLAYER_HIT_ANIM = {256, 196, 16, 28};  
const int PLAYER_HIT_LENGTH = 1;
const SDL_Rect SKELET_IDLE_ANIM = {368, 80, 16, 16};
const int SKELET_IDLE_LENGTH = 4;
const SDL_Rect SKELET_RUN_ANIM = {432, 80, 16, 16};
const int SKELET_RUN_LENGTH = 4;