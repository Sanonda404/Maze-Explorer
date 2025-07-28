#ifndef LEVEL_DEPENDENCIES_H
#define LEVEL_DEPENDENCIES_H

#include "iGraphics.h"
#include "MazeExplorer/player.h"
#include "MazeExplorer/monster.h"
#include "time.h"
#include "MazeExplorer/obstacles.h"
#include "MazeExplorer/leaderboard.h"
#include "MazeExplorer/level_completed.h"

int SCREEN_WIDTH = 1400, SCREEN_HEIGHT = 800;

int pre_page = 0;
int page_no = 0;
int t = 0;

int max_lvl = 1;

char player_name[100];

Image bg, exitframes[1], paused_img, pause_option, lvl_comp, lost, help;

bool help_showed = true;

char err[100] = "Collect diamonds to enter exit";

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
    load_monsters(current_lvl);
    load_obstacles();

}

void show_error(char err_msg[]){
    iShowText(50,50,err_msg,"MazeExplorer/assests/fonts/Roboto-Bold.ttf",30);
    error_timer--;
    if(error_timer<=0)error_showing = false;
}

void draw_levels()
{
    draw_player();

    draw_monsters((player_x-player_relative_x), (player_y-player_relative_y), current_lvl);

    draw_obstacles((player_x-player_relative_x), (player_y-player_relative_y));

    display_time();

    draw_bars();

    iSetColor(255,255,255);
    char lvl_txt[20];
    sprintf(lvl_txt,"Level %d",current_lvl);
    iShowText(610, 730, lvl_txt, "MazeExplorer/assests/fonts/DynaPuff-Medium.ttf", 50);
    //pause button
    iShowImage(SCREEN_WIDTH-100,SCREEN_HEIGHT-100, "MazeExplorer/assests/levels/pause_button.png");
    if(paused && !lvl_completed)iShowImage(SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-200, "MazeExplorer/assests/levels/paused.png");

    //help
    if(help_showed)
    iShowImage(SCREEN_WIDTH-900,SCREEN_HEIGHT-700, "MazeExplorer/assests/levels/help.png");

    if(lvl_completed){
        draw_level_complete_screen();
    }
    if(!is_alive){
        iShowImage(SCREEN_WIDTH/2-200,SCREEN_HEIGHT/2-200,"MazeExplorer/assests/levels/lost.png");
    }

    if(error_showing)show_error(err);
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
    diamond_collected = 0;
    diamond_bar_width = 0;

    loadPlayer();
    loadDiamonds();


    reset_monsters(current_lvl);
}

void next_level()
{
    generate_random_diamond_positions(current_lvl);
    loadrocks(current_lvl);
    current_lvl+=1;
    page_no+=1;
    reload();
    max_lvl = max(max_lvl,current_lvl);
}

void level_completed()
{
    if(lvl_completed)return;
    lvl_completed = true;
    max_lvl = max(max_lvl,current_lvl+1);
    calc_score(time_passed, health, current_lvl, player_name);
    printf("won %s %d %d\n",player_name,score[current_lvl-1],highscore);
    play_sound("won");
    start_level_complete_screen(score[current_lvl-1],highscore,current_lvl);
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
    int idx = level_complete_mouse_click(mx,my);
    if(idx==-1)return;
    if(idx==0){
        printf("next lvl");
        next_level();
    }
    //highscores
    else if(idx==2){
        pre_page = page_no;
        printf("Highscores");
        page_no = 12;
        player_count = load_players();   
        transitioning = true;            
        generate_leaderboard(current_level2);
    }
    //menu
    else if(idx==1){
        printf("Menu\n");
        page_no = 1;
    }
    //exit
    else if(idx==3){
        exit(0);
    }
}

void check_lost_buttons(int mx, int my, int &page_no)
{
    if(is_alive)return;
    //retry
    if(mx>=630 && mx<=810 && my>=390 && my<=440){
        reload();
    }
    //leaderboard
    if(mx>=630 && mx<=810 && my>=310 && my<=370)
    {
        pre_page = page_no;
        page_no = 12;
        player_count = load_players();   
        transitioning = true;            
        generate_leaderboard(current_level2);
    }
    //menu
    else if(mx>=630 && mx<=810 && my>=230 && my<=290){
        page_no=1;
    }
}

void check_pause_buttons(int mx, int my, int &page_no)
{
    if(!paused)return;
    //play
    if(mx>=SCREEN_WIDTH/2-20 && mx<=SCREEN_WIDTH/2+150 && my>=550 && my<=600){
        paused = false;
    }
    //retry
    else if(mx>=SCREEN_WIDTH/2-20 && mx<=SCREEN_WIDTH/2+150 && my>=470&& my<=530){
        reload();
    }
    //help
    else if(mx>=SCREEN_WIDTH/2-20 && mx<=SCREEN_WIDTH/2+150 && my>=320 && my<=370){
        help_showed = true;
    }
    //Settings
    else if(mx>=SCREEN_WIDTH/2-20 && mx<=SCREEN_WIDTH/2+150 && my>=390 && my<=450){
        pre_page = page_no;
        page_no=11;
    }
    //Menu
    else if(mx>=SCREEN_WIDTH/2-20 && mx<=SCREEN_WIDTH/2+150 && my>=230 && my<=290){
        page_no=1;
    }
}

void animate_levels()
{
    t++;

    animate_monsters(current_lvl);
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

void obstacle_collision()
{
    for (int j = 0; j < OBSTACLE_COUNT; j++)
    {
        if (iCheckCollision(&player.sprite, &obstacles[j].sprite))
        {
            if (!is_hurting)
            {
                is_hurting = true;
                update_health(10);
            }
        }
    }

    // level 3 & 4
    // checking if faces spike
    for (int j = 0; j < OBSTACLE_COUNT; j++)
    {
        if (iCheckCollision(&player.sprite, &obstacles[j].sprite))
        {
            if (!is_hurting)
            {
                is_hurting = true;
                update_health(10);
                // printf("B %d\n",health);
            }
        }
    }
    // checking if faces roller
    for (int j = 0; j < ROLLER_NO; j++)
    {
        if (iCheckCollision(&player.sprite, &roller[j].sprite))
        {
            if (!is_hurting)
            {
                is_hurting = true;
                update_health(15);
                // printf("B %d\n",health);
            }
        }
    }

    // level 5
    // checking if faces spike
    for (int j = 0; j < OBSTACLE_COUNT; j++)
    {
        if (iCheckCollision(&player.sprite, &obstacles[j].sprite))
        {
            if (!is_hurting)
            {
                is_hurting = true;
                update_health(10);
                // printf("B %d\n",health);
            }
        }
    }
    // checking if faces roller
    for (int j = 0; j < ROLLER_NO; j++)
    {
        if (iCheckCollision(&player.sprite, &roller[j].sprite))
        {
            if (!is_hurting)
            {
                is_hurting = true;
                update_health(15);
                // printf("B %d\n",health);
            }
        }
    }
    // checking if faces explosion
    for (int j = 0; j < Explosion_NO; j++)
    {
        if (iCheckCollision(&player.sprite, &explosion[j].sprite))
        {
            if (!is_hurting)
            {
                is_hurting = true;
                update_health(20);
                // printf("B %d\n",health);
            }
        }
    }

    // level 6
    for (int j = 0; j < OBSTACLE_COUNT; j++)
    {
        if (iCheckCollision(&player.sprite, &obstacles[j].sprite))
        {
            if (!is_hurting)
            {
                is_hurting = true;
                update_health(10);
                // printf("B %d\n",health);
            }
        }
    }
    // checking if faces roller
    for (int j = 0; j < ROLLER_NO; j++)
    {
        if (iCheckCollision(&player.sprite, &roller[j].sprite))
        {
            if (!is_hurting)
            {
                is_hurting = true;
                update_health(15);
                // printf("B %d\n",health);
            }
        }
    }
    // checking if faces explosion
    for (int j = 0; j < Explosion_NO; j++)
    {
        if (iCheckCollision(&player.sprite, &explosion[j].sprite))
        {
            if (!is_hurting)
            {
                is_hurting = true;
                update_health(20);
                // printf("B %d\n",health);
            }
        }
    }
    // cheaking if faces blades
    for (int j = 0; j < LEVEL6_OBSTACLE_COUNT; j++)
    {
        if (iCheckCollision(&player.sprite, &level6_obstacles[j].sprite))
        {
            if (!is_hurting)
            {
                is_hurting = true;
                update_health(10);
                // printf("B %d\n",health);
            }
        }
    }
}

void reset_collisions()
{
    collision_down = false;
    collision_left = false;
    collision_right = false;
    collision_up = false;
}

bool portal_collision(Sprite *portal)
{
    for (int j = 0; j < OBSTACLE_COUNT; j++)
    {
        if (iCheckCollision(portal, &obstacles[j].sprite))
        {
            return true;
        }
    }

    // level 3 & 4
    // checking if faces spike
    for (int j = 0; j < OBSTACLE_COUNT; j++)
    {
        if (iCheckCollision(portal, &obstacles[j].sprite))
        {
            return true;
        }
    }
    // checking if faces roller
    for (int j = 0; j < ROLLER_NO; j++)
    {
        if (iCheckCollision(portal, &roller[j].sprite))
        {
            return true;
        }
    }

    // level 5
    // checking if faces spike
    for (int j = 0; j < OBSTACLE_COUNT; j++)
    {
        if (iCheckCollision(portal, &obstacles[j].sprite))
        {
            return true;
        }
    }
    // checking if faces roller
    for (int j = 0; j < ROLLER_NO; j++)
    {
        if (iCheckCollision(portal, &roller[j].sprite))
        {
            return true;
        }
    }
    // checking if faces explosion
    for (int j = 0; j < Explosion_NO; j++)
    {
        if (iCheckCollision(portal, &explosion[j].sprite))
        {
            return true;
        }
    }

    // level 6
    for (int j = 0; j < OBSTACLE_COUNT; j++)
    {
        if (iCheckCollision(portal, &obstacles[j].sprite))
        {
            return true;
        }
    }
    // checking if faces roller
    for (int j = 0; j < ROLLER_NO; j++)
    {
        if (iCheckCollision(portal, &roller[j].sprite))
        {
            return true;
        }
    }
    // checking if faces explosion
    for (int j = 0; j < Explosion_NO; j++)
    {
        if (iCheckCollision(portal, &explosion[j].sprite))
        {
            return true;
        }
    }
    // cheaking if faces blades
    for (int j = 0; j < LEVEL6_OBSTACLE_COUNT; j++)
    {
        if (iCheckCollision(portal, &level6_obstacles[j].sprite))
        {
            return true;
        }
    }
}
#endif
