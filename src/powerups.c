#include "game.h"

void powerups_init(){
    powerups_spawned = 0;
    powerups_active = 0;
    powerups_fire_init();
    powerups_ray_init();
    /*create powerups entities*/
    int i = 0;
    Entity* p = powerups;
    for(i = 0; i < POWERUPS_NUMBER; i++){
        switch(i){
            case POWERUP_FIRE:
                p->sprite = SPR_addSprite(&powerup_fire, 0, -20, TILE_ATTR(PAL3,0,FALSE,FALSE));
                sprintf(p->name, "pufire");
            break;
            case POWERUP_RAY:
                p->sprite = SPR_addSprite(&powerup_ray, 0, -20, TILE_ATTR(PAL3, 0, FALSE, FALSE));
                sprintf(p->name, "puray");
            break;
        }
        p->w = 16;
        p->h = 16;
        p++;
    }
    SYS_disableInts();
    VDP_setPalette(PAL3, powerup_pal.data);
    SYS_enableInts();
}

void powerups_update(){
    if(powerups_active){
        switch(powerups_current){
            case POWERUP_FIRE:
                powerups_active = powerups_fire_update();
            break;
            case POWERUP_RAY:
                powerups_active = powerups_ray_update();
            break;
        }
    }
    else if(powerups_spawned){
        int i = 0;
        Entity *p = powerups_current_spawned_entity;
        p->y++;
        if(p->y > BOTTOM_EDGE){
            kill_entity(p);
            powerups_spawned = 0;
        }
        else{
            SPR_setPosition(p->sprite,p->x,p->y);
            SPR_update();
        }
    }
}

//spawn a powerup
void powerups_spawn(int powerup, int x, int y){
    powerups_spawned = 1;
    powerups_current = powerup;
    Entity* p = &powerups[powerup];
    powerups_current_spawned_entity = p;
    p->x = x;
    p->y = y;
    revive_entity(p);
}

void powerups_start(){
    powerups_spawned = 0;
    powerups_active = 1;
    switch(powerups_current){
        case POWERUP_FIRE:
            powerups_fire_start();
        break;
        case POWERUP_RAY:
            powerups_ray_start();
        break;
    }
}