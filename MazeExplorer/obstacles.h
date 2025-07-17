#ifndef OBSTACLES_H
#define OBSTACLES_H
#include "MazeExplorer/fire.h"

void load_obstacles()
{
    loadfires();
}

void draw_obstacles(int x, int y)
{
    draw_fires(x,y);
}

void animate_monsters()
{
    fires_animate();
}

#endif