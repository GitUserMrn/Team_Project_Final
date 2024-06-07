#pragma once

#ifndef PP_SPACE_INVASION_GLOBAL_H
#define PP_SPACE_INVASION_GLOBAL_H



#include <cmath>
#include <chrono>


constexpr unsigned char BASE_SIZE = 16;

// for drawing the window
constexpr unsigned char SCREEN_RESIZE = 4;
constexpr unsigned short SCREEN_HEIGHT = 180;
constexpr unsigned short SCREEN_WIDTH = 320;
constexpr unsigned char NEXT_WAVE_TRANSITION = 64;
constexpr unsigned char TOTAL_WAVES = 8;

// player stuff
constexpr unsigned char PLAYER_MOVE_SPEED = 2;
constexpr unsigned char PLAYER_BULLET_SPEED = 4;
constexpr unsigned char RELOAD_DURATION = 30;
constexpr unsigned char FAST_RELOAD_DURATION = 6;

// enemy stuff
constexpr unsigned char ENEMY_TYPES = 3;
constexpr unsigned char ENEMY_HIT_TIMER_DURATION = 2;
constexpr unsigned char ENEMY_MOVE_PAUSE_MIN = 3;
constexpr unsigned short ENEMY_SHOOT_CHANCE_INCREASE = 64;
constexpr unsigned short ENEMY_SHOOT_CHANCE_MIN = 1024;
constexpr unsigned char ENEMY_MOVE_SPEED = 3;

constexpr unsigned char ENEMY_MOVE_PAUSE_START = 63;
constexpr unsigned char ENEMY_MOVE_PAUSE_START_MIN = 47;
// the more enemies we kill, the faster they become.
constexpr unsigned char ENEMY_MOVE_PAUSE_DECREASE = 1;
constexpr unsigned char ENEMY_BULLET_SPEED = 2;
constexpr unsigned short ENEMY_SHOOT_CHANCE = 4500;

// bonus enemy stuff
constexpr unsigned char BONUS_ANIMATION_SPEED = 8;
constexpr unsigned char BONUS_MOVE_SPEED = 1;
constexpr unsigned short BONUS_TIMER_MAX = 1300;
constexpr unsigned short BONUS_TIMER_MIN = 768;

constexpr unsigned char EXPLOSION_ANIMATION_SPEED = 2;

constexpr unsigned short POWERUP_DURATION = 512;
constexpr unsigned char POWERUP_ANIMATION_SPEED = 16;
constexpr unsigned char POWERUP_SPEED = 2;
constexpr unsigned char POWERUP_TYPES = 4;

constexpr unsigned short MULTYPLAYER_SWITCH_TIMER = 100;

// a constant for the frame duration in ms
constexpr std::chrono::microseconds FRAME_DURATION(16667);

#endif