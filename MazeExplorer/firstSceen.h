#include "iGraphics.h"
#include "MazeExplorer/VolumeSlider.h"
//#include "iFont.h"
#include "MazeExplorer/level_dependencies.h"
#include "MazeExplorer/leaderboard.h"

Image fbg, fb1, fb2, fb3, fb4;

int x = 1400/2-150;
int btn_size = 90;
int offset = 30;
int y = 400;
int btn_width = 300;

bool trnstn = false;
int trnstn_timer = 15;
int sliding_speed = 80;
int x1=0,x2=0,x3=0,x4=0;

float alpha = 0;

void fs_load_resources()
{
    iLoadImage(&fbg, "MazeExplorer/assests/bg2.jpg");
    iLoadImage(&fb1, "MazeExplorer/assests/levels/playbtn.png");
    iLoadImage(&fb2, "MazeExplorer/assests/levels/highbtn.png");
    iLoadImage(&fb3, "MazeExplorer/assests/levels/settingsbtn.png");
    iLoadImage(&fb4, "MazeExplorer/assests/levels/exitbtn.png");
}

void draw_firstPage()
{
    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glColor4f(1.0, 1.0, 1.0, 1.0);

    iShowImage(0,0,"MazeExplorer/assests/bg2.png");
    iShowImage(x+x1, y,"MazeExplorer/assests/levels/playbtn.png");//play button
    iShowImage(x+x2, y-(btn_size+offset)*1,"MazeExplorer/assests/levels/highbtn.png");//settings button
    iShowImage(x+x3, y-(btn_size+offset)*2,"MazeExplorer/assests/levels/settingsbtn.png");//highscores button
    iShowImage(x+x4, y-(btn_size+offset)*3,"MazeExplorer/assests/levels/exitbtn.png");//exit button


    if(trnstn){
        iSetTransparentColor(0,0,0,alpha);
        iFilledRectangle(0,0,1400,800);
        alpha+=0.1;
        x1+=sliding_speed;
        x2-=sliding_speed;
        x3+=sliding_speed;
        x4-=sliding_speed;
       // printf("%f\n",alpha);
    }
    //iShowText(700, 400, "Play","MazeExplorer/assests/fonts/DynaPuff-Medium.ttf", 48);
}

void play_transition()
{
    trnstn_timer --;
    if(trnstn_timer<=0){
        trnstn = false;
        x1=0;
        x2=0;
        x3=0;
        x4=0;
        if(page_no==12)transitioning=true;
    }
}

void fs_check_button_pressed(int mx, int my, int &page_no)
{
    //for play button
    if(page_no==0 && mx>=x && mx<=x+btn_width && my>=y && my<=y+300){
            if(player_name[0]=='\0'){
                page_no = 11;
                pre_page = 1;
            }
            else page_no = 1;
            trnstn = true;
    }
    //for leaderboard button
    if(page_no==0 && mx>=x && mx<=x+btn_width && my>=y-(btn_size+offset)*1 && my<=y-(btn_size+offset)*1+btn_size){
            trnstn = true;
            page_no = 12;
            player_count = load_players();               
            generate_leaderboard(current_level2);
            pre_page = 0;
    }
    //for Settings button
     if(page_no==0 && mx>=x && mx<=x+btn_width && my>=y-(btn_size+offset)*2 && my<=y-(btn_size+offset)*2+btn_size){
            trnstn = true;
            page_no=11;
            pre_page = 0;
            
    }
     //for exit button
    if(page_no==0 && mx>=x && mx<=x+btn_width && my>=y-(btn_size+offset)*3 && my<=y-(btn_size+offset)*3+btn_size){
            trnstn = true;
            exit(0);
    }
}
