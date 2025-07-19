#include "iGraphics.h"
#include "MazeExplorer/level_dependencies.h"
#include "MazeExplorer/player.h"
#include "MazeExplorer/monster.h"

Image  mazeframes6[1], lvlblur6[1], exitframes6[1];
Sprite maze6, mazeblur6, exit_portal6;


int start_x6 = -1180, start_y6 = 300, end_x6 = 430, end_y6 = 4120;


void lvl6_load_resources()
{
    iLoadFramesFromSheet(mazeframes6, "MazeExplorer/assests/levels/level6f.png", 1, 1);
    iInitSprite(&maze6, -1);
    iChangeSpriteFrames(&maze6, mazeframes6, 1);
    iSetSpritePosition(&maze6, start_x6, start_y6);
    iScaleSprite(&maze6, 2.0);

    iLoadFramesFromSheet(lvlblur6, "MazeExplorer/assests/levels/level6fblur.png", 1, 1);
    iInitSprite(&mazeblur6, -1);
    iChangeSpriteFrames(&mazeblur6, lvlblur6, 1);
    iSetSpritePosition(&mazeblur6, start_x6 - 70, start_y6 - 70);
    iScaleSprite(&mazeblur6, 2.0);

    iLoadFramesFromSheet(exitframes6, "MazeExplorer/assests/levels/exit_portal.png", 1, 1);
    iInitSprite(&exit_portal6, -1);
    iChangeSpriteFrames(&exit_portal6, exitframes6, 1);
    iSetSpritePosition(&exit_portal6, end_x6, end_y6);
}


void draw_lvl6()
{
    maze6.x = start_x6 + (player_x - player_relative_x);
    maze6.y = start_y6 + player_y - player_relative_y;
    mazeblur6.x = start_x6 + (player_x - player_relative_x) - 70;
    mazeblur6.y = start_y6 + player_y - player_relative_y - 70;

    exit_portal6.x = end_x6 + (player_x - player_relative_x);
    exit_portal6.y = end_y6 + player_y - player_relative_y;

    iShowSprite(&exit_portal6);
    iShowSprite(&maze6);
    iShowSprite(&mazeblur6);
}

void check_collision6()
{
    if(current_lvl!=6)return;
    if(iCheckCollision(&maze6, &player.sprite)){
        if(!is_hurting){
            is_hurting = true;
            update_health(20);
        }
    }

    if(iCheckCollision(&exit_portal6, &player.sprite)){
        level_completed();
    }

    for(int i = 0; i < MAX_BULLETS; i++){
        for(int j = 0; j < bat_no; j++){
            if(released[i] && iCheckCollision(&bullets[i], &bats[j].sprite)){
                bats[j].is_alive = 0;
                update_score("kill_monster", current_lvl);
            }
        }
    }

    for(int i = 0; i < MAX_BULLETS; i++){
        for(int j = 0; j < SLIME_NO; j++){
            if(released[i] && iCheckCollision(&bullets[i], &slimes[j].sprite)){
                slimes[j].isAlive = 0;
                update_score("kill_monster", current_lvl);
            }
        }
    }

    for(int j = 0; j < diamond_no; j++){
        if(diamonds[j].is_visible && iCheckCollision(&player.sprite, &diamonds[j].sprite)){
            diamonds[j].is_visible = 0;
            cout << "Diamond collected" << endl;
            diamond_collected++;
            update_diamonds();
        }
    }
}