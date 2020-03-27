#include "game.h"

void powerups_fire_init(){
    powerups_fire_bullets_on_screen = 0;
    Entity* b = powerups_fire_bullets;
    for(int i = 0; i < POWERUPS_FIRE_BULLETS_NUMBER;i++){
        b->x = 0;
        b->y = -10;
        b->w = 8;
        b->h = 8;
        //set sprite
        b->sprite = SPR_addSprite(&bullet,powerups_fire_bullets[0].x,powerups_fire_bullets[0].y,TILE_ATTR(PAL2,0,FALSE,FALSE));
        //set name
        sprintf(b->name, "PFBu%d",i);
        //next bullet
        b++;
    }
}

void powerups_fire_start(){
    powerups_fire_bullets_fired = 0;
    powerups_fire_timer = getTime(1);
}

bool powerups_fire_update(){
    KDebug_AlertNumber(powerups_fire_bullets_fired);
    if(powerups_fire_bullets_fired < POWERUPS_FIRE_BULLETS_NUMBER && (getTime(1) - powerups_fire_timer) >= 30){
        Entity* b;
        u16 i = 0;
        for(i=0; i<POWERUPS_FIRE_BULLETS_NUMBER; i++){
            b = &powerups_fire_bullets[i];
            if(b->health == 0){

                b->x = player.x+4;
                b->y = player.y;

                revive_entity(b);
                switch(powerups_fire_bullets_fired%3){
                    case 0:
                        b->velx = 0;
                    break;
                    case 1:
                        b->velx = -1;
                    break;
                    case 2:
                        b->velx = 1;
                    break;
                }
                b->vely = -3;

                SPR_setPosition(b->sprite,b->x,b->y);
                break;
            }
        }
        powerups_fire_bullets_on_screen++;
        powerups_fire_bullets_fired++;
        powerups_fire_timer = getTime(1);
    }
    if(powerups_fire_bullets_on_screen>0){
        u16 i = 0;
        Entity *b;
        for(i = 0; i < POWERUPS_FIRE_BULLETS_NUMBER; i++){
            b = &powerups_fire_bullets[i];
            if(b->health > 0){
                b->y += b->vely;
                b->x += b->velx;
                if(b->y + b->h < 0){
                    kill_entity(b);
                    powerups_fire_bullets_on_screen--;
                } else{
                    SPR_setPosition(b->sprite,b->x,b->y);
                }  
                u16 ei = 0;
                Entity *e;
                for(ei = 0; ei < MAX_ENEMIES;ei++){
                    KDebug_Alert("test");
                    e = &enemies[ei];
                    if(e->health >0 && doesCollide(b, e)){
                        kill_entity(e);
                        kill_entity(b);
                    }
                }
            }
        }
    }
    return (powerups_fire_bullets_fired < POWERUPS_FIRE_BULLETS_NUMBER)||powerups_fire_bullets_on_screen>0;
}