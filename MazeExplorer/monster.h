#ifndef MONSTERS_H
#define MONSTERS_H

#include "MazeExplorer/bat.h"
#include "MazeExplorer/fire.h"
#include "MazeExplorer/slime.h"
#include "MazeExplorer/diamonds.h"
#include "MazeExplorer/SpikeObstacle.h"
#include "MazeExplorer/RotatingObstacle.h"
#include "MazeExplorer/Explosion.h"

void load_monsters(int level)
{
    loadBats();
    loadSlimes();
    loadDiamonds();
    loadSpikeObstacles(level) ;
    loadRollerObstacles( level);
    loadExplosionObstacles( level);
}

void draw_monsters(int x, int y,int level)
{
    draw_bats(x,y);
    drawSlimes(x,y);
    draw_diamonds(x,y);
    draw_SpikeObstacles(x,y,level) ;
    drawRollerObstacles(x, y,  level);
    drawExplosionObstacles(x, y,  level);
}

void animate_monsters(int level)
{
    bats_animate();
    animateSlimes();
    animateRollerObstacles() ;
    animateExplosionObstacles() ;
    
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