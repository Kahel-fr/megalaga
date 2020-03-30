#include "game.h"

void powerups_ray_init(){
    Entity* raypart;
    for(int i = 0; i < POWERUP_RAY_LENGTH;i++){
        raypart = &powerups_ray_parts[i];
        raypart->x = 0;
        raypart->y = -20;
        raypart->h = 16;
        raypart->w = 16;
        raypart->maxhealth = 1;
        raypart->sprite = SPR_addSprite(&ray, raypart->x, raypart->y, TILE_ATTR(PAL3,0,FALSE,FALSE));
    }
}

void powerups_ray_start(){
    powerups_ray_timer = getTime(1);
    Entity* raypart;
    for(int i = 0; i < POWERUP_RAY_LENGTH;i++){
        revive_entity(raypart);
    }
}

bool powerups_ray_update(){
    int currentTime = getTime(1);
    Entity* raypart;
    for(int i = 0; i < POWERUP_RAY_LENGTH;i++){
        raypart = &powerups_ray_parts[i];
        if(currentTime-powerups_ray_timer < POWERUP_RAY_TIME){
            raypart->x = player.x;
            raypart->y = (player.y-player.h-PLAYER_SHOOTING_OFFSET_Y)-(raypart->h*i);
            SPR_setPosition(raypart->sprite, raypart->x, raypart->y);
            u16 ei = 0;
            Entity *e;
            for(ei = 0; ei < MAX_ENEMIES;ei++){
                e = &enemies[ei];
                if(e->health>0){
                    if(doesCollide(raypart, e) && (currentTime % 15) <= 1)
                        enemies_take_damage(e, 1);
                }
            }
        }
        else{
            kill_entity(raypart);
        }
    }
    return currentTime-powerups_ray_timer < POWERUP_RAY_TIME;
}