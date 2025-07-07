#include "iGraphics.h"
#include "MazeExplorer/level_dependencies.h"
#include<bits/stdc++.h>

#define MAX_BULLETS 4

int bx=SCREEN_WIDTH/2+50, by=SCREEN_HEIGHT/2+50;
int bullet_x[]={bx,bx,bx,bx}, bullet_y[]={by,by,by,by};

int released []={0,0,0,0};

string directions[] = {"right","right","right","right"};

int b_speed = 70;

bool attacking = false;


Image bullet_frames[1];
Sprite bullets[4];

void load_bullet() {
    iLoadFramesFromSheet(bullet_frames, "MazeExplorer/assests/player/bullet.png", 1, 1);

    for (int i = 0; i < MAX_BULLETS; i++) {
        iInitSprite(&bullets[i], -1);
        iChangeSpriteFrames(&bullets[i], bullet_frames, 1);
        iSetSpritePosition(&bullets[i], bullet_x[i], bullet_y[i]);
        iScaleSprite(&bullets[i], 0.5);
    }
}

void draw_bullet()
{
    for(int i=0; i<4; i++){
        if(released[i]==1){
            iSetSpritePosition(&bullets[i], bullet_x[i], bullet_y[i]);
            iShowSprite(&bullets[i]);
        }
    }
    
}

void shoot_bullet(string dir_name)
{
    if (attacking)
    {
        iPlaySound("MazeExplorer/assests/music/shoot.wav", false, 50);
        attacking = false;
        for(int i=0; i<4; i++){
            if(released[i]==0){
                released[i]=1;
                directions[i] = dir_name;
                break;
            }
        }
    }
}

void reset(int i)
{
    bullet_x[i] = bx;
    bullet_y[i] = by;
    released[i] = 0;
    directions[i] = "right";
}

void move_bullet()
{
    for(int i=0; i<4; i++){
        if(released[i]==1){
            if (directions[i]=="left")bullet_x[i]-=b_speed;
            if(directions[i] == "right")bullet_x[i]+=b_speed;
            if(directions[i] == "up")bullet_y[i]+=b_speed;
            if(directions[i]=="down")bullet_y[i]-=b_speed;

            if(bullet_x[i]<0 || bullet_x[i]>1600){
                reset(i);
            }
            if(bullet_y[i]<0 || bullet_y[i]>1000){
                reset(i);
            }
        }
    }
    
    
}