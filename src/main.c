#include <genesis.h>
#include <resources.h>
#include <kdebug.h>

int main()
{
    //disable system inputs
    SYS_disableInts();

    //load tile
    VDP_loadTileSet(background.tileset,1,DMA);
    //set his palette
    VDP_setPalette(PAL1, background.palette->data);

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
        VDP_setTileMapXY(PLAN_B,TILE_ATTR_FULL(PAL1,0,0,0,val), thex, they );
    }

    //store background offset
    int offset = 0;
    //set scrolling for moving background
    VDP_setScrollingMode(HSCROLL_PLANE,VSCROLL_PLANE);
	while(1)
	{
        //scroll background
        VDP_setVerticalScroll(PLAN_B,offset -= 2);
        //to loop the background
        if(offset >= 256) offset = 0;

		VDP_waitVSync();
	}

    //re-enable system inputs
    SYS_enableInts();
	return(0);
}