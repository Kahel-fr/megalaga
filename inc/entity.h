#ifndef __ENTITY_H__
#define __ENTITY_H__
#include "game.h"

#define ENTITY_PLAYER 0
#define ENTITY_ENNEMY 1
#define ENTITY_BOSS 2

#define ENTITY_POWERUP 3
#define ENTITY_BULLET 4
#define ENTITY_RAY 5

//entity structure (like player, ennemies, ect...)
typedef struct {
	int x;
	int y;
	int w;
	int h;
	int velx;
	int vely;
	int maxhealth;
	int health;
	char name[6];
	int type;
    Sprite* sprite;
	bool isInvincible;
} Entity;

void kill_entity(Entity* e);
void revive_entity(Entity* e);
void entity_take_damage(Entity* e, int damage);
void entity_delete(Entity* e);

#endif