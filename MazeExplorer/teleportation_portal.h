#ifndef TELEPORTATION_PORTAL_H
#define TELEPORTATION_PORTAL_H

#include "iGraphics.h"
#include "MazeExplorer/player.h"
#include <cstdlib>
#include <ctime>

Image teleportation_portal;
Sprite teleportation_portal_collision;

const int teleportation_portal_size = 150; // width/height in pixels

int teleportation_portal_x, teleportation_portal_y;
int pdx,pdy;

// Load the portal sprite and image
void load_portal() {
    iLoadImage(&teleportation_portal, "MazeExplorer/assests/levels/teleportation portal.png");
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
void generate_portal_position(int x_start, int x_end, int y_start, int y_end) {
    //printf("bool %d",is_black_region(x_start,y_start));

    for (int attempt = 0; attempt < 1000; ++attempt) {
        int x = x_start + rand() % (x_end - x_start - teleportation_portal_size);
        int y = y_start + rand() % (y_end - y_start - teleportation_portal_size);

        if (is_black_region(x, y)) {
            teleportation_portal_x = x;
            teleportation_portal_y = y;
            pdx = x;
            pdy = y;
            printf("Portal Pos %d %d\n",x,y);
            return;
        }
    }

    // nothing found sad
    iSetSpritePosition(&teleportation_portal_collision, x_start, y_start);
    printf("Failed");
}

// Draw the portal
void draw_teleportation_portal(int x_offset, int y_offset) {
    pdx = teleportation_portal_x + x_offset;
    pdy = teleportation_portal_y + y_offset;

    iShowImage(
        pdx,
        pdy,
        "MazeExplorer/assests/levels/teleportation portal.png");
}

// Check if player touched the portal, and teleport if so
bool check_collision_and_teleport(int x_start, int x_end, int y_start, int y_end) {
    if (iCheckCollision(&teleportation_portal_collision, &player.sprite)) {
        generate_portal_position(x_start, x_end, y_start, y_end); // move portal to a new position
        return true;
    }
    return false;
}

#endif
