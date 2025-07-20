#include "iGraphics.h"
#include "MazeExplorer/level_dependencies.h"
#include "MazeExplorer/player.h"
#include "MazeExplorer/monster.h"

Image mazeframes5[1], lvlblur5[1], exitframes5[1];
Sprite maze5, mazeblur5, exit_portal5;

int start_x5 = -1600, start_y5 = 0, end_x5 = -1535, end_y5 = 2600;

void lvl5_load_resources()
{
    iLoadFramesFromSheet(mazeframes5, "MazeExplorer/assests/levels/level5f.png", 1, 1);
    iInitSprite(&maze5, -1);
    iChangeSpriteFrames(&maze5, mazeframes5, 1);
    iSetSpritePosition(&maze5, start_x5, start_y5);
    iScaleSprite(&maze5, 2.0);

    iLoadFramesFromSheet(lvlblur5, "MazeExplorer/assests/levels/level5fblur.png", 1, 1);
    iInitSprite(&mazeblur5, -1);
    iChangeSpriteFrames(&mazeblur5, lvlblur5, 1);
    iSetSpritePosition(&mazeblur5, start_x5 - 70, start_y5 - 70);
    iScaleSprite(&mazeblur5, 2.0);

    iLoadFramesFromSheet(exitframes5, "MazeExplorer/assests/levels/exit_portal.png", 1, 1);
    iInitSprite(&exit_portal5, -1);
    iChangeSpriteFrames(&exit_portal5, exitframes5, 1);
    iSetSpritePosition(&exit_portal5, end_x5, end_y5);
}

void draw_lvl5()
{
    maze5.x = start_x5 + (player_x - player_relative_x);
    maze5.y = start_y5 + player_y - player_relative_y;
    mazeblur5.x = start_x5 + (player_x - player_relative_x) - 70;
    mazeblur5.y = start_y5 + player_y - player_relative_y - 70;

    exit_portal5.x = end_x5 + (player_x - player_relative_x);
    exit_portal5.y = end_y5 + player_y - player_relative_y;

    iShowSprite(&exit_portal5);
    iShowSprite(&maze5);
    iShowSprite(&mazeblur5);
}

void check_collision5()
{
    if (current_lvl != 5)
        return;

    if (iCheckCollision(&maze5, &player.sprite))
    {
        collision = true;
        reset_collisions();
        if (dir_name == "left")
            collision_left = true;
        if (dir_name == "right")
            collision_right = true;
        if (dir_name == "up")
            collision_up = true;
        if (dir_name == "down")
            collision_down = true;
        if (!is_hurting)
        {
            is_hurting = true;
            update_health(20);
            // printf("B %d\n",health);
        }
    }

    else
    {
        collision = false;
        reset_collisions();
    }

    if (iCheckCollision(&exit_portal5, &player.sprite))
    {
        level_completed();
    }

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        for (int j = 0; j < bat_no; j++)
        {
            if (released[i] && iCheckCollision(&bullets[i], &bats[j].sprite))
            {
                bats[j].is_alive = 0;
                update_score("kill_monster", current_lvl);
            }
        }
    }

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        for (int j = 0; j < SLIME_NO; j++)
        {
            if (released[i] && iCheckCollision(&bullets[i], &slimes[j].sprite))
            {
                slimes[j].isAlive = 0;
                update_score("kill_monster", current_lvl);
            }
        }
    }

    // checking if collects diamond
    for (int j = 0; j < max_diamonds[current_lvl - 1]; j++)
    {
        if (diamonds[j].is_visible && iCheckCollision(&player.sprite, &diamonds[j].sprite))
        {
            diamonds[j].is_visible = 0; // hide the diamond
            diamond_collected++;        // increment count
            update_diamonds();          // update file/data if needed

            // Optional: play sound or show sparkle effect
            printf("Diamond collected at (%d, %d)\n", diamonds[j].sprite.x, diamonds[j].sprite.y);
        }
    }
}