#include "MazeExplorer/bat.h"
#include "MazeExplorer/fire.h"
#include "MazeExplorer/slime.h"

void load_monsters()
{
    loadBats();
    loadfires();
    loadSlimes();
}

void draw_monsters(int x, int y)
{
    draw_bats(x,y);
    draw_fires(x,y);
    drawSlimes(x,y);
}

void animate_monsters()
{
    bats_animate();
    fires_animate();
    animateSlimes();
}

void reset_monsters()
{
    reset_bats();
    reset_slimes();
}