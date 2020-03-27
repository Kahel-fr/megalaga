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

//check collisions between bullets and ennemies
void checkCollisions(){
    u16 ei = 0;
    Entity *e;
    for(ei = 0; ei < MAX_ENEMIES; ei++){
        e = &enemies[ei];
        if(e->health > 0){
            u16 bi = 0;
            Entity *b;
            for(bi = 0; bi < MAX_BULLETS; bi++){
                b = &bullets[bi];
                if(b->health > 0){
                        //if enemy collide with a bullet both die
                    if(doesCollide(e, b)){
                        enemies_take_damage(e, 1);
                        destroyBullet(b);
                        break;
                    }
                }
            }
            if(doesCollide(e, &player)){
                kill_entity(&player);
                paused = 1;
                showText("Game over!");
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
    ennemies_reset();
    wavesCount++;
}

int main()
{
    //is game finished
    paused = 0;

    wavesCount = 1;
    //init inputs
    JOY_init();
    //use the custom inputs handler
    JOY_setEventHandler( &myJoyHandler );
    //load tile
    SYS_disableInts();
    VDP_loadTileSet(background.tileset,1,DMA);
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

    //load sprite engine
    player_init();
    enemies_init();
    powerups_init();
    bullets_init();
    powerups_spawn(POWERUP_FIRE, player.x, player.y - 30);
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
            enemies_update();
            powerups_update();
            checkCollisions();
            if(enemiesLeft == 0){
                loadWave();
            }

            //update sprites
            SPR_update();

            VDP_waitVSync();
        }
	}

	return(0);
}