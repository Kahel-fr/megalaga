#include "game.h"

void bullets_init(){
        u16 i = 0;
        /*create bullets entities*/
    //point to first ennemy
    Entity* b = bullets;
    //for each bullet
    for(i = 0; i < MAX_BULLETS; i++){
        //set position and size
        b->x = 0;
        b->y = -10;
        b->w = 8;
        b->h = 8;
        //set sprite
        b->sprite = SPR_addSprite(&bullet,bullets[0].x,bullets[0].y,TILE_ATTR(PAL1,0,FALSE,FALSE));
        //set name
        sprintf(b->name, "Bu%d",i);
        //next bullet
        b++;
    }
    bulletsOnScreen = 0;
}

void bullets_update(){
    u16 i = 0;
    Entity *b;
    for(i = 0; i < MAX_BULLETS; i++){
        b = &bullets[i];
        if(b->health > 0){
          b->y += b->vely;
            if(b->y + b->h < 0){
                destroyBullet(b);
            } else{
                SPR_setPosition(b->sprite,b->x,b->y);
            }  
        }
    }
}

//destroy a bullet
void destroyBullet(Entity* bullet){
    kill_entity(bullet);
    bulletsOnScreen--;
}