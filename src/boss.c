#include "game.h"

void boss_init(){
        boss_entity.x = 130;
        boss_entity.y = 90;
        boss_entity.w = 64;
        boss_entity.h = 48;
        boss_entity.health = BOSS_PHASES_NUMBER * BOSS_HEALTH_BY_PHASE;
        boss_entity.sprite = SPR_addSprite(&boss,boss_entity.x,boss_entity.y,TILE_ATTR(PAL3,0,FALSE,FALSE));
        sprintf(boss_entity.name, "boss");
        enemiesLeft++;

        boss_current_phase = -1;
        boss_is_moving = 0;

        boss_phases_positions[0].x = 50;
        boss_phases_positions[0].y = 50;
        boss_phases_positions[1].x = 130;
        boss_phases_positions[1].y = 90;
        boss_phases_positions[2].x = 200;
        boss_phases_positions[2].y = 90;
}

void boss_update(){
    if(boss_current_phase>=0)
        boss_update_movement();
    if(boss_is_moving){
        boss_entity.x+=boss_entity.velx;
        boss_entity.y+=boss_entity.vely;
        SPR_setPosition(boss_entity.sprite,boss_entity.x,boss_entity.y);
    }
    
    u16 bi = 0;
    Entity *b;
    if(!boss_is_moving)
    for(bi = 0; bi < MAX_BULLETS; bi++){
        b = &bullets[bi];
        if(b->health > 0){
            if(doesCollide(b, &boss_entity)){
                enemies_take_damage(&boss_entity, 1);
                destroyBullet(b);
                if(boss_entity.health%BOSS_HEALTH_BY_PHASE==0)
                    boss_current_phase++;
            }
        }
    }
    if(boss_entity.health <= 0)
        boss_kill();
}

void boss_kill(){
    enemies_kill(&boss_entity);
    isBossWave = 0;
}

void boss_update_movement(){
    int positionX = boss_phases_positions[boss_current_phase].x;
    int positionY = boss_phases_positions[boss_current_phase].y;
    float distanceX = abs(positionX-boss_entity.x);
    float distanceY = abs(positionY-boss_entity.y);
    boss_entity.velx = distanceX < 1 ? 0 : (positionX -boss_entity.x)/distanceX;
    boss_entity.vely = distanceY < 1 ? 0 : (positionY-boss_entity.x)/distanceX;
    boss_is_moving = abs(boss_entity.velx + boss_entity.vely) > 0;
}