#ifndef __POWERUPS_RAY_H__
#define __POWERUPS_RAY_H__
#include "game.h"

#define POWERUP_RAY_LENGTH 12
#define POWERUP_RAY_TIME 1500

Entity powerups_ray_parts[POWERUP_RAY_LENGTH];
t_container* container_powerup_rayparts;
int powerups_ray_timer;

void powerups_ray_init();
void powerups_ray_start();
bool powerups_ray_update();
void powerups_ray_hit(Entity* ennemy);

#endif