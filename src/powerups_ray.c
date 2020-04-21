#include "game.h"

void powerups_ray_init(){
    container_powerup_rayparts = add_container_to_game();
}

void powerups_ray_start(){
    powerups_ray_timer = getTime(1);
    for(int i = 0; i < POWERUP_RAY_LENGTH;i++){
        Entity *raypart = &powerups_ray_parts[i];
        raypart->type = ENTITY_RAY;
        raypart->x = 0;
        raypart->y = 0;
        raypart->h = 16;
        raypart->w = 16;
        raypart->maxhealth = 1;
        raypart->health = 1;
        raypart->sprite = SPR_addSprite(&ray, raypart->x, raypart->y, TILE_ATTR(PAL3,0,FALSE,FALSE));
        t_element * obj = create_element(raypart);
        add_element_to_container(container_bullets, obj);
    }
}

bool powerups_ray_update(){
    int currentTime = getTime(1);
    bool isStillActive = currentTime-powerups_ray_timer < POWERUP_RAY_TIME;
    for(int i = 0; i < POWERUP_RAY_LENGTH;i++){
        Entity* raypart = &powerups_ray_parts[i];
        if(isStillActive){
            raypart->x = player.x;
            raypart->y = (player.y-player.h-PLAYER_SHOOTING_OFFSET_Y)-(raypart->h*i);
            SPR_setPosition(raypart->sprite, raypart->x, raypart->y);
        }
        else
            kill_entity(raypart);
    }
    return isStillActive;
}

void powerups_ray_hit(Entity* ennemy){
    if(powerups_ray_cooldown-getTime(0) > 1000){
        enemies_take_damage(ennemy, 1);
        powerups_ray_cooldown = getTime(0);
    }
}