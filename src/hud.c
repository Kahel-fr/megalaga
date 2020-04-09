#include "game.h"

void hud_print(){
    VDP_clearPlan(PLAN_A, 0);
    sprintf(hud_string,"WAVE %d",wavesCount);
    VDP_clearText(0,0,40);
    VDP_drawText(hud_string,0,0);
    for(int i = 0; i < player.health;i++){
        SYS_disableInts();
        VDP_setTileMapXY(PLAN_A,TILE_ATTR_FULL(PAL1,0,0,0,5), 36+i, 26);
        SYS_enableInts();
    }
}