#ifndef LEVEL_DEPENDENCIES_H
#define LEVEL_DEPENDENCIES_H

#include "iGraphics.h"
#include "MazeExplorer/player.h"
#include "MazeExplorer/monster.h"
#include "time.h"
#include "MazeExplorer/obstacles.h"

int SCREEN_WIDTH = 1400, SCREEN_HEIGHT = 800;

int pre_page = 0;
int page_no = 0;
int t = 0;

Image bg, exitframes[1], paused_img, pause_option, lvl_comp, lost, help;

int current_lvl = 1;

bool help_showed = true;

void load_level_resources()
{
    //background
    iLoadImage(&bg, "MazeExplorer/assests/levels/bg1.png");
    iScaleImage(&bg, 3.0);

    //paused
    iLoadImage(&paused_img, "MazeExplorer/assests/levels/pause_button.png");
    iLoadImage(&pause_option, "MazeExplorer/assests/levels/paused.png");

    //help
    iLoadImage(&help, "MazeExplorer/assests/levels/help.png");

    //lvl_completed
    iLoadImage(&lvl_comp, "MazeExplorer/assests/levels/lvl_completed.png");

    //lost
    iLoadImage(&lost, "MazeExplorer/assests/levels/lost.png");

    loadPlayer();
    load_monsters();
    load_obstacles();

}

void draw_levels()
{
    draw_player();
    draw_monsters((player_x-player_relative_x), (player_y-player_relative_y));
    draw_obstacles((player_x-player_relative_x), (player_y-player_relative_y));

    display_time();
    //pause button
    iShowImage(SCREEN_WIDTH-100,SCREEN_HEIGHT-100, "MazeExplorer/assests/levels/pause_button.png");
    if(paused && !lvl_completed)iShowImage(SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-200, "MazeExplorer/assests/levels/paused.png");

    //help
    if(help_showed)
    iShowImage(SCREEN_WIDTH-900,SCREEN_HEIGHT-700, "MazeExplorer/assests/levels/help.png");

    if(lvl_completed){
        iShowImage(SCREEN_WIDTH/2-200,SCREEN_HEIGHT/2-200,"MazeExplorer/assests/levels/lvl_completed.png");
        display_highscore(700,500);
    }

    if(!is_alive){
        iShowImage(SCREEN_WIDTH/2-200,SCREEN_HEIGHT/2-200,"MazeExplorer/assests/levels/lost.png");
    }
}

void reload()
{
    player_relative_x = player_x;
    player_relative_y = player_y;
    paused = false;
    health = 100;
    health_bar_width = 200;
    is_alive = true;
    time_passed = 0;
    help_showed = true;
    lvl_completed = false;
    started = false;

    reset_monsters();
}

void next_level()
{
    current_lvl+=1;
    page_no+=1;
    reload();
}

void level_completed()
{
    if(lvl_completed)return;
    lvl_completed = true;
    calc_score(time_passed, health);
    play_sound("won");
    loadHighScore();
    
}

void check_help_buttons(int mx, int my)
{
    if(!help_showed)return;
    if(mx>=SCREEN_WIDTH/2 && mx<=SCREEN_WIDTH/2+100 && my>=130 && my<=180){
        if(!started)started = true;
        help_showed = false;
    }
}

bool check_paused_pressed(int mx, int my)
{
    printf("Mouse pos %d %d\n",mx,my);
    printf("Player pos %d %d\n",player_relative_x, player_relative_y);
    check_help_buttons(mx,my);
    if(mx>=SCREEN_WIDTH-100 && mx<=SCREEN_WIDTH-30 && my>=SCREEN_HEIGHT-100 && my<=SCREEN_HEIGHT-30){
        paused=!paused;
        return true;
    }
    return false;
}

void check_lvl_completed_buttons(int mx, int my, int &page_no)
{
    if(!lvl_completed)return;
    if(lvl_completed)printf("lvls");
    if(mx>=SCREEN_WIDTH/2-120 && mx<=SCREEN_WIDTH/2+120 && my>=SCREEN_HEIGHT/2-50 && my<=SCREEN_HEIGHT/2){
        printf("next lvl");
        next_level();
    }
    //exit
    else if(mx>=SCREEN_WIDTH/2-120 && mx<=SCREEN_WIDTH/2+120 && my>=SCREEN_HEIGHT/2-140 && my<=SCREEN_HEIGHT/2-90){
        exit(0);
    }
}

void check_lost_buttons(int mx, int my, int &page_no)
{
    if(is_alive)return;
    if(mx>=SCREEN_WIDTH/2-120 && mx<=SCREEN_WIDTH/2+120 && my>=SCREEN_HEIGHT/2-50 && my<=SCREEN_HEIGHT/2){
        printf("next lvl");
        reload();
    }
    //exit
    else if(mx>=SCREEN_WIDTH/2-120 && mx<=SCREEN_WIDTH/2+120 && my>=SCREEN_HEIGHT/2-140 && my<=SCREEN_HEIGHT/2-90){
        exit(0);
    }
}

void check_pause_buttons(int mx, int my, int &page_no)
{
    if(!paused)return;
    if(lvl_completed)printf("lvls");
    //play
    if(mx>=SCREEN_WIDTH/2-10 && mx<=SCREEN_WIDTH/2+130 && my>=SCREEN_HEIGHT/2+120 && my<=SCREEN_HEIGHT/2+170){
        paused = false;
        printf("play");
    }
    //retry
    else if(mx>=SCREEN_WIDTH/2-10 && mx<=SCREEN_WIDTH/2+130 && my>=SCREEN_HEIGHT/2+50 && my<=SCREEN_HEIGHT/2+100){
        reload();
        printf("retry");
    }
    //help
    else if(mx>=SCREEN_WIDTH/2-10 && mx<=SCREEN_WIDTH/2+130 && my>=SCREEN_HEIGHT/2-20 && my<=SCREEN_HEIGHT/2+30){
        printf("help");
    }
    //Settings
    else if(mx>=SCREEN_WIDTH/2-10 && mx<=SCREEN_WIDTH/2+130 && my>=SCREEN_HEIGHT/2-100 && my<=SCREEN_HEIGHT/2-50){
        printf("Settings");
        pre_page = page_no;
        page_no=10;
    }
    //exit
    else if(mx>=SCREEN_WIDTH/2-10 && mx<=SCREEN_WIDTH/2+130 && my>=SCREEN_HEIGHT/2-170 && my<=SCREEN_HEIGHT/2-120){
        exit(0);
    }
}

void animate_levels()
{
    t++;

    animate_monsters();
    animate_obstacles();

    if(t%1==0){
        player_animate();
    }

    if (is_hurting)hurt_timer--;
    if(hurt_timer==0){
        hurt_timer = max_hurt_time;
        is_hurting = false;
    }

    if(!lvl_completed && is_alive && !paused && started){
        update_time();
        move_monsters(player_relative_x, player_relative_y);
    }
}



#endif
