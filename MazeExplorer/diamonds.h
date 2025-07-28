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

int x_range_start[6][10] = {{550, 1570, 1600, 940, 550, 1615, 1975, 1300}, {2750, 550, 580, 565, 758, 570, 1240, 1840, 2775,1210}, {1700, 1645, 880, 2380, 1615, 1900, 2200, 2650, 2410, 2390},{-1200, -1200, -830, -1200, -830, -250, -830, 180, -250, 180}, {-1500, -1300, -950, -500, -100, 500, -1500, -1300, -950, -500}, {-600, -600, 800, 1200, 850, 850, -500, 150, 150, 400}};

    int x_range_end[6][10] = {{1765, 1795, 2500, 1105, 730, 1765, 2170, 2500}, {2900, 1720, 760, 1045, 2125, 1630, 2850, 2905,2900},{1735, 2215, 1450, 2500, 1750, 2965, 2000, 2965, 2980, 2470}, {-850, -850, -100, -550, -150, 50, -150, 800, 50, 800}, {-1200, -900, -500, 100, 760, 1050, -1200, -900, -500, 1050}, {-550, -250, 1000, 1600, 2050, 2250, -100, 1000, 1050, 1600}};

int y_range_start[6][10] = {{1870, 1540, 1540, 459, 730, 490, 205, 200}, {205, 2455, 830, 1510, 1480, 2425, 1825, 2470, 1180,1870}, {350, 860, 1660, 865, 1640, 2170, 2410, 1135,400, 400}, {-40, 550, -10, 1550, 550, -40, 1650, 450, 1200, 1550}, {400, 1290, 400, 2200, 400, 530, 1250, 2050, 1650, 1860}, {400, 1250, 3000, 600, 600, 1500, 2100, 600, 1950, 1850}};

int y_range_end[6][10] = {{2020, 2020, 1660, 1675, 970, 505, 940, 345}, {985, 2575, 1330, 2260, 1630, 2590, 1945, 2590, 1950,1930},{400, 1450, 2230, 1870, 2410, 2755, 2770, 1690,1135,2050}, {500, 1500, 500, 2300, 1600, 1150, 2300, 1500, 2300, 2300}, {1200, 2000, 1600, 2500, 1900, 1860, 2560, 2500, 2560, 2560}, {1200, 2000, 3700, 1800, 1800, 3800, 3700, 1900, 3000, 3700}};

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