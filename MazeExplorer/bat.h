#include "iGraphics.h"


#define bat_no  2

typedef struct
{
    Image frames[4];
    Sprite sprite;
    int direction_x; // 1 for left, -1 for right
    int direction_y; //1 for up, 1 for down
    int is_alive = 1;
}Bat;

Bat bats[bat_no];

int bat_x[] = {700,500};
int bat_y[] = {600,400};



void loadBats()
{
    for(int i=0; i<bat_no; i++){
        iLoadFramesFromSheet(bats[i].frames, "MazeExplorer/assests/monsters/bat.png", 1, 4);
        iInitSprite(&bats[i].sprite, -1);
        iChangeSpriteFrames(&bats[i].sprite, bats[i].frames, 4);

        iSetSpritePosition(&bats[i].sprite, bat_x[i], bat_y[i]);

        iScaleSprite(&bats[i].sprite, 3);
        bats[i].direction_x = 1; // 1 for right, -1 for left, 0 for up and down
        bats[i].direction_y = 0; // 1 for up, -1 for down, 0 for left and right
    }
    

    
}

void draw_bats(int x, int y)
{
    for(int i=0; i<bat_no; i++){
        if(bats[i].is_alive==1){
           iShowSprite(&bats[i].sprite); 
            bats[i].sprite.x = bat_x[i] + x;
            bats[i].sprite.y = bat_y[i] + y; 
        }
       
    }
    
    
}


void bats_animate()
{
    for(int i=0; i<bat_no; i++){
       iAnimateSprite(&bats[i].sprite); 
    }
    
}

void reset_bats()
{
    for(int i=0; i<bat_no; i++){
        bats[i].is_alive = 1;
        //bat
    }
}
