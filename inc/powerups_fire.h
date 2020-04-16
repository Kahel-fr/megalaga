#ifndef __POWERUPS_FIRE_H__
#define __POWERUPS_FIRE_H__
#include "game.h"

#define POWERUPS_FIRE_BULLETS_NUMBER 30

Entity powerups_fire_bullets[POWERUPS_FIRE_BULLETS_NUMBER];
int powerups_fire_bullets_fired;
int powerups_fire_bullets_on_screen;
int powerups_fire_timer;

void powerups_fire_init();
void powerups_fire_start();
bool powerups_fire_update();
void powerups_fire_shootone(Entity* b);

#endif