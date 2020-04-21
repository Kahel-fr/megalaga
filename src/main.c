#include "game.h"

//display text on screen
void showText(char s[]){
	VDP_drawText(s, 20 - strlen(s)/2 ,15);
}

//return true if two entities collide
bool doesCollide(Entity *a, Entity *b){
    return a->x < b->x + b->w &&
   a->x + a->w > b->x &&
   a->y < b->y + b->h &&
   a->h + a->y > b->y;
}

void get_direction_between_two_points(int start_x, int start_y, int end_x, int end_y, fix16* velx, fix16* vely){
    int distance = getApproximatedDistance(end_x - start_x, end_y - start_y);
    if(distance==0) distance = 1;
    *velx = fix16Div(fix16Sub(intToFix16(end_x), intToFix16(start_x)), intToFix16(distance));
    *vely = fix16Div(fix16Sub(intToFix16(end_y), intToFix16(start_y)), intToFix16(distance));
}

//check collisions between bullets and ennemies
void checkCollisions(){
    u16 ei = 0;
    Entity *e;
    for(t_element *tmp = container_bullets->first; tmp != NULL; tmp = tmp->next){
        Entity* b = (Entity*)tmp->data;
        if(b->type==ENTITY_ENNEMY_BULLET || b->type==ENTITY_BOSS_PROJECTILE){
            if(doesCollide(&player, b)){
                entity_take_damage(&player, 1);
                bullets_kill(b);
                hud_print();
            }
        }
        else{
            if(boss_projectile_spawned && !boss_projectile_is_reflected && doesCollide(&boss_projectile_entity, b)){
                boss_projectile_hit_by_player();
                bullets_kill(b);
            }
            else{
                for (t_element *tmp = container_enemies->first; tmp != NULL; tmp = tmp->next) {
                    Entity* e = (Entity*)tmp->data;
                    if(e->health > 0 && !e->isInvincible){
                        if(doesCollide(e, b)){
                            //KDebug_AlertNumber(b->type);
                            switch(b->type){
                                case ENTITY_RAY:
                                    powerups_ray_hit(e);
                                break;
                                default:
                                    enemies_take_damage(e, 1);
                                    bullets_kill(b);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    if(powerups_spawned){
        if(doesCollide(&player, powerups_current_spawned_entity)){
            powerups_start();
            kill_entity(powerups_current_spawned_entity);
        }
    }
}

//inputs handler that will be used
void myJoyHandler( u16 joy, u16 changed, u16 state)
{
    //for the joystick 1
    if (joy == JOY_1)
    {
        //DEBUG TO REMOVE
        if (state & BUTTON_A & changed)
        {
            /*Entity* e;
            for (t_element *tmp = container_enemies->first; tmp != NULL; tmp = tmp->next) {
                Entity* e = (Entity*)tmp->data;
                entity_take_damage(e, 999);
            }*/
            powerups_spawn(POWERUP_FIRE, player.x, player.y-20);
        }
        //if B button is pressed once
        if (state & BUTTON_B & changed)
        {
            //shoot a bullet
            shootBullet();
        }
        //if start button is pressed
        if(state & BUTTON_START & changed){
            paused = !paused;
        }
        //if right button is pressed
        if (state & BUTTON_RIGHT)
	    {
            //set velocity to 2 to the right
            player.velx = 2;
            //set sprite to moving animation
            SPR_setAnim(player.sprite,ANIM_MOVE);
            //"mirror" the sprite to right (flip the sprite)
            SPR_setHFlip(player.sprite,TRUE);
        }
         //if left button is pressed
        else if (state & BUTTON_LEFT)
        {
            //set velocity to 2 to the left
            player.velx = -2;
            //set sprite to moving animation
            SPR_setAnim(player.sprite,ANIM_MOVE);
            //"mirror" the sprite to left (unflip the sprite)
            SPR_setHFlip(player.sprite,FALSE);
        }
        //if no direction button is pressed
        else{
            if( (changed & BUTTON_RIGHT) | (changed & BUTTON_LEFT) ){
                //no velocity
                player.velx = 0;
                //set sprite to not moving animation
                SPR_setAnim(player.sprite,ANIM_STRAIGHT);
            }
        }
    }
}

void loadWave(){
    wavesCount++;
    if(wavesCount % 10 == 0){
        boss_init();
        isBossWave = 1;
    }
    else
        ennemies_reset();
}

void game_reset(){
    paused = 0;
    wavesCount = 9;
    isBossWave = 0;
    ennemies_clear();
    player_reset();
    loadWave();
    hud_print();
}

void game_over(){
    game_reset();
}

int main()
{

    //init inputs
    JOY_init();
    //use the custom inputs handler
    JOY_setEventHandler( &myJoyHandler );
    //load tile
    SYS_disableInts();
    VDP_loadTileSet(background.tileset,1,DMA);
    VDP_loadTileSet(heart.tileset,5,DMA);
    //set his palette
    VDP_setPalette(PAL1, background.palette->data);
    SYS_enableInts();

    SPR_init();

    //-random background
    //index used for tiles and ennemies
    int i = 0;
    //tile position
    int thex = 0;
    int they = 0;
    //tile index
    int val = 1;

    //for each pixel
    for( i=0; i < 1280; i++){
        //set tile position
        thex = i % 40;
        they = i / 40;
        //to have a random value between 1 and 10
        val = (random() %  (10-1+1))+1;
        //to have more empty space tiles
        if(val > 3) val = 1;
        //display the tile
        SYS_disableInts();
        VDP_setTileMapXY(PLAN_B,TILE_ATTR_FULL(PAL1,0,0,0,val), thex, they );
        SYS_enableInts();
    }

    //store background offset
    int offset = 0;
    //set scrolling for moving background
    SYS_disableInts();
    VDP_setScrollingMode(HSCROLL_PLANE,VSCROLL_PLANE);
    SYS_enableInts();

    SYS_disableInts();
        VDP_setPalette(PAL3, powerup_pal.data);
    SYS_enableInts();

    //load sprite engine
    player_init();
    enemies_init();
    bullets_init();
    powerups_init();

    game_reset();

	while(1)
	{
        JOY_update();
        if(!paused){
            //scroll background
            SYS_disableInts();
            VDP_setVerticalScroll(PLAN_B,offset -= 2);
            SYS_enableInts();
            //to loop the background
            if(offset >= 256) offset = 0;

            //update entities positions
            player_update();
            bullets_update();
            if(isBossWave)
                boss_update();
            enemies_update();
            powerups_update();
            checkCollisions();
            if(enemiesLeft == 0){
                loadWave();
                hud_print();
            }
            if(player.health<1)
                game_over();

            //update sprites
            SPR_update();

            VDP_waitVSync();
        }
	}

	return(0);
}