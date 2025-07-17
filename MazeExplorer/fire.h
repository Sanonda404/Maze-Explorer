#ifndef FIRE_H
#define FIRE_H
#include "iGraphics.h"


#define fire_no  4

typedef struct
{
    Image frames[8];
    Sprite sprite;
    int direction_x; // 1 for left, -1 for right
    int direction_y; //1 for up, 1 for down
}Fire;

Fire fires[fire_no];

int fire_x[] = {1145,1865, 2285, 2585};
int fire_y[] = {500,770, 1070, 1510};



void loadfires()
{
    for(int i=0; i<fire_no; i++){
        iLoadFramesFromSheet(fires[i].frames, "MazeExplorer/assests/obstacles/fire4_blue_glowing.png", 1, 8);
        iInitSprite(&fires[i].sprite, -1);
        iChangeSpriteFrames(&fires[i].sprite, fires[i].frames, 8);

        iSetSpritePosition(&fires[i].sprite, fire_x[i], fire_y[i]);

        iScaleSprite(&fires[i].sprite, 3);
        fires[i].direction_x = 1; // 1 for right, -1 for left, 0 for up and down
        fires[i].direction_y = 0; // 1 for up, -1 for down, 0 for left and right
    }
    
}

void draw_fires(int x, int y)
{
    for(int i=0; i<fire_no; i++){
        iShowSprite(&fires[i].sprite); 
        fires[i].sprite.x = fire_x[i] + x;
        fires[i].sprite.y = fire_y[i] + y; 
       
    }
    
    
}


void fires_animate()
{
    for(int i=0; i<fire_no; i++){
       iAnimateSprite(&fires[i].sprite); 
    }
    
}

#endif
