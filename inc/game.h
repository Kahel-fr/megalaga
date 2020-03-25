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

//edges of the screen
#define LEFT_EDGE 0
#define RIGHT_EDGE 320
#define BOTTOM_EDGE 240

void showText(char s[]);

bool finished;

#endif