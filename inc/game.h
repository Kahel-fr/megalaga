#ifndef __GAME_H__
#define __GAME_H__
#include <genesis.h>
#include <kdebug.h>
#include <resources.h>
#include "container.h"
#include "hud.h"
#include "entity.h"
#include "enemies.h"
#include "player.h"
#include "bullets.h"
#include "powerups.h"
#include "powerups_fire.h"
#include "powerups_ray.h"
#include "boss.h"

//edges of the screen
#define LEFT_EDGE 0
#define RIGHT_EDGE 320
#define BOTTOM_EDGE 240

void showText(char s[]);
void get_direction_between_two_points(int start_x, int start_y, int end_x, int end_y, fix16* velx, fix16* vely);

bool paused;
int wavesCount;
bool isBossWave;

void loadWave();
void game_reset();
void game_over();

#endif