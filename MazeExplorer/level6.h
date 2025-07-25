#include "iGraphics.h"
#include "MazeExplorer/level_dependencies.h"
#include "MazeExplorer/player.h"
#include "MazeExplorer/monster.h"

Image mazeframes6[1], lvlblur6[1], exitframes6[1];
Sprite maze6, mazeblur6, exit_portal6;

int start_x6 = -1180, start_y6 = 300, end_x6 = 430, end_y6 = 4120;

void lvl6_load_resources()
{
    iLoadFramesFromSheet(mazeframes6, "MazeExplorer/assests/levels/level6f.png", 1, 1);
    iInitSprite(&maze6);
    iChangeSpriteFrames(&maze6, mazeframes6, 1);
    iSetSpritePosition(&maze6, start_x6, start_y6);
    iScaleSprite(&maze6, 2.0);

    iLoadFramesFromSheet(lvlblur6, "MazeExplorer/assests/levels/level6fblur.png", 1, 1);
    iInitSprite(&mazeblur6);
    iChangeSpriteFrames(&mazeblur6, lvlblur6, 1);
    iSetSpritePosition(&mazeblur6, start_x6 - 70, start_y6 - 70);
    iScaleSprite(&mazeblur6, 2.0);

    iLoadFramesFromSheet(exitframes6, "MazeExplorer/assests/levels/exit_portal.png", 1, 1);
    iInitSprite(&exit_portal6);
    iChangeSpriteFrames(&exit_portal6, exitframes6, 1);
    iSetSpritePosition(&exit_portal6, end_x6, end_y6);
}

void draw_lvl6()
{
    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glColor4f(1.0, 1.0, 1.0, 1.0);

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
    if (current_lvl != 6)
        return;

    if (iCheckCollision(&maze6, &player.sprite))
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
            update_health(15);
            // printf("B %d\n",health);
        }
    }

    else
    {
        collision = false;
        reset_collisions();
    }

    if (iCheckCollision(&exit_portal6, &player.sprite))
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
            update_health(-10);
            // Optional: play sound or show sparkle effect
            printf("Diamond collected at (%d, %d)\n", diamonds[j].sprite.x, diamonds[j].sprite.y);
        }
    }
}