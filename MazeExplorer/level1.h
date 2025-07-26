#include "iGraphics.h"
#include "MazeExplorer/level_dependencies.h"
#include "MazeExplorer/player.h"
#include "MazeExplorer/monster.h"
#include "MazeExplorer/time.h"
#include "MazeExplorer/teleportation_portal.h"

Image  mazeframes1[1], lvl1blur1[1], exitframes1[1];
Sprite maze1, mazeblur1, exit_portal1;

int start_x1 = 500, start_y1 = 140, end_x1 = 2440, end_y1 = 2000;

void lvl1_load_resources()
{
    iSetColor(0,0,0);
    iFilledRectangle(0,0,3000,3000);
    //maze
    iLoadFramesFromSheet(mazeframes1, "MazeExplorer/assests/levels/lvl1f.png",1,1);
    iInitSprite(&maze1);
    iChangeSpriteFrames(&maze1, mazeframes1, 1);
    iSetSpritePosition(&maze1, start_x1, start_y1);
    iScaleSprite(&maze1, 2.0);
    iLoadFramesFromSheet(lvl1blur1, "MazeExplorer/assests/levels/lvl1blurf.png",1,1);
    iInitSprite(&mazeblur1);
    iChangeSpriteFrames(&mazeblur1, lvl1blur1, 1);
    iSetSpritePosition(&mazeblur1, start_x1-70, start_y1-70);
    iScaleSprite(&mazeblur1, 2.0);

    //exit portal
    iLoadFramesFromSheet(exitframes1, "MazeExplorer/assests/levels/exit_portal.png",1,1);
    iInitSprite(&exit_portal1);
    iChangeSpriteFrames(&exit_portal1, exitframes1, 1);
    iSetSpritePosition(&exit_portal1, end_x1, end_y1);

    //teleportation_portal
    //load_portal();
    //generate_portal_position(start_x1,end_x1,start_y1,end_y1);
    
}

void draw_lvl1()
{
    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glColor4f(1.0, 1.0, 1.0, 1.0);
    //iShowImage(start_x,start_y, "MazeExplorer/assests/levels/bg1.png");
    //iSetColor(40,45,25);
    //iFilledRectangle(0,0,1400,800);
    
    maze1.x = start_x1 + (player_x-player_relative_x);
    maze1.y = start_y1 + player_y -player_relative_y;
    mazeblur1.x = start_x1 + (player_x-player_relative_x)-70;
    mazeblur1.y = start_y1 + player_y -player_relative_y-70;

    exit_portal1.x = end_x1 + (player_x-player_relative_x);
    exit_portal1.y = end_y1 + player_y -player_relative_y;

    iShowSprite(&exit_portal1);


    iShowSprite(&maze1);
    iShowSprite(&mazeblur1);

    //draw_teleportation_portal((player_x-player_relative_x),player_y -player_relative_y);
    
}

void check_collision1()
{
    if(current_lvl!=1)return;
    //checking if collides with fire
    //if(iCheckCollision(&fire , &player.sprite)){
    //    printf("Fire\n");
    //}

    //checking if collids with maze
    if(iCheckCollision(&maze1, &player.sprite)){
        collision = true;
        reset_collisions();
        if(dir_name=="left")collision_left = true;
        if(dir_name=="right")collision_right = true;
        if(dir_name == "up")collision_up = true;
        if(dir_name=="down")collision_down = true;
        if(!is_hurting){
            is_hurting = true;
            update_health(15);
           // printf("B %d\n",health);
        }      
    }

    else {
        collision = false;
        reset_collisions();
    }

    //checking if enters exit portal
    if(iCheckCollision(&exit_portal1, &player.sprite)){
        if(diamond_collected!=max_diamonds[current_lvl-1])return;
        level_completed();
    }

    //checking if bullet shoots bat
    for(int i=0; i<MAX_BULLETS; i++){
        for(int j=0; j<bat_no; j++){
            if(released[i] && iCheckCollision(&bullets[i], &bats[j].sprite)){
                bats[j].is_alive = 0;
                update_score("kill_monster", current_lvl);
                //cout<<"shooted bat"<<endl;
            }
        }
    }

    //checking if bullet shoots slime
    for(int i=0; i<MAX_BULLETS; i++){
        for(int j=0; j<SLIME_NO; j++){
            if(released[i] && iCheckCollision(&bullets[i], &slimes[j].sprite)){
                slimes[j].isAlive = 0;
                update_score("kill_monster", current_lvl);
                //cout<<"shooted bat"<<endl;
            }
        }
    }

    //checking if collects diamond
    for (int j = 0; j < max_diamonds[current_lvl - 1]; j++) {
    if (diamonds[j].is_visible && iCheckCollision(&player.sprite, &diamonds[j].sprite)) {
        diamonds[j].is_visible = 0; // hide the diamond
        diamond_collected++;        // increment count
        update_diamonds();          // update file/data if needed
        update_health(-10);
        // Optional: play sound or show sparkle effect
        printf("Diamond collected at (%d, %d)\n", diamonds[j].sprite.x, diamonds[j].sprite.y);
    }
}

}