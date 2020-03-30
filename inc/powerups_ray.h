#ifndef __POWERUPS_RAY_H__
#define __POWERUPS_RAY_H__
#include "game.h"

#define POWERUP_RAY_LENGTH 12
#define POWERUP_RAY_TIME 1500

Entity powerups_ray_parts[POWERUP_RAY_LENGTH];
int powerups_ray_timer;

void powerups_ray_init();
void powerups_ray_start();
bool powerups_ray_update();

#endif