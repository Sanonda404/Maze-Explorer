#ifndef PLAYER_H
#define PLAYER_H

#include "iGraphics.h"
#include"MazeExplorer/bullet.h"
#include "ScoreTimeManager.h"
#include "MazeExplorer/level_dependencies.h"

int speed = 15;

int const walk_frame_no = 7;
int const idle_frame_no = 1;

int player_x = 1400/2, player_y = 800/2;
int player_relative_x = player_x, player_relative_y = player_y;

int health = 100;

string dir_name = "right";

Image heart, health_bar_under, health_bar_hover;
double health_bar_width = 200;
bool is_hurting = false;
int hurt_timer = 20, max_hurt_time = 20;

bool direction_changed = false;

bool lvl_completed = false;

bool paused = false;

bool is_alive = true;
bool started = false;

int diamond_collected = 0;
float diamond_bar_width = 0;
int max_diamonds[] = {2,3,5,4,6,6};
int current_lvl = 1;
Image diamond_icon, diamond_bar_under, diamond_bar_hover;

typedef enum
{
    IDLE,
    WALK,
    ATTACK,
    DEATH

} State;

typedef struct
{
    Image idle_down[1], idle_up[1], idle_left[1], idle_right[1], walk_down[7], walk_up[7], walk_left[7], walk_right[7], death[5];
    Sprite sprite;
    State state;
    int direction_x; // 1 for left, -1 for right
    int direction_y; //1 for up, 1 for down
}Player;

Player player;

void loadPlayer()
{

    load_bullet();

    iLoadFramesFromSheet(player.idle_down, "MazeExplorer/assests/player/character_down.png", 1, idle_frame_no);
    iLoadFramesFromSheet(player.idle_up, "MazeExplorer/assests/player/character_up.png", 1, idle_frame_no);
    iLoadFramesFromSheet(player.idle_right, "MazeExplorer/assests/player/character_right.png", 1, idle_frame_no);
    iLoadFramesFromSheet(player.idle_left, "MazeExplorer/assests/player/character_left.png", 1, idle_frame_no);
    iLoadFramesFromSheet(player.walk_down, "MazeExplorer/assests/player/down_rotation.png", 1, walk_frame_no);
    iLoadFramesFromSheet(player.walk_up, "MazeExplorer/assests/player/up_rotation.png", 1, walk_frame_no);
    iLoadFramesFromSheet(player.walk_right, "MazeExplorer/assests/player/right_rotation.png", 1, walk_frame_no);
    iLoadFramesFromSheet(player.walk_left, "MazeExplorer/assests/player/left_rotation.png", 1, walk_frame_no);
    iLoadFramesFromSheet(player.death, "MazeExplorer/assests/player/exp/dead.png", 1, 3);

    //health bar
    iLoadImage(&heart, "MazeExplorer/assests/levels/heart.png");
    iLoadImage(&health_bar_under, "MazeExplorer/assests/levels/healthbar_under.png");

    //diamond bar
    iLoadImage(&diamond_icon, "MazeExplorer/assests/levels/diamond_icon.png");
    iScaleImage(&diamond_icon, 0.3);
    iLoadImage(&diamond_bar_under, "MazeExplorer/assests/levels/healthbar_under.png");

    iInitSprite(&player.sprite, -1);
    iChangeSpriteFrames(&player.sprite, player.idle_right, idle_frame_no);

    iSetSpritePosition(&player.sprite, player_x, player_y);

    iScaleSprite(&player.sprite, 0.4);
    player.state = IDLE;
    player.direction_x = 1; // 1 for right, -1 for left, 0 for up and down
    player.direction_y = 0; // 1 for up, -1 for down, 0 for left and right
}

void draw_player()
{
    draw_bullet();

    iShowSprite(&player.sprite);
    
    //health bar
    iShowImage(70, 750, "MazeExplorer/assests/levels/healthbar_under.png");
    iSetColor(214, 23, 31);
    iFilledRectangle(73, 753, health_bar_width, 25);
    iShowImage(35, 740, "MazeExplorer/assests/levels/heart.png");

    //diamond bar
    iShowImage(70, 650, "MazeExplorer/assests/levels/healthbar_under.png");
    iSetColor(21, 231, 31);
    iFilledRectangle(73, 653, diamond_bar_width, 25);
    iShowImage(40, 640, "MazeExplorer/assests/levels/diamond_icon.png");
    
}

void move_player()
{
    if(lvl_completed || paused || !is_alive || !started)return;
    if(dir_name=="left"){
        player_relative_x-=speed;
        iChangeSpriteFrames(&player.sprite, player.idle_left, idle_frame_no);
    }
    if(dir_name== "right"){
        player_relative_x+=speed;
        iChangeSpriteFrames(&player.sprite, player.idle_right, idle_frame_no);
    }
    if(dir_name == "up"){
        player_relative_y+=speed;
        iChangeSpriteFrames(&player.sprite, player.idle_up, idle_frame_no);
    }
    if(dir_name=="down"){
        player_relative_y-=speed;
        iChangeSpriteFrames(&player.sprite, player.idle_down, idle_frame_no);
    }
}

void lost_game()
{
    if(!is_alive)return;
    is_alive = false;
    play_sound("lost");
}

void update_health(int amount)
{
    health -= amount;
    if(health<=0)lost_game();
    health_bar_width = 200*health/100;
    health_bar_width = max(0.0,health_bar_width);
}

void update_diamonds()
{
    diamond_bar_width = 200*diamond_collected/max_diamonds[current_lvl-1];
}

void player_animate()
{
    move_bullet();

    if(lvl_completed || paused || !is_alive)return;

    switch (player.state)
    {
    case IDLE:
        break;
    case WALK:
        if (!isSpecialKeyPressed(GLUT_KEY_LEFT) &&
            !isSpecialKeyPressed(GLUT_KEY_RIGHT) && !isSpecialKeyPressed(GLUT_KEY_DOWN && !isSpecialKeyPressed(GLUT_KEY_UP)))
        {
            player.state = IDLE;
            if(dir_name=="right")
                iChangeSpriteFrames(&player.sprite, player.idle_right, idle_frame_no);
            else if(dir_name=="left")
                iChangeSpriteFrames(&player.sprite, player.idle_left, idle_frame_no);
            else if(dir_name=="up")
                iChangeSpriteFrames(&player.sprite,player.idle_up, idle_frame_no );
            else
                iChangeSpriteFrames(&player.sprite, player.idle_down, idle_frame_no);
        }
        break;
    case ATTACK:
        break;
    case DEATH:
        break;
    }
    iAnimateSprite(&player.sprite);

    
}

void iSpecialKeyboard(unsigned char key)
{

    //left arrow
    if (key == GLUT_KEY_LEFT)
    {
        if(dir_name!="left")direction_changed = true;

        dir_name = "left";

        move_player();


        if (player.state != WALK)
        {
            player.state = WALK;
            
        }

        //if(direction_changed){
           // iChangeSpriteFrames(&player.sprite, player.walk_left, 4);
        //}
    }
    //right arrow
    if (key == GLUT_KEY_RIGHT)
    {
        if(dir_name!="right")direction_changed = true;

        dir_name = "right";

        move_player();

        
        if (player.state != WALK)
        {
            player.state = WALK;
            
            
        }

        //if(direction_changed){
        //    iChangeSpriteFrames(&player.sprite, player.walk_right, 4);
        //}
    }
    //Up arrow
    if (key == GLUT_KEY_UP)
    {
        if(dir_name!="up")direction_changed = true;

        dir_name = "up";

        move_player();

        
        if (player.state != WALK)
        {
            player.state = WALK;
            
            
        }

        //if(direction_changed){
        //    iChangeSpriteFrames(&player.sprite, player.walk_up, 4);
        //}
    }
    //down arrow
    if (key == GLUT_KEY_DOWN)
    {
        if(dir_name!="down")direction_changed = true;

        dir_name = "down";

        move_player();

        
        if (player.state != WALK)
        {
            player.state = WALK;
            
            
        }

        //if(direction_changed){
         //   iChangeSpriteFrames(&player.sprite, player.walk_down, 4);
        //}
    }
    // place your codes for other keys here
}

void iKeyboard(unsigned char key)
{
    switch (key)
    {
    case ' '://detecting attack
        player.state = ATTACK;
        attacking = true;
        shoot_bullet(dir_name);
        break;
    // place your codes for other keys here
    default:
        break;
    }
}

#endif