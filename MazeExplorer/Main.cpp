#include "iGraphics.h"
#include "MazeExplorer/level_dependencies.h"
#include "MazeExplorer/firstSceen.h"
#include "MazeExplorer/menu.h"
#include "MazeExplorer/level1.h"
#include "MazeExplorer/level2.h"
#include "MazeExplorer/level3.h"
#include "MazeExplorer/level4.h"
#include "MazeExplorer/level5.h"
#include "MazeExplorer/level6.h"
#include "MazeExplorer/Signup.h"
#include "MazeExplorer/leaderboard.h"
#include "MazeExplorer/credits.h"

void load_resources()
{
    load_settings();
    fs_load_resources();
    menu_load_resources();
    load_level_resources();
    lvl1_load_resources();
    lvl2_load_resources();
    lvl3_load_resources();
    lvl4_load_resources();
    lvl5_load_resources();
    lvl6_load_resources();
}

/*
function iDraw() is called again and again by the system.
*/
void iDraw()
{
    // place your drawing codes here
    iClear();

    // drawVolumeSlider();

    if ((page_no == 0 || trnstn) && !transitioning)
    {
        iSetTransparentColor(0,0,0,1);
        draw_firstPage();
    }
    else if ((page_no == 1 || menu_trnstn) && !transitioning)
    {
        draw_menu();
    }
    else if (page_no == 2)
    {
        draw_lvl1();
    }
    else if (page_no == 3)
    {
        draw_lvl2();
    }
    else if (page_no == 4)
    {
        draw_lvl3();
    }
    else if (page_no == 5)
    {
        draw_lvl4();
    }
    else if (page_no == 6)
    {
        draw_lvl5();
    }
    else if (page_no == 7)
    {
        draw_lvl6();
    }
    // settings page
    else if (page_no == 11)
    {
       draw_signup();
    }

    else if ((page_no == 12 || transitioning) && !trnstn && !menu_trnstn)
    {
        draw_leaderboard();
    }

    else if(page_no==13 && show_credit){ 
        draw_credit();

    }

    if (!trnstn && !menu_trnstn && page_no >= 2 && page_no <= 7)
    {
        started = true;
        draw_levels();
    }

    else{
        started = false;
    }

    check_collision1();
    check_collision2();
    check_collision3();
    check_collision4();
    check_collision5();
    check_collision6();
    obstacle_collision();
}

void animate()
{
    if (trnstn)
        play_transition();

    if (menu_trnstn)
        menu_play_transition();

    if (transitioning)
        leaderboard_transition(page_no);

    animate_levels();

    if(lvl_completed){
        update_typing_animation();
        reveal_buttons_step();
    }
}

/*
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    // place your codes here
    if(lvl_completed)level_complete_mouse_move(mx,my);
    
}

/*
function iMouseDrag() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseDrag(int mx, int my)
{
    if (page_no == 11)
    {
        update_volume();
        if (dragging_music) {
        mx = std::max(music_slider_x, std::min(mx, music_slider_x + slider_w));
        music_volume = (float)(mx - music_slider_x) / slider_w;
    }
        if (dragging_sfx) {
            mx = std::max(sfx_slider_x, std::min(mx, sfx_slider_x + slider_w));
            sfx_volume = (float)(mx - sfx_slider_x) / slider_w;
        }
        //printf("Dragging Music: %d | Dragging SFX: %d | Music Vol: %.2f | SFX Vol: %.2f\n", 
        //dragging_music, dragging_sfx, music_volume, sfx_volume);
    }
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    // means clicked
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (page_no == 0)
            fs_check_button_pressed(mx, my, page_no);
        else if (page_no == 1)
            menu_check_button_pressed(mx, my, page_no);
        else if (page_no >= 2 && page_no <= 7)
        {
            check_paused_pressed(mx, my);
            check_lvl_completed_buttons(mx, my, page_no);
            check_pause_buttons(mx, my, page_no);
            check_lost_buttons(mx, my, page_no);
        }
        if (page_no == 10)
        {
            music_volume = check_ok_pressed(volume, mx, my, page_no, pre_page);
        }
        if(lvl_completed)level_complete_mouse_click(mx,my);
    }
    // ok button of settings
    if (page_no == 11 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (!input_done &&
            mx >= button_x && mx <= button_x + button_w &&
            my >= button_y && my <= button_y + button_h)
        {
            if (name_len > 0)
            {
                strcpy(new_player.name, input_name);
                //append_data();
                strcpy(player_name,input_name);
                input_done = true;
                if(name_exists(player_name)){
                    name_taken=true;
                    update_volume();
                }
                //page_no = pre_page;
            }
        }
        else {
            int char_x = 950, char_y = 300, char_w = 200;

            // Left arrow
            if (mx >= char_x - 40 && mx <= char_x - 10 && my >= char_y + 90 && my <= char_y + 120) {
                selected_character = (selected_character - 1 + TOTAL_CHARACTERS) % TOTAL_CHARACTERS;
                printf("%d",selected_character);
            }

            // Right arrow
            if (mx >= char_x + char_w + 10 && mx <= char_x + char_w + 40 && my >= char_y + 90 && my <= char_y + 120) {
                selected_character = (selected_character + 1) % TOTAL_CHARACTERS;
                printf("%d",selected_character);
            }

            // Select Button
            if (mx >= char_x + 40 && mx <= char_x + 160 && my >= char_y - 50 && my <= char_y - 15) {
                new_player.selected_character = selected_character;
            }

            // Done Button
            if (mx >= button_x && mx <= button_x + button_w + 20 && my >= button_y - 400 && my <= button_y - 400 + button_h + 20) {
                printf("Done\n");
                append_data();
                max_lvl = max_lvl2;
                page_no = pre_page;
                printf("%d\n",new_player.selected_character);
            }
        }

    }

    if (page_no==11 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // --- Music knob detection ---
        int cx = music_slider_x + (int)(music_volume * slider_w);
        int cy = music_slider_y + slider_h / 2;
        int dx = mx - cx;
        int dy = my - cy;
        if (dx * dx + dy * dy <= knob_r * knob_r) {
            dragging_music = true;
        }

        // --- SFX knob detection ---
        cx = sfx_slider_x + (int)(sfx_volume * slider_w);
        cy = sfx_slider_y + slider_h / 2;
        dx = mx - cx;
        dy = my - cy;
        if (dx * dx + dy * dy <= knob_r * knob_r) {
            dragging_sfx = true;
        }
    }

    if (page_no==11 && button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        dragging_music = false;
        dragging_sfx = false;
    }

    // back button of leader board
    if (page_no == 12 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (mx >= back_btn_x && mx <= back_btn_x + back_btn_w &&
            my >= back_btn_y && my <= back_btn_y + back_btn_h)
        {
            page_no = pre_page;
            transitioning = true;
        }
    }

    if(page_no==13)handle_credit_mouse(button,state, mx, my, page_no);
}

/*
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/

void iKeyboard(unsigned char key, int state)
{
    if(state==1)return;
    switch (key)
    {
    case ' ': // detecting attack
        if(!started)return;
        player.state = ATTACK;
        attacking = true;
        shoot_bullet(dir_name);
        break;
    // place your codes for other keys here
    default:
        break;
    }
    if(page_no==11 && !trnstn && !menu_trnstn){
        if (key == '\r' || key == '\n')
        {
            if (!input_done && name_len > 0)
            {
                strcpy(new_player.name, input_name);
                //append_data();
                strcpy(player_name,input_name);
                input_done = true;
                if(name_exists(player_name)){
                    name_taken=true;
                    update_volume();
                }
                //page_no = pre_page;
            }
        }
        else if (key == '\b')
        {
            if (name_len > 0)
            {
                name_len--;
                input_name[name_len] = '\0';
            }
        }
        else if (name_len < 99 && !input_done)
        {
            input_name[name_len++] = key;
            input_name[name_len] = '\0';
        }
    }
    
}

void iSpecialKeyboard(unsigned char key, int state)
{
    if(state==1)return;
    // for leader board
    if (page_no == 12)
    {
        if (key == GLUT_KEY_LEFT)
        {
            if (current_level2 > 1)
            {
                current_level2--;
                generate_leaderboard(current_level2);
            }
        }
        if (key == GLUT_KEY_RIGHT)
        {
            if (current_level2 < 6)
            {
                current_level2++;
                generate_leaderboard(current_level2);
            }
        }
        return;
    }

    // left arrow
    if (key == GLUT_KEY_LEFT)
    {
        if (dir_name != "left")
            direction_changed = true;

        dir_name = "left";

        move_player();

        if (player.state != WALK)
        {
            player.state = WALK;
        }

        // if(direction_changed){
        //  iChangeSpriteFrames(&player.sprite, player.walk_left, 4);
        //}
    }
    // right arrow
    if (key == GLUT_KEY_RIGHT)
    {
        if (dir_name != "right")
            direction_changed = true;

        dir_name = "right";

        move_player();

        if (player.state != WALK)
        {
            player.state = WALK;
        }

        // if(direction_changed){
        //     iChangeSpriteFrames(&player.sprite, player.walk_right, 4);
        // }
    }
    // Up arrow
    if (key == GLUT_KEY_UP)
    {
        if (dir_name != "up")
            direction_changed = true;

        dir_name = "up";

        move_player();

        if (player.state != WALK)
        {
            player.state = WALK;
        }

        // if(direction_changed){
        //     iChangeSpriteFrames(&player.sprite, player.walk_up, 4);
        // }
    }
    // down arrow
    if (key == GLUT_KEY_DOWN)
    {
        if (dir_name != "down")
            direction_changed = true;

        dir_name = "down";

        move_player();

        if (player.state != WALK)
        {
            player.state = WALK;
        }

        // if(direction_changed){
        //    iChangeSpriteFrames(&player.sprite, player.walk_down, 4);
        //}
    }
    // place your codes for other keys here
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    iInitializeFont();
    srand(time(0));
    init_sound();
    play_sound("bgm");

    load_resources();

    iSetTimer(20, animate);
    // place your own initialization codes here.

    iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Explorer");

    return 0;
}
