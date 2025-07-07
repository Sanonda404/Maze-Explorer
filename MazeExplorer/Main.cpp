#include "iGraphics.h"
#include "iSound.h"
#include "MazeExplorer/firstSceen.h"
#include "MazeExplorer/menu.h"
#include "level1.h"
#include "VolumeSlider.h"


int page_no = 0;
float music_volume = 1;

void load_resources()
{
    load_settings();
    fs_load_resources();
    menu_load_resources();
    lvl_load_resources();
}



/*
function iDraw() is called again and again by the system.
*/
void iDraw()
{
    // place your drawing codes here
    iClear();

    //drawVolumeSlider();

    if(page_no == 0){
        draw_firstPage();
    }
    else if(page_no == 1){
        draw_menu();
    }
    else if(page_no==2){
        draw_lvl1();
    }
    //settings page
    else if (page_no==10){
        drawVolumeSlider();
    }

    check_collision();
    
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
       else if(page_no==2){
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
    iInitializeSound();
    iPlaySound("MazeExplorer/assests/music/bgm.wav", true, music_volume*100);
    
    load_resources();

    iSetTimer(50, animate);    
    // place your own initialization codes here.
    
    iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Explorer");

    return 0;
}
