#include <genesis.h>
#include <resources.h>
#include <kdebug.h>

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

int main()
{
    //load tile
    SYS_disableInts();
    VDP_loadTileSet(background.tileset,1,DMA);
    //set his palette
    VDP_setPalette(PAL1, background.palette->data);
    SYS_enableInts();

    //-random background
    //pixel index
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

	while(1)
	{
        //scroll background
        SYS_disableInts();
        VDP_setVerticalScroll(PLAN_B,offset -= 2);
        //to loop the background
        if(offset >= 256) offset = 0;

        //update sprites
        SPR_update();

		VDP_waitVSync();
        SYS_enableInts();
	}

	return(0);
}