#ifndef ROCK_H
#define ROCK_H

#include "iGraphics.h"
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unordered_set>
#include "MazeExplorer/level_dependencies.h"

#define MAX_LEVELS 6
#define MAX_ROCKS 20
#define MAX_BLASTS 12
#define BLAST_FRAME_COUNT 8

int max_rocks[MAX_LEVELS] = {8, 16, 9, 11, 12, 12};
int x_strts[6] = {450,450,530,-1550,-1600,-1150};
int x_ends[6] = {2200,2800,2800,800,900,2300};
int y_strts[6] = {160,160,350,0,50,300};
int y_ends[6] = {1950,2500,2700,2350,2600,4000};

typedef struct {
    Image frames[1];
    Sprite sprite;
    int is_visible;
} Rocks;

typedef struct {
    Image frames[BLAST_FRAME_COUNT];
    Sprite sprite;
    int is_playing;
    int current_frame;
    int pos_x;
    int pos_y;
} Blast;

Rocks rocks[MAX_ROCKS];
Blast blasts[MAX_BLASTS];

int rocks_x[MAX_LEVELS][MAX_ROCKS] = {0};
int rocks_y[MAX_LEVELS][MAX_ROCKS] = {0};

std::unordered_set<int> used_indices2;

// Range arrays
int rock_x_range_start[6][10] = {
    {1975, 570, 550}, 
    {640, 2750, 1915}, 
    {1100, 1650, 2800, 2010, 650}, 
    {370, 650, -1250, -1350}, 
    {-640, 25, -995, -700, -1200,-85 }, 
    {700, -700, -400, 700, 50, 850}
};

int rock_x_range_end[6][10] = {
    {2175, 1780, 715}, 
    {670, 2850, 1950}, 
    {1150, 1700, 3000, 2200, 700}, 
    {500, 750, -1100, -1200}, 
    {-500, 50, -850, 800,160, -100}, 
    {710, -600, -500, 600, 100, 900}
};

int rock_y_range_start[6][10] = {
    {600, 2000, 1570}, 
    {1585, 250, 2400}, 
    {400, 1200, 2000, 2390, 1000}, 
    {20, 910, 100, 990}, 
    {1125, 290, 2500, 2200, 1200, 1530}, 
    {400, 3000, 1900, 1000, 2100, 1000}
};

int rock_y_range_end[6][10] = {
    {970, 1800, 1675}, 
    {1620, 1000, 2490}, 
    {800, 1400, 2100, 2520, 1200}, 
    {60, 930, 200, 1100}, 
    {1150, 300, 2600, 2300, 1600, 1660}, 
    {500, 3200, 2100, 1300, 2500, 1200}
};

int generate_unique_random_index2(int max) {
    int tries = 0, x;
    do {
        x = rand() % max;
        tries++;
    } while (used_indices2.count(x) && tries < 100);
    used_indices2.insert(x);
    return x;
}

void generate_random_rocks_positions(int level) {
    int count = max_rocks[level];

    for (int i = 0; i < count; i++) {
        int dx = x_ends[level]-x_strts[level];
        int dy = y_ends[level] - y_strts[level];
        int pos_x = rand() % dx+x_strts[level];
        int pos_y = rand() % dy+y_strts[level];

        while(dx>=700 && dx<=800)pos_x = rand()%dx+x_strts[level];
        while(dy>=500 && dy<=600)pos_y = rand()%dy+y_strts[level];

        rocks_x[level][i] = pos_x;
        rocks_y[level][i] = pos_y;

        printf("rocks %d at: x=%d y=%d (index %d)\n", i, pos_x, pos_y);
    }
}


void update_blasts() {
    for (int i = 0; i < MAX_BLASTS; i++) {
        if (blasts[i].is_playing) {
            iAnimateSprite(&blasts[i].sprite);
            blasts[i].current_frame++;
            if (blasts[i].current_frame >= BLAST_FRAME_COUNT) {
                blasts[i].is_playing = 0;
                blasts[i].current_frame = 0;
            }
        }
    }
}


void loadrocks(int level) {
    int count = max_rocks[level];

    generate_random_rocks_positions(level);

    for (int i = 0; i < count; i++) {
        iLoadFramesFromSheet(rocks[i].frames, "MazeExplorer/assests/obstacles/rock.png", 1, 1);
        iInitSprite(&rocks[i].sprite);
        iChangeSpriteFrames(&rocks[i].sprite, rocks[i].frames, 1);
        iSetSpritePosition(&rocks[i].sprite, rocks_x[level][i], rocks_y[level][i]);
        iScaleSprite(&rocks[i].sprite, 1.5);
        rocks[i].is_visible = 1;
        iLoadFramesFromSheet(blasts[i].frames, "MazeExplorer/assests/obstacles/blast.png", 8, 1);
        iInitSprite(&blasts[i].sprite);
        iChangeSpriteFrames(&blasts[i].sprite, blasts[i].frames, 8);
        iSetSpritePosition(&blasts[i].sprite, rocks_x[level][i], rocks_y[level][i]);
        iScaleSprite(&blasts[i].sprite, 2.5);
        blasts[i].is_playing = 0;
    }
}

void draw_rocks(int cam_x, int cam_y) {
    int level = current_lvl - 1;
    int count = max_rocks[level];

    for (int i = 0; i < count; i++) {
        if (rocks[i].is_visible) {
            rocks[i].sprite.x = rocks_x[level][i] + cam_x;
            rocks[i].sprite.y = rocks_y[level][i] + cam_y;
            iShowSprite(&rocks[i].sprite);
        }
    }
    for (int i = 0; i < count; i++) {
        if (blasts[i].is_playing) {
            blasts[i].sprite.x = rocks[i].sprite.x;
            blasts[i].sprite.y = rocks[i].sprite.y;
            iShowSprite(&blasts[i].sprite);
        }
    }

}

void destroy_rock(int index) {
    if (index >= 0 && index < MAX_ROCKS && rocks[index].is_visible) {
        rocks[index].is_visible = 0;
        blasts[index].is_playing=1;
    }
}

void reset_rocks(int level) {
    int count = max_rocks[level];
    for (int i = 0; i < count; i++) {
        rocks[i].is_visible = 1;
    }
    loadrocks(level);
}

#endif
