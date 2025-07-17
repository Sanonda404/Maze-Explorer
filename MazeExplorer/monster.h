#ifndef MONSTERS_H
#define MONSTERS_H

#include "MazeExplorer/bat.h"
#include "MazeExplorer/fire.h"
#include "MazeExplorer/slime.h"
#include "MazeExplorer/diamonds.h"

void load_monsters()
{
    loadBats();
    loadfires();
    loadSlimes();
    loadDiamonds();
}

void draw_monsters(int x, int y)
{
    draw_bats(x,y);
    draw_fires(x,y);
    drawSlimes(x,y);
    draw_diamonds(x,y);
}

void animate_monsters()
{
    bats_animate();
    fires_animate();
    animateSlimes();
}

void move_monsters(int player_x, int player_y)
{
    moveSlimesToward(player_x, player_y);
}

void reset_monsters()
{
    reset_bats();
    reset_slimes();
    reset_diamonds();
}

#endif