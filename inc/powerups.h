#include "game.h"


//number of diffrent powerups
#define POWERUPS_NUMBER 2

//powerups
#define POWERUP_FIRE 0
#define POWERUP_RAY 1

//powerup entities
Entity powerups[POWERUPS_NUMBER];

void powerups_init();

void powerups_update();

//spawn a powerup
void spawnPowerup(int powerup, int x, int y);