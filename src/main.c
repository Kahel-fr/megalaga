#include <genesis.h>
#include <resources.h>
#include <kdebug.h>

//edges of the screen
#define LEFT_EDGE 0
#define RIGHT_EDGE 320

//indexes for ship when not moving and when moving
#define ANIM_STRAIGHT 0
#define ANIM_MOVE 1

//max number of ennemies and bullets on the screen
#define MAX_ENEMIES 6
#define MAX_BULLETS	3

//entity structure (like player, ennemies, ect...)
typedef struct {
	int x;
	int y;
	int w;
	int h;
	int velx;
	int vely;
	int health;
	char name[6];
    Sprite* sprite;
} Entity;

//player entity
Entity player = {0, 0, 16, 16, 0, 0, 0, "PLAYER"};

//ennemies entities
Entity enemies[MAX_ENEMIES];

//bullets
Entity bullets[MAX_BULLETS];

//count of ennemies still alive
u16 enemiesLeft = 0;

//count of bullets on screen
u16 bulletsOnScreen = 0;

//kill an entity
void killEntity(Entity* e){
	e->health = 0;
	SPR_setVisibility(e->sprite,HIDDEN);
}

//revive an entity
void reviveEntity(Entity* e){
	e->health = 1;
	SPR_setVisibility(e->sprite,VISIBLE);
}

//update player position (velocity is set by inputs handler)
void positionPlayer(){
    //add velocity to position
    player.x += player.velx;

    //if the position exceeds screen, set position to edge position
    if(player.x < LEFT_EDGE) player.x = LEFT_EDGE;
    if(player.x + player.w > RIGHT_EDGE) player.x = RIGHT_EDGE - player.w;

    //set sprite position
    SPR_setPosition(player.sprite,player.x,player.y);
}

//update ennemies positions
void positionEnemies(){
    u16 i = 0;
    //for each ennemy
    for(i = 0; i < MAX_ENEMIES; i++){
        Entity* e = &enemies[i];
        //if the ennemy is still alive
        if(e->health > 0){
            //if the future position exceeds screen, change direction
            if( (e->x+e->w) > RIGHT_EDGE){
                e->velx = -1;
            }
            else if(e->x < LEFT_EDGE){
                e->velx = 1;
            }
            //add velocity to current position
            e->x += e->velx;
            //set sprite position
            SPR_setPosition(e->sprite,e->x,e->y);
        }
    }
}

//update bullets positions
void positionBullets(){
    u16 i = 0;
    Entity *b;
    for(i = 0; i < MAX_BULLETS; i++){
        b = &bullets[i];
        if(b->health > 0){
          b->y += b->vely;
            if(b->y + b->h < 0){
                killEntity(b);
                bulletsOnScreen--;
            } else{
                SPR_setPosition(b->sprite,b->x,b->y);
            }  
        }
    }
}

//check collisions between bullets and ennemies
void checkCollisions(){
    u16 bi = 0;
    Entity *b;
    for(bi = 0; bi < MAX_BULLETS; bi++){
        b = &bullets[bi];
        if(b->health > 0){
            u16 ei = 0;
            Entity *e;
            for(ei = 0; ei < MAX_ENEMIES; ei++){
                e = &enemies[ei];
                if(e->health > 0){
                    if(b->x >= e->x && b->x <= e->x + e->w && b->y >= e->y && b->y <= e->y + e->h){
                        killEntity(e);
                        enemiesLeft--;
                        killEntity(b);
                        bulletsOnScreen--;
                        break;
                    }
                }
            }
        }
    }
}

//shoot a bullet
void shootBullet(){
    if( bulletsOnScreen < MAX_BULLETS ){
        Entity* b;
        u16 i = 0;
        for(i=0; i<MAX_BULLETS; i++){
            b = &bullets[i];
            if(b->health == 0){

                b->x = player.x+4;
                b->y = player.y;

                reviveEntity(b);
                b->vely = -3;

                SPR_setPosition(b->sprite,b->x,b->y);
                bulletsOnScreen++;
                break;
            }
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

int main()
{
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
    SPR_init();

    /*Add the player*/
    player.x = 152;
    player.y = 192;
    player.health = 1;
    player.sprite = SPR_addSprite(&ship,player.x,player.y,TILE_ATTR(PAL1,0,FALSE,FALSE));
    SPR_update();

    /*Create all enemy*/
    //point to first ennemy
    Entity* e = enemies;
    //for each enemy
    for(i = 0; i < MAX_ENEMIES; i++){
        //set position, size, health
        e->x = i*32;
        e->y = 32;
        e->w = 16;
        e->h = 16;
        e->velx = 1;
        e->health = 1;
        //set sprite (using ship sprite but flipped toward player and with a different color pal)
        e->sprite = SPR_addSprite(&ship,e->x,e->y,TILE_ATTR(PAL2,0,TRUE,FALSE));
        //set ennemy name
        sprintf(e->name, "En%d",i);
        //increment ennemy count
        enemiesLeft++;
        //next enemy
        e++;
    }
    //set color pal used for enemies
    VDP_setPaletteColor(34,RGB24_TO_VDPCOLOR(0x0078f8));

    /*create bullets entities*/
    //point to first ennemy
    Entity* b = bullets;
    //for each bullet
    for(i = 0; i < MAX_BULLETS; i++){
        //set position and size
        b->x = 0;
        b->y = -10;
        b->w = 8;
        b->h = 8;
        //set sprite
        b->sprite = SPR_addSprite(&bullet,bullets[0].x,bullets[0].y,TILE_ATTR(PAL1,0,FALSE,FALSE));
        //set name
        sprintf(b->name, "Bu%d",i);
        //next bullet
        b++;
    }

	while(1)
	{
        //scroll background
        SYS_disableInts();
        VDP_setVerticalScroll(PLAN_B,offset -= 2);
        //to loop the background
        if(offset >= 256) offset = 0;

        //update entities positions
        positionPlayer();
        positionBullets();
        positionEnemies();
        checkCollisions();

        //update sprites
        SPR_update();

		VDP_waitVSync();
        SYS_enableInts();
	}

	return(0);
}