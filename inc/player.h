#include "game.h"

//indexes for ship when not moving and when moving
#define ANIM_STRAIGHT 0
#define ANIM_MOVE 1

//player entity
Entity player;

void player_init();

void player_update();

//shoot a bullet
void shootBullet();