#include "iGraphics.h"
#include "MazeExplorer/level_dependencies.h"
#include "MazeExplorer/player.h"
#include "MazeExplorer/monster.h"

Image  mazeframes3[1], lvlblur3[1], exitframes3[1];
Sprite maze3, mazeblur3, exit_portal3;


int start_x3 = 580, start_y3 = 320, end_x3 = 2920, end_y3 = 2725;

void lvl3_load_resources()
{
    //maze
    iLoadFramesFromSheet(mazeframes3, "MazeExplorer/assests/levels/level3f.png",1,1);
    iInitSprite(&maze3, -1);
    iChangeSpriteFrames(&maze3, mazeframes3, 1);
    iSetSpritePosition(&maze3, start_x3, start_y3);
    iScaleSprite(&maze3, 2.0);
    iLoadFramesFromSheet(lvlblur3, "MazeExplorer/assests/levels/level3fblur.png",1,1);
    iInitSprite(&mazeblur3, -1);
    iChangeSpriteFrames(&mazeblur3, lvlblur3, 1);
    iSetSpritePosition(&mazeblur3, start_x3-70, start_y3-70);
    iScaleSprite(&mazeblur3, 2.0);

    //exit portal
    iLoadFramesFromSheet(exitframes3, "MazeExplorer/assests/levels/exit_portal.png",1,1);
    iInitSprite(&exit_portal3, -1);
    iChangeSpriteFrames(&exit_portal3, exitframes3, 1);
    iSetSpritePosition(&exit_portal3, end_x3, end_y3);
}

void draw_lvl3()
{
    maze3.x = start_x3 + (player_x - player_relative_x);
    maze3.y = start_y3 + player_y - player_relative_y;
    mazeblur3.x = start_x3 + (player_x - player_relative_x) - 70;
    mazeblur3.y = start_y3 + player_y - player_relative_y - 70;

    exit_portal3.x = end_x3 + (player_x - player_relative_x);
    exit_portal3.y = end_y3 + player_y - player_relative_y;

    iShowSprite(&exit_portal3);
    iShowSprite(&maze3);
    iShowSprite(&mazeblur3);
}

void check_collision3()
{
    if(current_lvl!=3)return;
    // Maze collision causes damage
    if(iCheckCollision(&maze3, &player.sprite)){
        if(!is_hurting){
            is_hurting = true;
            update_health(20);
        }
    }

    // Exit portal triggers level completion
    if(iCheckCollision(&exit_portal3, &player.sprite)){
        level_completed();
    }

    // Bullet hits bat
    for(int i = 0; i < MAX_BULLETS; i++){
        for(int j = 0; j < bat_no; j++){
            if(released[i] && iCheckCollision(&bullets[i], &bats[j].sprite)){
                bats[j].is_alive = 0;
                update_score("kill_monster");
            }
        }
    }

    // Bullet hits slime
    for(int i = 0; i < MAX_BULLETS; i++){
        for(int j = 0; j < SLIME_NO; j++){
            if(released[i] && iCheckCollision(&bullets[i], &slimes[j].sprite)){
                slimes[j].isAlive = 0;
                update_score("kill_monster");
            }
        }
    }

    // Diamond collection
    for(int j = 0; j < diamond_no; j++){
        if(diamonds[j].is_visible && iCheckCollision(&player.sprite, &diamonds[j].sprite)){
            diamonds[j].is_visible = 0;
            cout << "Diamond collected" << endl;
            diamond_collected++;
            update_diamonds();
        }
    }
}