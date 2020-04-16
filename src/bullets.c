#include "game.h"


void bullets_init(){
    container_bullets = add_container_to_game();
    bulletsOnScreen = 0;
}

void bullets_update(){
    for (t_element *tmp = container_bullets->first; tmp != NULL; tmp = tmp->next){
        Entity* b = (Entity*)tmp->data;
            if(b->health > 0){
                if(b->type == ENTITY_BULLET){
                    b->y += b->vely;
                    if(b->y + b->h < 0){
                        bullets_kill(b);
                    } else{
                        SPR_setPosition(b->sprite,b->x,b->y);
                    } 
                }
            }
            else
            {
                SPR_releaseSprite(b->sprite);
                del_element_from_container(container_bullets, tmp);
            }
    }
}

void bullets_spawn(int x, int y){
        Entity *b = MEM_alloc(sizeof(Entity));
        b->type = ENTITY_BULLET;
        b->w = 8;
        b->h = 8;
        b->x = x+4;
        b->y = y;
        b->vely = -3;
        b->maxhealth = 1;
        b->health = b->maxhealth;
        b->sprite = SPR_addSprite(&bullet,b->x,b->y,TILE_ATTR(PAL1,0,FALSE,FALSE));
        t_element * obj = create_element(b);
        add_element_to_container(container_bullets, obj);
        bulletsOnScreen++;
}

void bullets_kill(Entity* b){
    b->health = 0;
    bulletsOnScreen--;
}