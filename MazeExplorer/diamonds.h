#include "iGraphics.h"

#define diamond_no 1

typedef struct
{
    Image frames[1];
    Sprite sprite;
    int direction_x; // 1 for left, -1 for right
    int direction_y; //1 for up, 1 for down
    int is_visible = 1;
}Diamond;

Diamond diamonds[diamond_no];

int diamond_x[] = {700};
int diamond_y[] = {600};



void loadDiamonds()
{
    for(int i=0; i<diamond_no; i++){
        iLoadFramesFromSheet(diamonds[i].frames, "MazeExplorer/assests/levels/diamond.png", 1, 1);
        iInitSprite(&diamonds[i].sprite, -1);
        iChangeSpriteFrames(&diamonds[i].sprite, diamonds[i].frames, 1);

        iSetSpritePosition(&diamonds[i].sprite, diamond_x[i], diamond_y[i]);

        iScaleSprite(&diamonds[i].sprite, 0.5);
    }
    

    
}

void draw_diamonds(int x, int y)
{
    for(int i=0; i<diamond_no; i++){
        if(diamonds[i].is_visible==1){
           iShowSprite(&diamonds[i].sprite); 
            diamonds[i].sprite.x = diamond_x[i] + x;
            diamonds[i].sprite.y = diamond_y[i] + y; 
        }
       
    }
    
    
}


void reset_diamonds()
{
    for(int i=0; i<diamond_no; i++){
        diamonds[i].is_visible = 1;
        //diamond
    }
}
