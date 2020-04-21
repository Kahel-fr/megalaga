#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "game.h"

//indexes for ship when not moving and when moving
#define ANIM_STRAIGHT 0
#define ANIM_MOVE 1

#define PLAYER_SHOOTING_OFFSET_Y 4

//player entity
Entity player;

void player_init();
void player_reset();

void player_update();

//shoot a bullet
void shootBullet();

#endif