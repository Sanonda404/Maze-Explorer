#ifndef DIAMONDS_H
#define DIAMONDS_H
#include "iGraphics.h"
#include <stdlib.h> // for rand
#include <ctime>   // for time
#include <bits/stdc++.h>

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
int diamond_x[MAX_LEVELS][MAX_DIAMONDS] = {0};
int diamond_y[MAX_LEVELS][MAX_DIAMONDS] = {0};

int x_range_start[6][10] = {
    {1975, 570, 550}, 
    {640, 2750, 1915}, 
    {1100, 1650, 2800, 2010, 650}, 
    {370, 650, -1250, -1350}, 
    {-640, 25, -995, -700, -1200,-85 }, 
    {700, -700, -400, 700, 50, 850}
};

int x_range_end[6][10] = {
    {2175, 1780, 715}, 
    {670, 2850, 1950}, 
    {1150, 1700, 3000, 2200, 700}, 
    {500, 750, -1100, -1200}, 
    {-500, 50, -850, 800,160, -100}, 
    {710, -600, -500, 600, 100, 900}
};

int y_range_start[6][10] = {
    {600, 1850, 1570}, 
    {1585, 250, 2400}, 
    {400, 1200, 2000, 2390, 1000}, 
    {20, 910, 100, 990}, 
    {1125, 290, 2500, 2200, 1200, 1530}, 
    {400, 3000, 1900, 1000, 2100, 1000}
};

int y_range_end[6][10] = {
    {970, 2000, 1675}, 
    {1620, 1000, 2490}, 
    {800, 1400, 2100, 2520, 1200}, 
    {60, 930, 200, 1100}, 
    {1150, 300, 2600, 2300, 1600, 1660}, 
    {500, 3200, 2100, 1300, 2500, 1200}
};


vector<int> random_nums;

//
bool check_exists(int n){
    for(int i=0; i<random_nums.size(); i++){
        if(random_nums[i]==n)return true;
    }
    return false;
}

int generate_random_number(int n){
    int x = rand()%n;
    while(check_exists(x)){
        x=rand()%n;
    }
    random_nums.push_back(x);
    return x;
}

void generate_random_diamond_positions(int level) {
    int count = max_diamonds[level];
    int range = 0;
    for (int i = 0; i < 10; i++) {
    if (x_range_end[level][i] > x_range_start[level][i])
        range++;
    }
    for(int i=0; i<count; i++){
       int x = generate_random_number(range);
        int d_x = (x_range_end[level][x]-x_range_start[level][x]);
        int pos_x = x_range_start[level][x] + (rand()% d_x);
        int d_y = (y_range_end[level][x]-y_range_start[level][x]);
        int pos_y = y_range_start[level][x] + (rand()% d_y);
        diamond_x[level][i] = pos_x;
        diamond_y[level][i] = pos_y;
        printf("Diamond pos %d %d %d\n",diamond_x[level][i],diamond_y[level][i],x);
    }
    random_nums.clear();
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
