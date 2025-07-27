#ifndef PLAYER_H
#define PLAYER_H

#include "iGraphics.h"
#include"MazeExplorer/bullet.h"
#include "ScoreTimeManager.h"
#include "MazeExplorer/level_dependencies.h"
#include "MazeExplorer/diamonds.h"
#include "MazeExplorer/Signup.h"
#include "MazeExplorer/SoundManager.h"

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
int current_lvl = 1;
Image diamond_icon, diamond_bar_under, diamond_bar_hover;

bool collision_left = false, collision_right = false, collision_up = false, collision_down = false, collision=false;

typedef enum
{
    IDLE,
    WALK,
    ATTACK,
    DEATH

} State;

typedef struct
{
    Image idle_down[1], idle_up[1], idle_left[1], idle_right[1];
    Sprite sprite;
    State state;
    int direction_x; // 1 for left, -1 for right
    int direction_y; //1 for up, 1 for down
}Player;

typedef struct
{
    Image idle_down[1], idle_up[1], idle_left[1], idle_right[1];
    Sprite sprite;
    State state;
    int direction_x; // 1 for left, -1 for right
    int direction_y; //1 for up, 1 for down
}Player_Hurt;

Player player;
Player_Hurt player_hurt;

char sprites[4][50];
char hurt_sprites[4][60];

void loadPlayer()
{
    //printf("%d",new_player.selected_character);
    sprintf(sprites[0],"MazeExplorer/assests/player/character%d_down.png",new_player.selected_character);//down
    sprintf(sprites[1],"MazeExplorer/assests/player/character%d_up.png",new_player.selected_character);//up
    sprintf(sprites[2],"MazeExplorer/assests/player/character%d_right.png",new_player.selected_character);//right
    sprintf(sprites[3],"MazeExplorer/assests/player/character%d_left.png",new_player.selected_character);//left

    sprintf(hurt_sprites[0],"MazeExplorer/assests/player/character%d_downhurt.png",new_player.selected_character);//down
    sprintf(hurt_sprites[1],"MazeExplorer/assests/player/character%d_uphurt.png",new_player.selected_character);//up
    sprintf(hurt_sprites[2],"MazeExplorer/assests/player/character%d_righthurt.png",new_player.selected_character);//right
    sprintf(hurt_sprites[3],"MazeExplorer/assests/player/character%d_lefthurt.png",new_player.selected_character);//left

    load_bullet();

    iLoadFramesFromSheet(player.idle_down, sprites[0], 1, idle_frame_no);
    iLoadFramesFromSheet(player.idle_up, sprites[1], 1, idle_frame_no);
    iLoadFramesFromSheet(player.idle_right, sprites[2], 1, idle_frame_no);
    iLoadFramesFromSheet(player.idle_left, sprites[3], 1, idle_frame_no);
    
    iLoadFramesFromSheet(player_hurt.idle_down, hurt_sprites[0], 1, idle_frame_no);
    iLoadFramesFromSheet(player_hurt.idle_up, hurt_sprites[1], 1, idle_frame_no);
    iLoadFramesFromSheet(player_hurt.idle_right, hurt_sprites[2], 1, idle_frame_no);
    iLoadFramesFromSheet(player_hurt.idle_left, hurt_sprites[3], 1, idle_frame_no);
    //return;

    //health bar
    iLoadImage(&heart, "MazeExplorer/assests/levels/heart.png");
    iLoadImage(&health_bar_under, "MazeExplorer/assests/levels/healthbar_under.png");

    //diamond bar
    iLoadImage(&diamond_icon, "MazeExplorer/assests/levels/diamond_icon.png");
    iScaleImage(&diamond_icon, 0.3);
    iLoadImage(&diamond_bar_under, "MazeExplorer/assests/levels/healthbar_under.png");

    iInitSprite(&player.sprite);
    iInitSprite(&player_hurt.sprite);
    iChangeSpriteFrames(&player.sprite, player.idle_right, idle_frame_no);
    iChangeSpriteFrames(&player_hurt.sprite, player_hurt.idle_right, idle_frame_no);

    iSetSpritePosition(&player.sprite, player_x, player_y);
    iSetSpritePosition(&player_hurt.sprite, player_x, player_y);

    iScaleSprite(&player.sprite, 0.4);
    iScaleSprite(&player_hurt.sprite, 0.4);
    player.state = IDLE;
    player_hurt.state = IDLE;
    player.direction_x = 1; // 1 for right, -1 for left, 0 for up and down
    player.direction_y = 0; // 1 for up, -1 for down, 0 for left and right
    player_hurt.direction_x = 1;
    player_hurt.direction_y = 0;
}

void draw_player()
{
    draw_bullet();

    iShowSprite(&player.sprite);
    if(is_hurting)iShowSprite(&player_hurt.sprite);
    
    //health bar
    iShowImage(70, 750, "MazeExplorer/assests/levels/healthbar_under.png");
    iSetColor(214, 23, 31);
    iFilledRectangle(73, 753, health_bar_width, 25);
    iShowImage(35, 740, "MazeExplorer/assests/levels/heart.png");

    //diamond bar
    iShowImage(70, 700, "MazeExplorer/assests/levels/healthbar_under.png");
    iSetColor(21, 231, 31);
    iFilledRectangle(73, 703, diamond_bar_width, 25);
    iShowImage(40, 690, "MazeExplorer/assests/levels/diamond_icon.png");
    
}

void move_player()
{
    if(lvl_completed || paused || !is_alive || !started)return;
    if(dir_name=="left" && !collision_left){
        if(collision_right)collision_right = false;
        player_relative_x-=speed;
        iChangeSpriteFrames(&player.sprite, player.idle_left, idle_frame_no);
        iChangeSpriteFrames(&player_hurt.sprite, player_hurt.idle_left, idle_frame_no);
    }
    if(dir_name== "right" && !collision_right){
        if(collision_left)collision_left=false;
        player_relative_x+=speed;
        iChangeSpriteFrames(&player.sprite, player.idle_right, idle_frame_no);
        iChangeSpriteFrames(&player_hurt.sprite, player_hurt.idle_right, idle_frame_no);
    }
    if(dir_name == "up" && !collision_up){
        if(collision_down)collision_down = false;
        player_relative_y+=speed;
        iChangeSpriteFrames(&player.sprite, player.idle_up, idle_frame_no);
        iChangeSpriteFrames(&player_hurt.sprite, player_hurt.idle_up, idle_frame_no);
    }
    if(dir_name=="down" && !collision_down){
        if(collision_up)collision_up=false;
        player_relative_y-=speed;
        iChangeSpriteFrames(&player.sprite, player.idle_down, idle_frame_no);
        iChangeSpriteFrames(&player_hurt.sprite, player_hurt.idle_down, idle_frame_no);
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
    if(health>0 && amount>0)play_sound("hurt");
    health -= amount;
    health = min(100,health);
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
            if(dir_name=="right"){
                iChangeSpriteFrames(&player.sprite, player.idle_right, idle_frame_no);
                iChangeSpriteFrames(&player_hurt.sprite, player_hurt.idle_right, idle_frame_no);
            }
            else if(dir_name=="left"){
                iChangeSpriteFrames(&player.sprite, player.idle_left, idle_frame_no);
                iChangeSpriteFrames(&player_hurt.sprite, player_hurt.idle_left, idle_frame_no);
            }
            else if(dir_name=="up"){
                iChangeSpriteFrames(&player.sprite,player.idle_up, idle_frame_no );
                iChangeSpriteFrames(&player_hurt.sprite, player_hurt.idle_up, idle_frame_no);
            }
            else{
                iChangeSpriteFrames(&player.sprite, player.idle_down, idle_frame_no);
                iChangeSpriteFrames(&player_hurt.sprite, player_hurt.idle_down, idle_frame_no);
            }
        }
        break;
    case ATTACK:
        break;
    case DEATH:
        break;
    }
    iAnimateSprite(&player.sprite);

    
}



#endif