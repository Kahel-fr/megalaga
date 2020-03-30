#include "game.h"

void player_init(){
    player.w = 16;
    player.h = 16;
    player.velx = 0;
    player.vely = 0;
    player.x = 152;
    player.y = 192;
    player.health = 1;
    player.sprite = SPR_addSprite(&ship,player.x,player.y,TILE_ATTR(PAL1,0,FALSE,FALSE));
    sprintf(player.name, "PLAYER");
}

void player_update(){
    //add velocity to position
    player.x += player.velx;

    //if the position exceeds screen, set position to edge position
    if(player.x < LEFT_EDGE) player.x = LEFT_EDGE;
    if(player.x + player.w > RIGHT_EDGE) player.x = RIGHT_EDGE - player.w;

    //set sprite position
    SPR_setPosition(player.sprite,player.x,player.y);
}

//shoot a bullet
void shootBullet(){
    if( bulletsOnScreen < MAX_BULLETS ){
        Entity* b;
        u16 i = 0;
        for(i=0; i<MAX_BULLETS; i++){
            b = &bullets[i];
            if(b->health == 0){
                b->x = player.x+PLAYER_SHOOTING_OFFSET_Y;
                b->y = player.y;

                revive_entity(b);
                b->vely = -3;

                SPR_setPosition(b->sprite,b->x,b->y);
                bulletsOnScreen++;
                break;
            }
        }	
    }
}