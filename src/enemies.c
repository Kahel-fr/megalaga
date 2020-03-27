#include "game.h"

void enemies_init(){

    //count of ennemies still alive
    enemiesLeft = 0;
    /*Create all enemy*/
        u16 i = 0;
    //point to first ennemy
    Entity* e = enemies;
    //for each enemy
    for(i = 0; i < MAX_ENEMIES; i++){
        //set position, size, health
        e->x = i*32;
        e->y = 16;
        e->w = 16;
        e->h = 16;
        e->velx = 1;
        e->health = 5;
        //set sprite (using ship sprite but flipped toward player and with a different color pal)
        e->sprite = SPR_addSprite(&ship,e->x,e->y,TILE_ATTR(PAL2,0,TRUE,FALSE));
        //set ennemy name
        sprintf(e->name, "En%d",i);
        //increment ennemy count
        enemiesLeft++;
        //next enemy
        e++;
    }
    //set color pal used for enemies
    SYS_disableInts();
    VDP_setPaletteColor(34,RGB24_TO_VDPCOLOR(0x0078f8));
    SYS_enableInts();
}

void enemies_update(){
    u16 i = 0;
    //for each ennemy
    for(i = 0; i < MAX_ENEMIES; i++){
        Entity* e = &enemies[i];
        //if the ennemy is still alive
        if(e->health > 0){
            if(e->x+e->w > RIGHT_EDGE || e->x < LEFT_EDGE){
                e->velx = -e->velx;
                e->y += e->h;
            }
            //add velocity to current position
            e->x += e->velx;
            e->y += e->vely;
            //set sprite position
            SPR_setPosition(e->sprite,e->x,e->y);
        }
    }
}

void ennemies_reset(){
    enemiesLeft = 0;
    u16 i = 0;
    Entity* e = enemies;
    for(i = 0; i < MAX_ENEMIES; i++){
        e->x = i*32;
        e->y = 16;
        e->velx = wavesCount;
        e->health = 5;
        enemiesLeft++;
        revive_entity(e);
        e++;
    }
}

void enemies_kill(Entity* e){
    kill_entity(e);
    enemiesLeft--;
    if(!powerups_spawned && !powerups_active)
        powerups_spawn(POWERUP_FIRE, e->x, e->y);
}

void enemies_take_damage(Entity* e, int damage){
    e->health-=damage;
    if(e->health<=0){
        enemies_kill(e);
    }
}