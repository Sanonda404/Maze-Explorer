#include "iGraphics.h"
#include "MazeExplorer/player.h"
#include "MazeExplorer/monster.h"
#include "MazeExplorer/time.h"

Image  ghostframes1[8], mazeframes[1], exitframes[1], bg, lvl_comp, paused_img, pause_option, lvl1blur[1], lost;
Sprite ghost1;
Sprite maze, mazeblur;
Sprite exit_portal;

int  b_x=0, b_y=0;

int t=0;

int start_x = 500, start_y = 140, end_x = 2600, end_y = 2300;

void lvl_load_resources()
{
    //background
    iLoadImage(&bg, "MazeExplorer/assests/levels/bg1.png");
    iScaleImage(&bg, 3.0);


    //exit portal
    iLoadFramesFromSheet(exitframes, "MazeExplorer/assests/levels/exit_portal.png",1,1);
    iInitSprite(&exit_portal, -1);
    iChangeSpriteFrames(&exit_portal, exitframes, 1);
    iSetSpritePosition(&exit_portal, end_x, end_y);


    //maze
    iLoadFramesFromSheet(mazeframes, "MazeExplorer/assests/levels/lvl1f.png",1,1);
    iInitSprite(&maze, -1);
    iChangeSpriteFrames(&maze, mazeframes, 1);
    iSetSpritePosition(&maze, start_x, start_y);
    iScaleSprite(&maze, 2.0);
    iLoadFramesFromSheet(lvl1blur, "MazeExplorer/assests/levels/lvl1blurf.png",1,1);
    iInitSprite(&mazeblur, -1);
    iChangeSpriteFrames(&mazeblur, lvl1blur, 1);
    iSetSpritePosition(&mazeblur, start_x-70, start_y-70);
    iScaleSprite(&mazeblur, 2.0);

    loadPlayer();

    load_monsters();

    //paused
    iLoadImage(&paused_img, "MazeExplorer/assests/levels/pause_button.png");
    iLoadImage(&pause_option, "MazeExplorer/assests/levels/paused.png");

    //lvl_completed
    iLoadImage(&lvl_comp, "MazeExplorer/assests/levels/lvl_completed.png");

    //lost
    iLoadImage(&lost, "MazeExplorer/assests/levels/lost.png");
    
}

void draw_lvl1()
{
    //iShowImage(start_x,start_y, "MazeExplorer/assests/levels/bg1.png");

    
    maze.x = start_x + (player_x-player_relative_x);
    maze.y = start_y + player_y -player_relative_y;
    mazeblur.x = start_x + (player_x-player_relative_x)-70;
    mazeblur.y = start_y + player_y -player_relative_y-70;

    exit_portal.x = end_x + (player_x-player_relative_x);
    exit_portal.y = end_y + player_y -player_relative_y;

    iShowSprite(&exit_portal);


    iShowSprite(&maze);
    iShowSprite(&mazeblur);

    draw_player();
    draw_monsters((player_x-player_relative_x), (player_y-player_relative_y));

    //pause button
    iShowImage(SCREEN_WIDTH-100,SCREEN_HEIGHT-100, "MazeExplorer/assests/levels/pause_button.png");
    if(paused && !lvl_completed)iShowImage(SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-200, "MazeExplorer/assests/levels/paused.png");

    if(lvl_completed){
        iShowImage(SCREEN_WIDTH/2-200,SCREEN_HEIGHT/2-200,"MazeExplorer/assests/levels/lvl_completed.png");
        display_highscore(700,500);
    }

    if(!is_alive){
        iShowImage(SCREEN_WIDTH/2-200,SCREEN_HEIGHT/2-200,"MazeExplorer/assests/levels/lost.png");
    }

    display_time();
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

    reset_monsters();
}

void level_completed()
{
    if(lvl_completed)return;
    lvl_completed = true;
    calc_score(time_passed, health);
    play_sound("won");
    loadHighScore();
    
}

bool check_paused_pressed(int mx, int my)
{
    printf("Mouse pos %d %d\n",mx,my);
    printf("Player pos %d %d\n",player_relative_x, player_relative_y);
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

void check_collision()
{
    //checking if collides with fire
    //if(iCheckCollision(&fire , &player.sprite)){
    //    printf("Fire\n");
    //}

    //checking if collids with maze
    if(iCheckCollision(&maze, &player.sprite)){
        if(!is_hurting){
            is_hurting = true;
            health -= 10;
            update_health();
           // printf("B %d\n",health);
        }      
    }

    //checking if enters exit portal
    if(iCheckCollision(&exit_portal, &player.sprite)){
        level_completed();
    }

    //checking if bullet shoots bat
    for(int i=0; i<MAX_BULLETS; i++){
        for(int j=0; j<bat_no; j++){
            if(released[i] && iCheckCollision(&bullets[i], &bats[j].sprite)){
                bats[j].is_alive = 0;
                update_score("kill_monster");
                //cout<<"shooted bat"<<endl;
            }
        }
    }

    //checking if bullet shoots slime
    for(int i=0; i<MAX_BULLETS; i++){
        for(int j=0; j<SLIME_NO; j++){
            if(released[j] && iCheckCollision(&bullets[i], &slimes[j].sprite)){
                slimes[j].isAlive = 0;
                update_score("kill_monster");
                //cout<<"shooted bat"<<endl;
            }
        }
    }

    //checking if collects diamond
    for(int j=0; j<diamond_no; j++){
        if(diamonds[j].is_visible && iCheckCollision(&player.sprite, &diamonds[j].sprite)){
            diamonds[j].is_visible = 0;
            cout<<"Diamond collected"<<endl;
        }
    }

}

void lvl1_animate()
{
    t++;

    animate_monsters();

    if(t%1==0){
        player_animate();
        iAnimateSprite(&ghost1);
    }

    if (is_hurting)hurt_timer--;
    if(hurt_timer==0){
        hurt_timer = max_hurt_time;
        is_hurting = false;
    }

    if(!lvl_completed && is_alive && !paused){
        update_time();
        move_monsters(player_relative_x, player_relative_y);
    }
}


