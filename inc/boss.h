#ifndef __BOSS_H__
#define __BOSS_H__
#include "game.h"
#define BOSS_MINIONS_NUMBER 10

#define BOSS_PHASE_MINIONS 0
#define BOSS_PHASE_TENNIS 1

Entity boss_entity;

Entity boss_minions[BOSS_MINIONS_NUMBER];

int boss_current_phase;
bool boss_is_moving;
int timer;
fix16 boss_x, boss_y, boss_velx, boss_vely;
int boss_moving_target_x, boss_moving_target_y;

int boss_minions_spawned;

bool boss_projectile_spawned;
Entity boss_projectile_entity;
fix16 boss_projectile_velx, boss_projectile_vely, boss_projectile_x, boss_projectile_y;
bool boss_projectile_is_reflected;

void boss_init();
void boss_update();
void boss_kill();
void boss_hit();
void boss_next_phase();
void boss_start_phase();
void boss_move_to(int x, int y);

//phase 1
void boss_spawn_minions();
void boss_update_minions();

//phase 2
void boss_shoot_projectile();
void boss_update_projectile();
void boss_projectile_hit_by_player();

void boss_update_movement();

void boss_start_phase_minions();
void boss_start_phase_tennis();

void boss_update_phase_minions();
void boss_update_phase_tennis();

#endif