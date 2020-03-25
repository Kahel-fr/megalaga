#ifndef __ENTITY_H__
#define __ENTITY_H__
#include "game.h"
//entity structure (like player, ennemies, ect...)
typedef struct {
	int x;
	int y;
	int w;
	int h;
	int velx;
	int vely;
	int health;
	char name[6];
    Sprite* sprite;
} Entity;

void kill_entity(Entity* e);
void revive_entity(Entity* e);

#endif