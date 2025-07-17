#include "iGraphics.h"
#include "MazeExplorer/level_dependencies.h"
#include "MazeExplorer/firstSceen.h"
#include "MazeExplorer/menu.h"
#include "MazeExplorer/level1.h"
#include "MazeExplorer/level2.h"
#include "MazeExplorer/level3.h"
#include "MazeExplorer/level4.h"
#include "MazeExplorer/level5.h"
#include "MazeExplorer/level6.h"


void load_resources()
{
    load_settings();
    fs_load_resources();
    menu_load_resources();
    load_level_resources();
    lvl1_load_resources();
    lvl2_load_resources();
    lvl3_load_resources();
    lvl4_load_resources();
    lvl5_load_resources();
    lvl6_load_resources();
}



/*
function iDraw() is called again and again by the system.
*/
void iDraw()
{
    // place your drawing codes here
    iClear();

    //drawVolumeSlider();

    if(page_no == 0 || trnstn){
        draw_firstPage();
    }
    else if(page_no == 1 || menu_trnstn){
        draw_menu();
    }
    else if(page_no==2){
        draw_lvl1();
    }
    else if(page_no==3){
        draw_lvl2();
    }
    else if(page_no==4){
        draw_lvl3();
    }
    else if(page_no==5){
        draw_lvl4();
    }
    else if(page_no==6){
        draw_lvl5();
    }
     else if(page_no==7){
        draw_lvl6();
    }
    //settings page
    else if (page_no==10){
        drawVolumeSlider();
    }

    if(!trnstn && !menu_trnstn && page_no>=2 && page_no<=7){
        draw_levels();
    }

    check_collision1();
    check_collision2();
    check_collision3();
    check_collision4();
    check_collision5();
    check_collision6();
}


void animate()
{
    if(trnstn)play_transition();

    if(menu_trnstn)menu_play_transition();

    animate_levels();
}

/*
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    // place your codes here
    if(page_no==10){
        volumeSliderMouseMove(mx, my);
    }
}

/*
function iMouseDrag() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseDrag(int mx, int my)
{
    if(page_no==10)isDragging = true;
    else isDragging = false;
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    //means clicked
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
       if(page_no==0)fs_check_button_pressed(mx, my, page_no);
       else if(page_no==1)menu_check_button_pressed(mx, my, page_no);
       else if(page_no>=2 && page_no<=7){
        check_paused_pressed(mx,my);
        check_lvl_completed_buttons(mx,my, page_no);
        check_pause_buttons(mx,my, page_no);
        check_lost_buttons(mx,my,page_no);
       }
       if(page_no==10){
        music_volume = check_ok_pressed(volume, mx, my, page_no, pre_page);
       }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
    }
}

/*
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    init_sound();
    play_sound("bgm");
    
    load_resources();

    iSetTimer(20, animate);    
    // place your own initialization codes here.
    
    iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Explorer");

    return 0;
}
