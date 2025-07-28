#ifndef DIAMONDS_H
#define DIAMONDS_H
#include "iGraphics.h"
#include <stdlib.h> // for rand
#include <ctime>    // for time
#include <bits/stdc++.h>

#define MAX_LEVELS 6
#define MAX_DIAMONDS 10 // max per level

extern int current_lvl;

int max_diamonds[MAX_LEVELS] = {2, 3, 5, 4, 6, 6};

typedef struct
{
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

int x_range_start[6][10] = {{2020, 580, 1660, 580}, {2800, 580, 565, 2770, 1825, 565}, {910, 880, 1915, 2890, 1900, 2920, 2200}, {310, -845, 760, 760, 775, 550, -365, -1535, -1550}, {350, -140, 625, 340, 130, -1070, -575, 145, -1570, -1325}, {685, 355, 340, -1145, -65, -1145, -740, 1765, 1390, 1060}};

int x_range_end[6][10] = {{2170, 1795, 2455, 685}, {2890, 685, 1015, 2890, 2245, 1600}, {1720, 940, 2215, 2980, 1975, 2980, 2470}, {790, -545, 820, 810, 805, 610, -335, -1490, -1490}, {430, -35, 910, 430, 205, -515, -545, 220, -1490, -950}, {754, 505, 520, -1085, -5, -890, -380, 2320, 1570, 1255}};

int y_range_start[6][10] = {{445, 1870, 1660, 1180}, {205, 865, 2110, 1180, 2470, 2455}, {385, 1600, 1390, 370, 370, 1150, 2680}, {-65, 880, 880, 880, 1585, 1990, 895, -20, 1090}, {340, 805, 1810, 1330, 1060, 1300, 295, 2320, 820, 1795}, {1540, 2140, 2920, 2320, 2155, 1165, 775, 2090, 2335, 2125}};

int y_range_end[6][10] = {{494, 1990, 1880, 1630}, {700, 1300, 2245, 1915, 2575, 2575}, {475, 2245, 1465, 925, 685, 1735, 2770}, {-5, 925, 1390, 1390, 2335, 2350, 1375, 925, 1840}, {660, 1150, 1870, 2350, 1630, 1420, 895, 2620, 1990, 1995}, {1615, 2395, 3310, 3490, 2740, 1765, 970, 2335, 2545, 2335}};

vector<int> random_nums;

//
bool check_exists(int n)
{
    for (int i = 0; i < random_nums.size(); i++)
    {
        if (random_nums[i] == n)
            return true;
    }
    return false;
}

int generate_random_number(int n)
{
    int x = rand() % n;
    while (check_exists(x))
    {
        x = rand() % n;
    }
    random_nums.push_back(x);
    return x;
}

void generate_random_diamond_positions(int level)
{
    int count = max_diamonds[level];
    int range = 0;
    for (int i = 0; i < 10; i++)
    {
        if (x_range_end[level][i] > x_range_start[level][i])
            range++;
    }
    for (int i = 0; i < count; i++)
    {
        int x = generate_random_number(range);
        int d_x = (x_range_end[level][x] - x_range_start[level][x]);
        int pos_x = x_range_start[level][x] + (rand() % d_x);
        int d_y = (y_range_end[level][x] - y_range_start[level][x]);
        int pos_y = y_range_start[level][x] + (rand() % d_y);
        diamond_x[level][i] = pos_x;
        diamond_y[level][i] = pos_y;
        printf("Diamond pos %d %d %d\n", diamond_x[level][i], diamond_y[level][i], x);
    }
    random_nums.clear();
}

void loadDiamonds()
{
    int level = current_lvl - 1;
    int count = max_diamonds[level];

    for (int i = 0; i < count; i++)
    {
        iLoadFramesFromSheet(diamonds[i].frames, "MazeExplorer/assests/levels/diamond.png", 1, 1);
        iInitSprite(&diamonds[i].sprite);
        iChangeSpriteFrames(&diamonds[i].sprite, diamonds[i].frames, 1);

        iSetSpritePosition(&diamonds[i].sprite, diamond_x[level][i], diamond_y[level][i]);
        iScaleSprite(&diamonds[i].sprite, 0.5);
        diamonds[i].is_visible = 1;
    }
}

void draw_diamonds(int cam_x, int cam_y)
{
    int level = current_lvl - 1;
    int count = max_diamonds[level];

    for (int i = 0; i < count; i++)
    {
        if (diamonds[i].is_visible)
        {
            diamonds[i].sprite.x = diamond_x[level][i] + cam_x;
            diamonds[i].sprite.y = diamond_y[level][i] + cam_y;
            iShowSprite(&diamonds[i].sprite);
        }
    }
}

void reset_diamonds()
{
    int level = current_lvl - 1;
    int count = max_diamonds[level];
    for (int i = 0; i < count; i++)
    {
        diamonds[i].is_visible = 1;
    }
    loadDiamonds();
}

#endif