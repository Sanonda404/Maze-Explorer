#ifndef TELEPORTATION_PORTAL_H
#define TELEPORTATION_PORTAL_H

#include "iGraphics.h"
#include "MazeExplorer/player.h"
#include <cstdlib>
#include <ctime>
#include "MazeExplorer/level_dependencies.h"

Image teleportation_portal_frames[1];
Sprite portal, teleportation_portal_collision, *maze_sprite;

const int teleportation_portal_size = 150;

int teleportation_portal_x, teleportation_portal_y;
int pdx, pdy;

int x_s,x_e,y_s,y_e;

int portal_pos_x[6][10] = {
    {1315,1315,2455,2400,1690,595},
    {1500,1800,1950,2100,2300,2400},
    {800,900,1000,1100,1200,1300},
    {400,500,600,700,800,900},
    {300,1400,2000,2300,2600,2800},
    {600,650,1200,1600,1900,2100}
};

int portal_pos_y[6][10] = {
    {910,1615,280,1210,1595,1975},
    {1800,1750,1700,1650,1600,1550},
    {1000,1100,1200,1300,1400,1500},
    {100,300,500,700,900,1100},
    {2000,1800,1600,1400,1200,1000},
    {400,600,800,1000,1200,1400}
};

int player_teleportation_pos[6][10] = {};

void load_portal() {
    iLoadFramesFromSheet(teleportation_portal_frames, "MazeExplorer/assests/levels/teleportation portal.png", 1, 1);

    iInitSprite(&portal);
    iChangeSpriteFrames(&portal, teleportation_portal_frames, 1);
    iSetSpritePosition(&portal, 0, 0);

    iInitSprite(&teleportation_portal_collision);  // This is the real collision sprite
    iChangeSpriteFrames(&teleportation_portal_collision, teleportation_portal_frames, 1);
    iSetSpritePosition(&teleportation_portal_collision, 0, 0);
}

void generate_portal_position(int x_start, int x_end, int y_start, int y_end, Sprite *maze) {
    maze_sprite = maze;
    x_s=x_start;
    x_e = x_end;
    y_s = y_start;
    y_e = y_end;
    for (int attempt = 0; attempt < 1000; ++attempt) {
        int x = x_start + rand() % (x_end - x_start - teleportation_portal_size);
        int y = y_start + rand() % (y_end - y_start - teleportation_portal_size);

        iSetSpritePosition(&teleportation_portal_collision, x, y);

        if (!iCheckCollision(&teleportation_portal_collision, maze) && !portal_collision(&portal)) {
            teleportation_portal_x = x;
            teleportation_portal_y = y;
            pdx = x;
            pdy = y;
            printf("Portal placed at: %d %d\n", x, y);
            return;
        }
    }

    // Fallback if no good position found
    int lvl = current_lvl - 1;
    int idx = rand() % 6;
    teleportation_portal_x = portal_pos_x[lvl][idx];
    teleportation_portal_y = portal_pos_y[lvl][idx];
    pdx = teleportation_portal_x;
    pdy = teleportation_portal_y;

    printf("Failed to find empty space. Using fallback portal position at %d %d\n",
           teleportation_portal_x, teleportation_portal_y);
}

void teleport_player()
{
    for (int attempt = 0; attempt < 1000; ++attempt) {
        int x = x_s + rand() % (x_e - x_s - 120);
        int y = y_s + rand() % (y_e - y_s- 120);

        iSetSpritePosition(&teleportation_portal_collision, x, y);

        if (!iCheckCollision(&player.sprite, maze_sprite) && !portal_collision(&player.sprite)) {
            player_relative_x = x;
            player_relative_y = y;
            printf("Portal placed at: %d %d\n", x, y);
            return;
        }
    }

    // Fallback if no good position found
    int lvl = current_lvl - 1;
    int idx = rand() % 6;
    player_relative_x = portal_pos_x[lvl][idx];
    player_relative_y = portal_pos_y[lvl][idx];

    printf("Failed to find empty space. Using fallback player position at %d %d\n",
           player_relative_x, player_relative_y);
}

void check_collision_and_teleport() {
    if(iCheckCollision(&player.sprite, &portal)){
        printf("Teleporting!!!");
        teleport_player();
    }
}

void draw_teleportation_portal(int x_offset, int y_offset) {
    int draw_x = teleportation_portal_x + x_offset;
    int draw_y = teleportation_portal_y + y_offset;

    iSetSpritePosition(&portal, draw_x, draw_y);
    iSetSpritePosition(&teleportation_portal_collision, draw_x, draw_y);
    iShowSprite(&portal);

    check_collision_and_teleport();
}
#endif
