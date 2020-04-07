#ifndef __BOSS_H__
#define __BOSS_H__
#include "game.h"

#define BOSS_PHASES_NUMBER 4
#define BOSS_HEALTH_BY_PHASE 10

Entity boss_entity;

Vect2D_u16 boss_phases_positions[BOSS_PHASES_NUMBER];

int boss_current_phase;
bool boss_is_moving;

void boss_init();
void boss_update();
void boss_kill();

void boss_update_movement();
#endif