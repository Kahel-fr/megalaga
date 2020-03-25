#include "game.h"

void powerups_init(){
    /*create powerups entities*/
    int i = 0;
    Entity* p = powerups;
    for(i = 0; i < POWERUPS_NUMBER; i++){
        switch(i){
            case POWERUP_FIRE:
                p->sprite = SPR_addSprite(&powerup_fire, 0, 0, TILE_ATTR(PAL3,0,FALSE,FALSE));
                sprintf(p->name, "pufire");
            break;
            case POWERUP_RAY:
                p->sprite = SPR_addSprite(&powerup_ray, 0, 0, TILE_ATTR(PAL3, 0, FALSE, FALSE));
                sprintf(p->name, "puray");
            break;
        }
        p->w = 16;
        p->h = 16;
        kill_entity(p);
        p++;
    }

    VDP_setPalette(PAL3, powerup_pal.data);
}

void powerups_update(){
    int i = 0;
    Entity *p;
    for(i = 0; i < POWERUPS_NUMBER; i++){
        p = &powerups[i];
        if(p->health>0){
            p->y++;
            if(p->y > BOTTOM_EDGE)
                kill_entity(p);
            else{
                SPR_setPosition(p->sprite,p->x,p->y);
                SPR_update();
            }
        }
    }
}

//spawn a powerup
void spawnPowerup(int powerup, int x, int y){
    Entity* p = &powerups[1];
    KDebug_Alert(p->name);
    revive_entity(p);
    p->x = x;
    p->y = y;
}