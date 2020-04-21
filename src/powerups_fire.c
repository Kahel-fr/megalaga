#include "game.h"

void powerups_fire_init(){
    powerups_fire_bullets_on_screen = 0;
}

void powerups_fire_start(){
    powerups_fire_bullets_fired = 0;
    powerups_fire_timer = getTime(1);
}

bool powerups_fire_update(){
    if(powerups_fire_bullets_fired < POWERUPS_FIRE_BULLETS_NUMBER && (getTime(1) - powerups_fire_timer) >= 30){
        Entity* b;
        b = &powerups_fire_bullets[powerups_fire_bullets_fired];
        b->type = ENTITY_BULLET;
        b->health = 1;
        b->w = 8;
        b->h = 8;
        b->maxhealth = 1;
        b->sprite = SPR_addSprite(&bullet,powerups_fire_bullets[0].x,powerups_fire_bullets[0].y,TILE_ATTR(PAL2,0,FALSE,FALSE));
        b->x = player.x+4;
        b->y = player.y;

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
        powerups_fire_shootone(b);
        powerups_fire_bullets_on_screen++;
        powerups_fire_bullets_fired++;
        powerups_fire_timer = getTime(1);
    }
    return (powerups_fire_bullets_fired < POWERUPS_FIRE_BULLETS_NUMBER);
}

void powerups_fire_shootone(Entity* b){
    t_element * obj = create_element(b);
    add_element_to_container(container_bullets, obj);
}