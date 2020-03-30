#ifndef __POWERUPS_H__
#define __POWERUPS_H__

#include "game.h"


//number of diffrent powerups
#define POWERUPS_NUMBER 2

//powerups
#define POWERUP_FIRE 0
#define POWERUP_RAY 1

//powerup entities
Entity powerups[POWERUPS_NUMBER];

bool powerups_spawned;
int powerups_current;
Entity* powerups_current_spawned_entity;
bool powerups_active;

void powerups_init();
void powerups_start();
void powerups_update();
//spawn a powerup
void powerups_spawn(int powerup, int x, int y);
void powerups_spawn_random(int x, int y);
#endif