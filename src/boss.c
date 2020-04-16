#include "game.h"

void boss_init(){
        boss_entity.x = 130;
        boss_entity.y = 0;
        boss_entity.w = 64;
        boss_entity.h = 48;
        boss_entity.maxhealth = BOSS_PHASES_NUMBER * BOSS_HEALTH_BY_PHASE;
        boss_entity.health = boss_entity.maxhealth;
        boss_entity.sprite = SPR_addSprite(&boss,boss_entity.x,boss_entity.y,TILE_ATTR(PAL3,0,FALSE,FALSE));
        sprintf(boss_entity.name, "boss");
        t_element * obj = create_element(&boss_entity);
        add_element_to_container(container_enemies, obj);
        enemiesLeft++;
        boss_current_phase = 0;
        boss_is_moving = 0;
        boss_minions_spawned = 0;

        boss_phases_positions[0].x = (RIGHT_EDGE/2)-(boss_entity.w/2);
        boss_phases_positions[0].y = BOTTOM_EDGE-180;
        boss_phases_positions[1].x = RIGHT_EDGE-boss_entity.w;
        boss_phases_positions[1].y = 0;
        boss_phases_positions[2].x = RIGHT_EDGE-boss_entity.w;
        boss_phases_positions[2].y = BOTTOM_EDGE-boss_entity.h;
        boss_phases_positions[3].x = 0;
        boss_phases_positions[3].y = BOTTOM_EDGE-boss_entity.h;
}

void boss_update(){
    boss_update_movement();
    boss_entity.isInvincible = boss_is_moving || enemiesLeft > 1;
    if(boss_is_moving){
        boss_entity.x+=boss_entity.velx;
        boss_entity.y+=boss_entity.vely;
        SPR_setPosition(boss_entity.sprite,boss_entity.x,boss_entity.y);
        return;
    }
    if(boss_entity.health%BOSS_HEALTH_BY_PHASE==0 && (BOSS_PHASES_NUMBER - boss_entity.health / BOSS_HEALTH_BY_PHASE) != boss_current_phase){
        boss_current_phase++;
        timer = getTime(0);
    }
    if(boss_entity.health <= 0)
        boss_kill();
    switch(boss_current_phase){
        case 0:
            boss_spawn_minions();
            boss_update_minions();
        break;
    }
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
    boss_entity.vely = distanceY < 1 ? 0 : (positionY-boss_entity.y)/distanceY;
    boss_is_moving = abs(boss_entity.velx) + abs(boss_entity.vely) > 0;
}

void boss_spawn_minions(){
    if(getTime(0)-timer>=50 && boss_minions_spawned < BOSS_MINIONS_NUMBER){
        KLog("spawn minion");
        timer = getTime(0);
        Entity *minion = &boss_minions[boss_minions_spawned];
        minion->type = ENTITY_ENNEMY;
        minion->h = 16;
        minion->w = 16;
        minion->x = boss_entity.x+(boss_entity.w/2-minion->w/2);
        minion->y = boss_entity.y+70;
        minion->maxhealth = 1;
        minion->health = 1;
        minion->sprite = SPR_addSprite(&ship,minion->x,minion->y,TILE_ATTR(PAL2,0,TRUE,FALSE));
        t_element * obj = create_element(minion);
        add_element_to_container(container_enemies, obj);
        boss_minions_spawned++;
        enemiesLeft++;
    }
}

void boss_update_minions(){
    fix32 rotation = fix32Div(intToFix32(getTime(0)), FIX32(1000));
    for(int i = 0; i < boss_minions_spawned; i++){
        Entity* minion = &boss_minions[i];

        if(minion->health > 0){
            minion->x = 3*fix16ToInt(cosFix32(rotation+i*100)) + boss_entity.x+(boss_entity.w/2-minion->w/2);
            minion->y = 3*fix16ToInt(sinFix32(rotation+i*100)) + boss_entity.y+(boss_entity.h/2-minion->h/2);
            SPR_setPosition(minion->sprite,minion->x,minion->y);
        }
    }
}