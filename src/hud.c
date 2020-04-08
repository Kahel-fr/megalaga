#include "game.h"

void hud_print(){
    sprintf(hud_string,"WAVE %d",wavesCount);
    VDP_clearText(0,0,40);
    VDP_drawText(hud_string,0,0);
}