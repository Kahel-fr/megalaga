#include <genesis.h>
#include <resources.h>
#include <kdebug.h>

int main()
{
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




	while(1)
	{
		VDP_waitVSync();
	}

	return(0);
}