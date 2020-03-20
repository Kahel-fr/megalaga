#include <genesis.h>
#include <resources.h>
#include <kdebug.h>

//edges of the screen
#define LEFT_EDGE 0
#define RIGHT_EDGE 320

//number of ennemies
#define MAX_ENEMIES 6

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

//count of ennemies still alive
u16 enemiesLeft = 0;

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

int main()
{
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

	while(1)
	{
        //scroll background
        SYS_disableInts();
        VDP_setVerticalScroll(PLAN_B,offset -= 2);
        //to loop the background
        if(offset >= 256) offset = 0;

        //update enemies positions
        positionEnemies();

        //update sprites
        SPR_update();

		VDP_waitVSync();
        SYS_enableInts();
	}

	return(0);
}