#include "iGraphics.h"

Image b1,b2,b3,b4,b5,b6;


void menu_load_resources()
{
    iLoadImage(&b1, "MazeExplorer/assests/button1.png");
    iLoadImage(&b2, "MazeExplorer/assests/button1.png");
    iLoadImage(&b3, "MazeExplorer/assests/button1.png");
    iLoadImage(&b4, "MazeExplorer/assests/button1.png");
    iLoadImage(&b5, "MazeExplorer/assests/button1.png");
    iLoadImage(&b6, "MazeExplorer/assests/button1.png");
}

void draw_menu()
{
    iShowImage(700, 700,"MazeExplorer/assests/button1.png");//lvl 1
    iShowImage(700, 600,"MazeExplorer/assests/button1.png");//lvl 2
    iShowImage(700, 500,"MazeExplorer/assests/button1.png");//lvl 3
    iShowImage(700, 400,"MazeExplorer/assests/button1.png");//lvl 4
    iShowImage(700, 300,"MazeExplorer/assests/button1.png");//lvl 5
    iShowImage(700, 200,"MazeExplorer/assests/button1.png");//lvl 6

    iText(760,720,"Level 1",GLUT_BITMAP_TIMES_ROMAN_24 );
    iText(760,620,"Level 2",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(760,520,"Level 3",GLUT_BITMAP_TIMES_ROMAN_24 );
    iText(760,420,"Level 4",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(760,320,"Level 5",GLUT_BITMAP_TIMES_ROMAN_24 );
    iText(760,220,"Level 6",GLUT_BITMAP_TIMES_ROMAN_24);
}


void menu_check_button_pressed(int mx, int my, int &page_no)
{
    //for level 1
    if(mx>=710 && mx<=865 && my>=710 && my<=760){
            printf("Level 1\n");
            page_no = 2;
    }
}
