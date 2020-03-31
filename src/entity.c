#include "game.h"

//kill an entity
void kill_entity(Entity* e){
	e->health = 0;
	SPR_setVisibility(e->sprite,HIDDEN);
}

//revive an entity
void revive_entity(Entity* e){
	KLog("test");
	e->health = e->maxhealth;
	SPR_setVisibility(e->sprite,VISIBLE);
}
