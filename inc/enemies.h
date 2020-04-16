#ifndef __ENEMIES_H__
#define __ENEMIES_H__

#include "game.h"

#define MAX_ENEMIES 12

//ennemies entities
t_container* container_enemies;

//count of ennemies still alive
u16 enemiesLeft;

int timer;

void enemies_init();
void enemies_update();
void ennemies_reset();
void enemies_take_damage(Entity* e, int damage);
void enemies_kill(Entity* e);
void enemies_random_shoot(Entity* e);

#endif