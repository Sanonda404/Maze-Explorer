#ifndef DIAMONDS_H
#define DIAMONDS_H

#include "iGraphics.h"
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unordered_set>

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

// Store diamond positions
int diamond_x[MAX_LEVELS][MAX_DIAMONDS] = {0};
int diamond_y[MAX_LEVELS][MAX_DIAMONDS] = {0};

// Ranges (hardcoded per level)
int x_range_start[6][10] = {{800, 700, 500, 400, 400, 800, 400, 1000}, {640, 2350, 1500, 640, 1000, 1500, 900, 2000, 1200}, {700, 1000, 1000, 2050, 750, 2000, 1000, 750, 900, 1800}, {-1200, -1200, -830, -1200, -830, -250, -830, 180, -250, 180}, {-1500, -1300, -950, -500, -100, 500, -1500, -1300, -950, -500}, {-600, -600, 800, 1200, 850, 850, -500, 150, 150, 400}};

int x_range_end[6][10] = {{1875, 1800, 1000, 1000, 1000, 1875, 900, 1875}, {800, 2850, 1950, 1000, 1500, 2850, 1900, 2850, 2000},{1200, 2000, 2900, 1800, 1900, 2900, 2000, 1800, 2000, 2900}, {-850, -850, -100, -550, -150, 50, -150, 800, 50, 800}, {-1200, -900, -500, 100, 760, 1050, -1200, -900, -500, 1050}, {-550, -250, 1000, 1600, 2050, 2250, -100, 1000, 1050, 1600}};

int y_range_start[6][10] = {{1800, 1000, 700, 1000, 1500, 700, 1250, 700}, {585, 250, 1000, 1500, 1600, 1200, 500, 750, 400}, {400, 1250, 400, 1500, 1550, 950, 400, 400,1400, 400}, {-40, 550, -10, 1550, 550, -40, 1650, 450, 1200, 1550}, {400, 1290, 400, 2200, 400, 530, 1250, 2050, 1650, 1860}, {400, 1250, 3000, 600, 600, 1500, 2100, 600, 1950, 1850}};

int y_range_end[6][10] = {{1950, 1800, 1200, 1500, 1950, 1700, 1950, 1700}, {1550, 700, 2490, 2490, 2490, 2490, 1800, 2000, 2490},{900, 2500, 1200, 2550, 2500, 2000, 1200, 1450,2500,900}, {500, 1500, 500, 2300, 1600, 1150, 2300, 1500, 2300, 2300}, {1200, 2000, 1600, 2500, 1900, 1860, 2560, 2500, 2560, 2560}, {1200, 2000, 3700, 1800, 1800, 3800, 3700, 1900, 3000, 3700}};

std::unordered_set<int> used_indices;

int generate_unique_random_index(int max) {
    int tries = 0;
    int x;
    do {
        x = rand() % max;
        tries++;
    } while (used_indices.count(x) && tries < 100);
    used_indices.insert(x);
    return x;
}

void generate_random_diamond_positions(int level) {
    used_indices.clear();

    int count = max_diamonds[level];
    int valid_ranges = 0;
    for (int i = 0; i < 10; i++) {
        if (x_range_end[level][i] > x_range_start[level][i]) {
            valid_ranges++;
        }
    }

    for (int i = 0; i < count; i++) {
        int rand_index = generate_unique_random_index(valid_ranges);

        int dx = x_range_end[level][rand_index] - x_range_start[level][rand_index];
        int dy = y_range_end[level][rand_index] - y_range_start[level][rand_index];

        int pos_x = x_range_start[level][rand_index] + rand() % dx;
        int pos_y = y_range_start[level][rand_index] + rand() % dy;

        diamond_x[level][i] = pos_x;
        diamond_y[level][i] = pos_y;

        printf("Diamond %d at: x=%d y=%d (index %d)\n", i, pos_x, pos_y, rand_index);
    }
}

void loadDiamonds() {
    int level = current_lvl - 1;
    int count = max_diamonds[level];

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
    loadDiamonds();
}

#endif
