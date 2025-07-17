#include "iGraphics.h"
#include "MazeExplorer/level_dependencies.h"

Image lvl_map;

int c_x[] = {125,370,605,860,1113,1151};
int c_y[] = {218,440,200,330,500,130};

int radius = 125;

int menu_trnstn_timer = 25;
int r = 0;
int index;

bool menu_trnstn = false;

void menu_load_resources()
{
    iLoadImage(&lvl_map, "MazeExplorer/assests/levels/levelmap.png");
}

void draw_menu()
{
    iShowImage(0,0,"MazeExplorer/assests/levels/levelmap.png");

    if(menu_trnstn){
        iSetColor(0,0,0);
        iFilledCircle(c_x[index],c_y[index],r,100);
    }
}

int menu_clac_dis(int x1, int x2, int y1, int y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void menu_play_transition()
{
    menu_trnstn_timer--;
    if(menu_trnstn_timer<=0)menu_trnstn = false;

    r+=60;
}

void menu_check_button_pressed(int mx, int my, int &page_no)
{
    printf("mm %d %d\n",mx,my);
    //for level 1
    if(menu_clac_dis(c_x[0],mx,c_y[0],my)<=radius){
            printf("Level 1\n");
            menu_trnstn = true;
            index = 0;
            page_no = 2;
            current_lvl = 1;
    }
    //for level 2
    else if(menu_clac_dis(c_x[1],mx,c_y[1],my)<=radius){
            printf("Level 2\n");
            menu_trnstn = true;
            index = 1;
            page_no = 3;
            current_lvl = 2;
    }
    //for level 3
    else if(menu_clac_dis(c_x[2],mx,c_y[2],my)<=radius){
            printf("Level 3\n");
            menu_trnstn = true;
            index = 2;
            page_no = 4;
            current_lvl = 3;
    }
    //for level 4
    else if(menu_clac_dis(c_x[3],mx,c_y[3],my)<=radius){
            printf("Level 4\n");
            menu_trnstn = true;
            index = 3;
            page_no = 5;
            current_lvl = 4;
    }
    //for level 5
    else if(menu_clac_dis(c_x[4],mx,c_y[4],my)<=radius){
            printf("Level 5\n");
            menu_trnstn = true;
            index = 4;
            page_no = 6;
            current_lvl = 5;
    }
    //for level 6
    else if(menu_clac_dis(c_x[5],mx,c_y[5],my)<=radius){
            printf("Level 6\n");
            menu_trnstn = true;
            index = 5;
            page_no = 7;
            current_lvl = 6;
    }
}
