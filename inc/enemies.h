#include "game.h"

#define MAX_ENEMIES 6

//ennemies entities
Entity enemies[MAX_ENEMIES];

//count of ennemies still alive
u16 enemiesLeft;

void enemies_init();

void enemies_update();