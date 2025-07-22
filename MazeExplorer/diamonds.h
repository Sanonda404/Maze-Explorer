#ifndef DIAMONDS_H
#define DIAMONDS_H
#include "iGraphics.h"
#include <cstdlib> // for rand
#include <ctime>   // for time

#define MAX_LEVELS 6
#define MAX_DIAMONDS 10 // max per level

extern int current_lvl;

int max_diamonds[MAX_LEVELS] = {2, 3, 5, 4, 6, 6};

typedef struct {
    Image frames[1];
    Sprite sprite;
    int is_visible;
    int pos_x;
    int pos_y;
} Diamond;

Diamond diamonds[MAX_DIAMONDS];

// Position arrays
int diamond_x[MAX_LEVELS][MAX_DIAMONDS];
int diamond_y[MAX_LEVELS][MAX_DIAMONDS];

int x_range_start[6][10] = {{1975,570,550}};//add the start of range x
int x_range_end[6][10] = {{2175,1780,715}};//add the end of range x
int y_range_start[6][10] = {{600,200,1570}};//add the start of range y
int y_range_end[6][10] = {{970,1800,1675}};//add the end of range y

void generate_random_diamond_positions(int level) {
    int count = max_diamonds[level];
    int zones = 0;
    for (int i = 0; i < 10; i++) {
        if (x_range_end[level][i] > x_range_start[level][i]) zones++;
    }

    int min_gap = 100; // Minimum distance between diamonds (adjust if needed)

    for (int i = 0; i < count; i++) {
        int try_count = 0;
        int valid = 0;

        while (!valid && try_count < 100) {
            try_count++;
            int zone = rand() % zones;

            int new_x = x_range_start[level][zone] + rand() % 
                        (x_range_end[level][zone] - x_range_start[level][zone]);
            int new_y = y_range_start[level][zone] + rand() % 
                        (y_range_end[level][zone] - y_range_start[level][zone]);

            valid = 1;
            for (int j = 0; j < i; j++) {
                int dx = new_x - diamond_x[level][j];
                int dy = new_y - diamond_y[level][j];
                if (dx * dx + dy * dy < min_gap * min_gap) {
                    valid = 0; // too close to another diamond
                    break;
                }
            }

            if (valid) {
                diamond_x[level][i] = new_x;
                diamond_y[level][i] = new_y;
            }
        }

        if (!valid) {
            // fallback if too many attempts: just place at origin (or skip)
            diamond_x[level][i] = x_range_start[level][0];
            diamond_y[level][i] = y_range_start[level][0];
        }
    }
}


void loadDiamonds() {
    int level = current_lvl - 1;
    int count = max_diamonds[level];

    generate_random_diamond_positions(level);

    for (int i = 0; i < count; i++) {
        iLoadFramesFromSheet(diamonds[i].frames, "MazeExplorer/assests/levels/diamond.png", 1, 1);
        iInitSprite(&diamonds[i].sprite);
        iChangeSpriteFrames(&diamonds[i].sprite, diamonds[i].frames, 1);

        iSetSpritePosition(&diamonds[i].sprite, diamond_x[level][i], diamond_y[level][i]);
        iScaleSprite(&diamonds[i].sprite, 0.5);
        diamonds[i].is_visible = 1;
    }
}

void draw_diamonds(int cam_x, int cam_y) {
    int level = current_lvl - 1;
    int count = max_diamonds[level];

    for (int i = 0; i < count; i++) {
        if (diamonds[i].is_visible) {
            diamonds[i].sprite.x = diamond_x[level][i] + cam_x;
            diamonds[i].sprite.y = diamond_y[level][i] + cam_y;
            iShowSprite(&diamonds[i].sprite);
        }
    }
}

void reset_diamonds() {
    int level = current_lvl - 1;
    int count = max_diamonds[level];
    for (int i = 0; i < count; i++) {
        diamonds[i].is_visible = 1;
    }
}

#endif
