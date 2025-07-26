#ifndef TELEPORTATION_PORTAL_H
#define TELEPORTATION_PORTAL_H

#include "iGraphics.h"
#include "MazeExplorer/player.h"
#include <cstdlib>
#include <stdlib.h> // for rand
#include <ctime>   // for time
#include "MazeExplorer/level_dependencies.h"

Image teleportation_portal[1];
Sprite teleportation_portal_collision,portal;

const int teleportation_portal_size = 150; // width/height in pixels

int teleportation_portal_x, teleportation_portal_y;
int pdx,pdy;

int portal_pos_x[6][10] = {{1315,1415,2455,2485,1690,595}};
int portal_pos_y[6][10] = {{910,1615,280,1210,1595,1975}};

// Load the portal sprite and image
void load_portal() {
    iLoadFramesFromSheet(teleportation_portal, "MazeExplorer/assests/levels/teleportation portal.png",1,1);
    iInitSprite(&portal);
    iChangeSpriteFrames(&portal, teleportation_portal, 1);
    iSetSpritePosition(&portal, 0,01);
    iScaleSprite(&portal,3.0);
    //iInitSprite(&teleportation_portal_collision);
}

// Check if the region is entirely black
bool is_black_region(int x, int y) {
    int rgb[3];
    for (int dx = 0; dx < teleportation_portal_size; dx += 10) {         // Step by 10 to speed up
        for (int dy = 0; dy < teleportation_portal_size; dy += 10) {
            iGetPixelColor(x + dx, y + dy, rgb);
            if (!(rgb[0] == 234 && rgb[1] == 24 && rgb[2] == 119)) {
                return false; // not black
            }
        }
    }
    return true;
}

// Generate a random valid position for the portal
void generate_portal_position(int x_start, int x_end, int y_start, int y_end,Sprite *maze) {
    //printf("bool %d",is_black_region(x_start,y_start));

    for (int attempt = 0; attempt < 1000; ++attempt) {
        int x = x_start + rand() % (x_end - x_start - teleportation_portal_size);
        int y = y_start + rand() % (y_end - y_start - teleportation_portal_size);

        if (!iCheckCollision(&portal, maze)) {
            teleportation_portal_x = x;
            teleportation_portal_y = y;
            pdx = x;
            pdy = y;
            printf("Portal Pos %d %d\n",x,y);
            return;
        }
    }

    // nothing found sad
    int x = rand()%6;
    teleportation_portal_x = portal_pos_x[0][x];
    teleportation_portal_y = portal_pos_y[0][x];
    pdx = teleportation_portal_x;
    pdy = teleportation_portal_y;
    printf("Failed");
    printf("Portal Pos %d %d %d\n",x,portal_pos_x,portal_pos_y);
}

// Draw the portal
void draw_teleportation_portal(int x_offset, int y_offset) {
    portal.x = teleportation_portal_x + x_offset;
    portal.y = teleportation_portal_y + y_offset;
}

// Check if player touched the portal, and teleport if so
bool check_collision_and_teleport(int x_start, int x_end, int y_start, int y_end) {
    if (iCheckCollision(&teleportation_portal_collision, &player.sprite)) {
        //generate_portal_position(x_start, x_end, y_start, y_end); // move portal to a new position
        return true;
    }
    return false;
}

#endif
