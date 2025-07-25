#include "iGraphics.h"
#include "MazeExplorer/level_dependencies.h"
#include "MazeExplorer/player.h"
#include "MazeExplorer/monster.h"

Image mazeframes2[1], lvlblur2[1], exitframes2[1];
Sprite maze2, mazeblur2, exit_portal2;

int start_x2 = 500, start_y2 = 140, end_x2 = 2830, end_y2 = 2560;

void lvl2_load_resources()
{
    // maze
    iLoadFramesFromSheet(mazeframes2, "MazeExplorer/assests/levels/level2f.png", 1, 1);
    iInitSprite(&maze2);
    iChangeSpriteFrames(&maze2, mazeframes2, 1);
    iSetSpritePosition(&maze2, start_x2, start_y2);
    iScaleSprite(&maze2, 2.0);
    iLoadFramesFromSheet(lvlblur2, "MazeExplorer/assests/levels/level2fblur.png", 1, 1);
    iInitSprite(&mazeblur2);
    iChangeSpriteFrames(&mazeblur2, lvlblur2, 1);
    iSetSpritePosition(&mazeblur2, start_x2 - 70, start_y2 - 70);
    iScaleSprite(&mazeblur2, 2.0);

    // exit portal
    iLoadFramesFromSheet(exitframes2, "MazeExplorer/assests/levels/exit_portal.png", 1, 1);
    iInitSprite(&exit_portal2);
    iChangeSpriteFrames(&exit_portal2, exitframes2, 1);
    iSetSpritePosition(&exit_portal2, end_x2, end_y2);
}

void draw_lvl2()
{
    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glColor4f(1.0, 1.0, 1.0, 1.0);

    maze2.x = start_x2 + (player_x - player_relative_x);
    maze2.y = start_y2 + player_y - player_relative_y;
    mazeblur2.x = start_x2 + (player_x - player_relative_x) - 70;
    mazeblur2.y = start_y2 + player_y - player_relative_y - 70;

    exit_portal2.x = end_x2 + (player_x - player_relative_x);
    exit_portal2.y = end_y2 + player_y - player_relative_y;

    iShowSprite(&exit_portal2);

    iShowSprite(&maze2);
    iShowSprite(&mazeblur2);
}

void check_collision2()
{
    if (current_lvl != 2)
        return;
    // checking if collides with fire
    // if(iCheckCollision(&fire , &player.sprite)){
    //     printf("Fire\n");
    // }

    // checking if collids with maze
    if (iCheckCollision(&maze2, &player.sprite))
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

    // checking if enters exit portal
    if (iCheckCollision(&exit_portal2, &player.sprite))
    {
        if(diamond_collected!=max_diamonds[current_lvl-1])return;
        level_completed();
    }

    // checking if bullet shoots bat
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        for (int j = 0; j < bat_no; j++)
        {
            if (released[i] && iCheckCollision(&bullets[i], &bats[j].sprite))
            {
                bats[j].is_alive = 0;
                update_score("kill_monster", current_lvl);
                // cout<<"shooted bat"<<endl;
            }
        }
    }

    // checking if bullet shoots slime
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        for (int j = 0; j < SLIME_NO; j++)
        {
            if (released[i] && iCheckCollision(&bullets[i], &slimes[j].sprite))
            {
                slimes[j].isAlive = 0;
                update_score("kill_monster", current_lvl);
                // cout<<"shooted bat"<<endl;
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
