#ifndef __BOSS_H__
#define __BOSS_H__
#include "game.h"

#define BOSS_PHASES_NUMBER 4
#define BOSS_HEALTH_BY_PHASE 10
#define BOSS_MINIONS_NUMBER 10

Entity boss_entity;

Vect2D_u16 boss_phases_positions[BOSS_PHASES_NUMBER];
Entity boss_minions[BOSS_MINIONS_NUMBER];

int boss_current_phase;
bool boss_is_moving;
int timer;

int boss_minions_spawned;

void boss_init();
void boss_update();
void boss_kill();

//phase 1
void boss_spawn_minions();
void boss_update_minions();

void boss_update_movement();
#endif