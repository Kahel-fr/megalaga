#ifndef __GAME_H__
#define __GAME_H__
#include <genesis.h>
#include <kdebug.h>
#include <resources.h>
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

bool paused;
int wavesCount;

void loadWave();

#endif