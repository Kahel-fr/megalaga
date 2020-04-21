#include "game.h"

void boss_init(){
        boss_entity.type = ENTITY_BOSS;
        boss_entity.x = 130;
        boss_entity.y = 0;
        boss_entity.w = 64;
        boss_entity.h = 48;
        boss_entity.maxhealth = 29;
        boss_entity.health = boss_entity.maxhealth;
        boss_entity.sprite = SPR_addSprite(&boss,boss_entity.x,boss_entity.y,TILE_ATTR(PAL3,0,FALSE,FALSE));
        sprintf(boss_entity.name, "boss");
        t_element * obj = create_element(&boss_entity);
        add_element_to_container(container_enemies, obj);
        enemiesLeft++;
        boss_current_phase = 0;
        boss_is_moving = 0;
        boss_minions_spawned = 0;
        boss_projectile_spawned = 0;
        boss_x = intToFix16(boss_entity.x);
        boss_y = intToFix16(boss_entity.y);

        boss_start_phase();
}

void boss_update(){
    if(boss_entity.health <= 0){
        boss_kill();
        return;
    }
    boss_update_movement();
    switch(boss_current_phase){
        case 0:
            if(!boss_is_moving){
                boss_entity.isInvincible = enemiesLeft > 1;
                boss_spawn_minions();
                boss_update_minions();
                if(boss_entity.health<16){
                    boss_minions_spawned = 0;
                    boss_next_phase();
                }
            }
        break;
        case 1:
            boss_entity.isInvincible = 1;
            if(!boss_is_moving){
                if(!boss_projectile_spawned)
                    boss_shoot_projectile();
                else{
                    boss_update_projectile();
                    if(boss_entity.health<13)
                        boss_next_phase();
                }
            }
        break;
        case 2:
            if(!boss_is_moving){
                boss_entity.isInvincible = enemiesLeft > 1;
                boss_spawn_minions();
                boss_update_minions();
                if(boss_entity.health<10)
                        boss_next_phase();
            }
        break;
        case 3:
            boss_entity.isInvincible = 1;
            if(!boss_is_moving){
                if(!boss_projectile_spawned)
                    boss_shoot_projectile();
                else{
                    boss_update_projectile();
                }
            }
        break;
    }
    SPR_setPosition(boss_entity.sprite,boss_entity.x,boss_entity.y);
}

void boss_kill(){
    enemies_kill(&boss_entity);
    isBossWave = 0;
}

void boss_next_phase(){
    boss_current_phase++;
    boss_start_phase();
}

void boss_start_phase(){
    switch(boss_current_phase){
        case 0:
            boss_entity.isInvincible = 1;
            boss_move_to((RIGHT_EDGE/2)-(boss_entity.w/2), BOTTOM_EDGE-180);
        break;
        case 1:
            boss_entity.isInvincible = 1;
            boss_move_to(RIGHT_EDGE-boss_entity.w, 0);
        break;
        case 2:
            boss_entity.isInvincible = 1;
            boss_move_to((RIGHT_EDGE/2)-(boss_entity.w/2), BOTTOM_EDGE-180);
        break;
        case 3:
            boss_entity.isInvincible = 1;
            boss_move_to(0, 0);
        break;
    }
}

void boss_move_to(int x, int y){
    boss_moving_target_x = x;
    boss_moving_target_y = y;
    get_direction_between_two_points(boss_entity.x, boss_entity.y, x, y, &boss_velx, &boss_vely);
    boss_velx = fix16Mul(boss_velx, FIX16(2));
    boss_vely = fix16Mul(boss_vely, FIX16(2));
    boss_is_moving = 1;
}

void boss_update_movement(){
    if(boss_is_moving)
        boss_is_moving = getApproximatedDistance(boss_moving_target_x - boss_entity.x, boss_moving_target_y - boss_entity.y)>1;
    if(!boss_is_moving){
        boss_entity.x = boss_moving_target_x;
        boss_entity.y = boss_moving_target_y;
        boss_velx = 0;
        boss_vely = 0;
        boss_is_moving = 0;
    }
    else{
        boss_x = fix16Add(boss_x, boss_velx);
        boss_y = fix16Add(boss_y, boss_vely);
        boss_entity.x = fix16ToRoundedInt(boss_x);
        boss_entity.y = fix16ToRoundedInt(boss_y);
    }
}

void boss_spawn_minions(){
    if(getTime(0)-timer>=50 && boss_minions_spawned < BOSS_MINIONS_NUMBER){
        timer = getTime(0);
        Entity *minion = &boss_minions[boss_minions_spawned];
        minion->type = ENTITY_ENNEMY;
        minion->h = 16;
        minion->w = 16;
        minion->x = boss_entity.x+(boss_entity.w/2-minion->w/2);
        minion->y = boss_entity.y+70;
        minion->maxhealth = 1;
        minion->health = 1;
        minion->sprite = SPR_addSprite(&ship,minion->x,minion->y,TILE_ATTR(PAL3,0,TRUE,FALSE));
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

void boss_shoot_projectile(){
    boss_projectile_entity.type = ENTITY_BOSS_PROJECTILE;
    boss_projectile_entity.w = 16;
    boss_projectile_entity.h = 16;
    boss_projectile_entity.x = boss_entity.x+boss_entity.w/2;
    boss_projectile_entity.y = boss_entity.y+boss_entity.h/2;
    boss_projectile_x = intToFix16(boss_projectile_entity.x);
    boss_projectile_y = intToFix16(boss_projectile_entity.y);

    get_direction_between_two_points(boss_projectile_entity.x+boss_projectile_entity.w/2, boss_projectile_entity.y+boss_projectile_entity.h/2, player.x+player.w/2, player.y+player.h/2, &boss_projectile_velx, &boss_projectile_vely);
    boss_projectile_velx = fix16Mul(boss_projectile_velx, FIX16(2));
    boss_projectile_vely = fix16Mul(boss_projectile_vely, FIX16(2));
    KDebug_AlertNumber(boss_projectile_velx);

    boss_projectile_entity.maxhealth = 1;
    boss_projectile_entity.health = boss_projectile_entity.maxhealth;
    boss_projectile_entity.sprite = SPR_addSprite(&boss_projectile,boss_projectile_entity.x,boss_projectile_entity.y,TILE_ATTR(PAL3,0,FALSE,FALSE));
    t_element * obj = create_element(&boss_projectile_entity);
    add_element_to_container(container_bullets, obj);
    boss_projectile_spawned = 1;
    boss_projectile_is_reflected = 0;
}

void boss_update_projectile(){
    if(boss_projectile_entity.health<1)
        boss_projectile_spawned= 0;
    else{
        boss_projectile_x = fix16Add(boss_projectile_x, boss_projectile_velx);
        boss_projectile_y = fix16Add(boss_projectile_y, boss_projectile_vely);
        boss_projectile_entity.x = fix16ToRoundedInt(boss_projectile_x);
        boss_projectile_entity.y = fix16ToRoundedInt(boss_projectile_y);
        if(boss_projectile_is_reflected && doesCollide(&boss_projectile_entity, &boss_entity)){
            enemies_take_damage(&boss_entity, 1);
            bullets_kill(&boss_projectile_entity);
        }
    }
}

void boss_projectile_hit_by_player(){
    get_direction_between_two_points(boss_projectile_entity.x+boss_projectile_entity.w/2, boss_projectile_entity.y+boss_projectile_entity.h/2, boss_entity.x+boss_entity.w/2, boss_entity.y+boss_entity.h/2, &boss_projectile_velx, &boss_projectile_vely);
    boss_projectile_velx = fix16Mul(boss_projectile_velx, FIX16(2));
    boss_projectile_vely = fix16Mul(boss_projectile_vely, FIX16(2));
    boss_projectile_is_reflected = 1;
}