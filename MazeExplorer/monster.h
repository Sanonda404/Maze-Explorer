#ifndef MONSTERS_H
#define MONSTERS_H

#include "MazeExplorer/bat.h"
#include "MazeExplorer/fire.h"
#include "MazeExplorer/slime.h"
#include "MazeExplorer/diamonds.h"
#include "MazeExplorer/SpikeObstacle.h"
#include "MazeExplorer/RotatingObstacle.h"
#include "MazeExplorer/Explosion.h"
#include "MazeExplorer/rock.h"

void load_monsters(int level)
{
    //loadBats();
    //loadSlimes();
    loadDiamonds();
    loadSpikeObstacles(level) ;
    loadRollerObstacles( level);
    loadExplosionObstacles( level);
    loadrocks(level-1);
}

void draw_monsters(int x, int y,int level)
{
    //draw_bats(x,y);
    //drawSlimes(x,y);
    draw_rocks(x,y);
    
    draw_SpikeObstacles(x,y,level) ;
    drawRollerObstacles(x, y,  level);
    drawExplosionObstacles(x, y,  level);
    draw_diamonds(x,y);
}

void animate_monsters(int level)
{
    //bats_animate();
    //animateSlimes();
    animateRollerObstacles() ;
    animateExplosionObstacles() ;
    update_blasts();
    
}

void move_monsters(int player_x, int player_y)
{
   // moveSlimesToward(player_x, player_y);
}

void reset_monsters(int level)
{
    //reset_bats();
   // reset_slimes();
    reset_diamonds();
    reset_rocks(level-1);
}

#endif