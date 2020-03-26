#ifndef __BULLETS_H__
#define __BULLETS_H__
#include "game.h"

#define MAX_BULLETS	3

Entity bullets[MAX_BULLETS];

//count of bullets on screen
u16 bulletsOnScreen;

void bullets_init();
void bullets_update();

//destroy a bullet
void destroyBullet(Entity* bullet);

#endif