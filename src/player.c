#include "game.h"

void player_init(){
    player.w = 16;
    player.h = 16;
    player.health = 3;
    player.sprite = SPR_addSprite(&ship,player.x,player.y,TILE_ATTR(PAL1,0,FALSE,FALSE));
    KLog(player.x);
    sprintf(player.name, "PLAYER");
}

void player_reset(){
    player.health = 3;
    player.velx = 0;
    player.vely = 0;
    player.x = 152;
    player.y = 192;
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
    if(!powerups_active && bulletsOnScreen < 3)
        bullets_spawn(player.x, player.y, 0);
}