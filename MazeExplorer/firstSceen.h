#include "iGraphics.h"
#include "MazeExplorer/VolumeSlider.h"
//#include "iFont.h"
//#include "MazeExplorer/level_dependencies.h"

Image fbg, fb1, fb2;



void fs_load_resources()
{
    iLoadImage(&fbg, "MazeExplorer/assests/bg.jpg");
    iLoadImage(&fb1, "MazeExplorer/assests/levels/button1.png");
}

void draw_firstPage()
{
    iShowImage(0,0,"MazeExplorer/assests/bg.png");
    iShowImage(1400/2-150, 400,"MazeExplorer/assests/levels/button1.png");//play button
    iShowImage(1400/2-150, 280,"MazeExplorer/assests/levels/button1.png");//settings button
    iShowImage(1400/2-150, 160,"MazeExplorer/assests/levels/button1.png");//exit button

    iSetColor(0,0,0);
    //iShowText(700, 400, "Play","MazeExplorer/assests/fonts/DynaPuff-Medium.ttf", 48);
    iText(650,450,"Play",GLUT_BITMAP_TIMES_ROMAN_24 );
    iText(640,330,"Settings",GLUT_BITMAP_TIMES_ROMAN_24 );
    iText(650,210,"Exit",GLUT_BITMAP_TIMES_ROMAN_24);
}


void fs_check_button_pressed(int mx, int my, int &page_no)
{
    printf("%d %d\n",mx,my);
    //for play button
    if(page_no==0 && mx>=560 && mx<=780 && my>=420 && my<=490){
            //printf("Play");
            page_no = 1;
    }

    if(page_no==0 && mx>=560 && mx<=780 && my>=290 && my<=370){
            //printf("Play");
           page_no = 10;
    }
     //for exit button
    if(page_no==0 && mx>=560 && mx<=780 && my>=170 && my<=250){
            printf("Exit");
            //exit(0);
    }
}
