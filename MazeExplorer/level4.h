#include "iGraphics.h"
#include "MazeExplorer/level_dependencies.h"
#include "MazeExplorer/player.h"
#include "MazeExplorer/monster.h"

Image mazeframes4[1], lvlblur4[1], exitframes4[1];
Sprite maze4, mazeblur4, exit_portal4;

int start_x4 = -1600, start_y4 = -100, end_x4 = -1535, end_y4 = 2050;

void lvl4_load_resources()
{
    // Maze
    iLoadFramesFromSheet(mazeframes4, "MazeExplorer/assests/levels/level4f.png", 1, 1);
    iInitSprite(&maze4);
    iChangeSpriteFrames(&maze4, mazeframes4, 1);
    iSetSpritePosition(&maze4, start_x4, start_y4);
    iScaleSprite(&maze4, 2.0);

    // Blurred Maze
    iLoadFramesFromSheet(lvlblur4, "MazeExplorer/assests/levels/level4fblur.png", 1, 1);
    iInitSprite(&mazeblur4);
    iChangeSpriteFrames(&mazeblur4, lvlblur4, 1);
    iSetSpritePosition(&mazeblur4, start_x4 - 70, start_y4 - 70);
    iScaleSprite(&mazeblur4, 2.0);

    // Exit Portal
    iLoadFramesFromSheet(exitframes4, "MazeExplorer/assests/levels/exit_portal.png", 1, 1);
    iInitSprite(&exit_portal4);
    iChangeSpriteFrames(&exit_portal4, exitframes4, 1);
    iSetSpritePosition(&exit_portal4, end_x4, end_y4);
}

//  Draw level visuals
void draw_lvl4()
{
    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glColor4f(1.0, 1.0, 1.0, 1.0);

    maze4.x = start_x4 + (player_x - player_relative_x);
    maze4.y = start_y4 + player_y - player_relative_y;
    mazeblur4.x = start_x4 + (player_x - player_relative_x) - 70;
    mazeblur4.y = start_y4 + player_y - player_relative_y - 70;

    exit_portal4.x = end_x4 + (player_x - player_relative_x);
    exit_portal4.y = end_y4 + player_y - player_relative_y;

    iShowSprite(&exit_portal4);
    iShowSprite(&maze4);
    iShowSprite(&mazeblur4);
}

//  Check collision interactions
void check_collision4()
{
    if (current_lvl != 4)
        return;
    // Maze collision causes damage
    if (iCheckCollision(&maze4, &player.sprite))
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

    // Exit portal triggers level completion
    if (iCheckCollision(&exit_portal4, &player.sprite))
    {
        if(diamond_collected!=max_diamonds[current_lvl-1]){
            error_showing = true;
            return;
        }
        level_completed();
    }

    // Bullet hits bat
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

    // Bullet hits slime
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
           // printf("Diamond collected at (%d, %d)\n", diamonds[j].sprite.x, diamonds[j].sprite.y);
        play_sound("Diamond");
        }
    }
    for(int i=0; i<MAX_BULLETS; i++){
        for(int j=0; j<max_rocks[current_lvl-1]; j++){
            if(released[i] && rocks[j].is_visible && iCheckCollision(&bullets[i], &rocks[j].sprite)){
                slimes[j].isAlive = 0;
                update_score("kill_monster", current_lvl);
                destroy_rock(j);
                //printf("Rock blasted at (%d, %d)\n", diamonds[j].sprite.x, diamonds[j].sprite.y);
                play_sound("Blast");
                //cout<<"shooted bat"<<endl;
            }
        }
    }
    for (int j = 0; j < max_rocks[current_lvl - 1]; j++)
    {
        if (rocks[j].is_visible && iCheckCollision(&player.sprite, &rocks[j].sprite))
        {                // update file/data if needed
            if(!is_hurting){
            is_hurting = true;
            update_health(25);
           // printf("B %d\n",health);
        }  
            // Optional: play sound or show sparkle effect
            //printf("Rock Attack\n");
        }
    }
}