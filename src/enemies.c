#include "game.h"

void enemies_init(){

    container_enemies = add_container_to_game();
    //count of ennemies still alive
    enemiesLeft = 0;

    //set color pal used for enemies
    SYS_disableInts();
    VDP_setPaletteColor(34,RGB24_TO_VDPCOLOR(0x0078f8));
    SYS_enableInts();
}

void enemies_update(){
    for (t_element *tmp = container_enemies->first; tmp != NULL; tmp = tmp->next) {
        Entity* e = (Entity*)tmp->data;
        if(e->type == ENTITY_ENNEMY){
            if(e->health > 0){
                if(e->x+e->w > RIGHT_EDGE || e->x < LEFT_EDGE){
                    e->velx = -e->velx;
                    e->y += e->h;
                }
                //add velocity to current position
                e->x += e->velx;
                e->y += e->vely;
                //set sprite position
                SPR_setPosition(e->sprite,e->x,e->y);
                enemies_random_shoot(e);
            }
            else{
                if(!powerups_spawned && !powerups_active && (random() % 2)==0)
                    powerups_spawn_random(e->x, e->y);
                SPR_releaseSprite(e->sprite);
                del_element_from_container(container_enemies, tmp);
                enemiesLeft--;
            }
        }
    }
}

void ennemies_reset(){
    //KLog("reset");
    enemiesLeft = 0;
    int ennemies_count = ((wavesCount%MAX_ENEMIES));
    int ennemies_speed = 1+wavesCount/MAX_ENEMIES;
    int ennemies_health = ennemies_speed*2;
    for (u16 i = 0; i < ennemies_count;i++) 
    {
        Entity *e = MEM_alloc(sizeof(Entity));
        e->type = ENTITY_ENNEMY;
        e->x = i*32;
        e->y = 16;
        e->w = 16;
        e->h = 16;
        e->velx = ennemies_speed;
        e->maxhealth = ennemies_health;
        e->health = e->maxhealth;
        e->sprite = SPR_addSprite(&ship,e->x,e->y,TILE_ATTR(PAL2,0,TRUE,FALSE));
        sprintf(e->name, "En%d",i);
        t_element * obj = create_element(e);
        add_element_to_container(container_enemies, obj);
        enemiesLeft++;
        i++;
    }
    timer = getTime(0);
}

void enemies_kill(Entity* e){
    kill_entity(e);
    if(enemiesLeft>0)
        enemiesLeft--;
    //entity_delete(e);
}

void enemies_take_damage(Entity* e, int damage){
    entity_take_damage(e, damage);
}

void enemies_random_shoot(Entity* e){
    if(getTime(0)-timer>200 && (random() % 10)==0){
        bullets_spawn(e->x, e->y, 1);
        timer = getTime(0);
    }
}