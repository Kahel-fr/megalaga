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
        e->health = 1;
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
    VDP_setPaletteColor(34,RGB24_TO_VDPCOLOR(0x0078f8));
}

void enemies_update(){
    u16 i = 0;
    //for each ennemy
    for(i = 0; i < MAX_ENEMIES; i++){
        Entity* e = &enemies[i];
        //if the ennemy is still alive
        if(e->health > 0){
            //if the future position exceeds screen, change direction
            if( (e->x+e->w) > RIGHT_EDGE){
                e->velx = -1;
                e->y += e->h;
            }
            else if(e->x < LEFT_EDGE){
                e->velx = 1;
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