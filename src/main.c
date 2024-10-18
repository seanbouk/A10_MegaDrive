#include <genesis.h>
#include <resources.h>

#define ANIM_STILL 0
#define ANIM_IDLE 1
#define ANIM_WALK 2
#define ANIM_UPPER 3

u16 ind = TILE_USER_INDEX;
float bg_x = 0;
int fg_x = 0;
Sprite* player;

float player_x = 10;
float dx = 0;
float d2x = 0.2;

float player_y = 10;
float roll = 0;
float rollD = 0.2;
float dy = 0;
float my = 0.1;
float dyMax = 2;
float yu = 0.95;

int floor(float x) {
    int xi = (int)x;
    return (x < xi) ? (xi - 1) : xi;
}

void intToString(int num, char *str) {
    sprintf(str, "%d", num);
}

void floatToString(float num, char *str) {
    sprintf(str, "%.2f", num); // Format the float to 2 decimal places
}

float lerp(float start, float end, float t) {
    return start + t * (end - start);
}

static void handleInput() {
    u16 value = JOY_readJoypad(JOY_1);
    if (value & BUTTON_UP) {
        roll += rollD;
    }
    else if (value & BUTTON_DOWN) {
        roll -= rollD;
    }
    else {
        if (roll > rollD)
        {
            roll -= rollD;
        } else if (roll < -rollD) {
            roll += rollD;
        }
        else {
            roll = 0;
        }
    }

    if (value & BUTTON_LEFT) {
        dx = lerp(dx, -2, d2x);
    } else if (value & BUTTON_RIGHT) {
        dx = lerp(dx, 0.75, d2x);
    }
    else {
        dx = lerp(dx, 0, d2x);
    }

    roll = clamp(roll, -4, 4);
    dy -= roll * my;//roll accelerates in y
    dy *= yu;//yfriction acts against velocity
    dy = clamp(dy, -dyMax, dyMax);

    player_y += dy;
    player_y = clamp(player_y, -32, 192);

    player_x += dx;

    SPR_setPosition(player, player_x, player_y);
    SPR_setFrame(player, floor(roll)+4);
}

int main()
{
    //VDP_drawText("Hello Mega Drive", 12,13);

    SPR_init();
    PAL_setPalette(PAL2, our_sprite.palette->data, DMA);
    player = SPR_addSprite(&our_sprite, player_x, player_y, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
    SPR_setAnim(player, ANIM_IDLE);

    PAL_setPalette(PAL0, bg1.palette->data, DMA);
    VDP_drawImageEx(BG_B, &bg1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += bg1.tileset->numTile;
    PAL_setPalette(PAL1, fg1.palette->data, DMA);
    VDP_drawImageEx(BG_A, &fg1, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += fg1.tileset->numTile;

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    while(1)
    {
        handleInput();
        SPR_update();

        bg_x -= 1.75;
        VDP_setHorizontalScroll(BG_B, floor(bg_x));

        fg_x -= 2;
        VDP_setHorizontalScroll(BG_A, fg_x);

        SYS_doVBlankProcess();
    }
    return (0);
}
