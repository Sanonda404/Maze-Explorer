#ifndef SIGNUP_H
#define SIGNUP_H

#include "iGraphics.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "iFont.h"
#include "MazeExplorer/level_dependencies.h"

//==================== Player Info ======================
struct Player_Info
{
    char name[100];
    int max_lvl;
    int highscores[6];
    float music_volume;
    float sfx_volume;
    int selected_character;
};

Player_Info new_player = {"", 1, {0, 0, 0, 0, 0, 0}, 1.0f, 1.0f, 0};
bool input_done = false;
bool name_taken = false;
bool returning_player = false;

char input_name[100];
int name_len = 0;

int button_x = 600, button_y = 500, button_w = 100, button_h = 40;

//==================== Volume Settings ======================
int slider_w = 200, slider_h = 6, knob_r = 15;

// Music Volume
int music_slider_x = 300, music_slider_y = 420;
float music_volume = 1.0f, current_music_volume = 1.0f;
bool dragging_music = false;

// SFX Volume
int sfx_slider_x = 300, sfx_slider_y = 360;
float sfx_volume = 1.0f, current_sfx_volume = 1.0f;
bool dragging_sfx = false;

//data appended
bool appended_data = false;

//==================== Character Selection ======================
const int TOTAL_CHARACTERS = 5;
int selected_character = 0;
int character_img_ids[TOTAL_CHARACTERS];
Image chars[5];
const char *char_paths[5] = {
    "MazeExplorer/assests/player/character_down.png",
    "MazeExplorer/assests/player/character1_down.png",
    "MazeExplorer/assests/player/character2_down.png",
    "MazeExplorer/assests/player/character3_down.png",
    "MazeExplorer/assests/player/character_down.png"};

void load_characters()
{
    for (int i = 0; i < TOTAL_CHARACTERS; i++)
    {
        character_img_ids[i] = iLoadImage(&chars[i], char_paths[i]);
    }
}

//==================== Font Paths ======================
const char *font_title = "MazeExplorer/assests/fonts/Pacifico-Regular.ttf";
const char *font_label = "MazeExplorer/assests/fonts/Poppins-Regular.ttf";
const char *font_button = "MazeExplorer/assests/fonts/Roboto-Bold.ttf";

//==================== Sound Hooks ======================
void setMusicVolume(float v)
{
    // implement your audio engine hook here
}
void setSFXVolume(float v)
{
    // implement your audio engine hook here
}

//==================== Name Existence Check ======================
bool name_exists(char name[])
{
    FILE *fptr = fopen("MazeExplorer/saves/info.txt", "r");
    if (!fptr)return false;

    char line[512];
    while (fgets(line, sizeof(line), fptr))
    {
        char existing_name[100];
        int level, hs[6], char_id;
        float mv, sv;
        sscanf(line, "%s %d %d %d %d %d %d %d %f %f %d",
               existing_name, &level,
               &hs[0], &hs[1], &hs[2], &hs[3], &hs[4], &hs[5],
               &mv, &sv, &char_id);
        if (strcmp(name, existing_name) == 0)
        {
            strcpy(new_player.name, existing_name);
            new_player.max_lvl = level;
            memcpy(new_player.highscores, hs, sizeof(hs));
            new_player.music_volume = mv;
            new_player.sfx_volume = sv;
            new_player.selected_character = char_id;
            music_volume = current_music_volume = mv;
            sfx_volume = current_sfx_volume = sv;
            selected_character = char_id;
            fclose(fptr);
            return true;
        }
    }
    fclose(fptr);
    return false;
}

void update_info(char player_name[]) {
    FILE *fptr = fopen("MazeExplorer/saves/info.txt", "r");
    if (!fptr) {
        printf("Failed to open file for reading.\n");
        return;
    }

    Player_Info players[100]; // Max 100 players
    int count = 0;
    while (fscanf(fptr, "%s %d %d %d %d %d %d %d %f %f %d",
                  players[count].name,
                  &players[count].max_lvl,
                  &players[count].highscores[0],
                  &players[count].highscores[1],
                  &players[count].highscores[2],
                  &players[count].highscores[3],
                  &players[count].highscores[4],
                  &players[count].highscores[5],
                  &players[count].music_volume,
                  &players[count].sfx_volume,
                  &players[count].selected_character) == 11) {
        count++;
    }
    fclose(fptr);

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (strcmp(players[i].name, player_name) == 0) {
            found = true;
            players[i].music_volume = new_player.music_volume;
            players[i].sfx_volume = new_player.sfx_volume;
            players[i].selected_character = new_player.selected_character;
            break;
        }
    }

    if (!found) {
        printf("Player not found.\n");
        return;
    }

    fptr = fopen("MazeExplorer/saves/info.txt", "w");
    if (!fptr) {
        printf("Failed to open file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fptr, "%s %d %d %d %d %d %d %d %.2f %.2f %d\n",
                players[i].name,
                players[i].max_lvl,
                players[i].highscores[0],
                players[i].highscores[1],
                players[i].highscores[2],
                players[i].highscores[3],
                players[i].highscores[4],
                players[i].highscores[5],
                players[i].music_volume,
                players[i].sfx_volume,
                players[i].selected_character);
    }

    fclose(fptr);
    printf("Info updated.\n");
}


//==================== Save Player Data ======================
void append_data()
{
    strcpy(new_player.name, input_name);
    new_player.music_volume = music_volume;
    new_player.sfx_volume = sfx_volume;
    new_player.selected_character = selected_character;

    if (name_taken)
    {
        update_info(new_player.name);
        return;
    }

    FILE *fptr = fopen("MazeExplorer/saves/info.txt", "a");
    if (fptr)
    {
        fprintf(fptr, "%s %d %d %d %d %d %d %d %.2f %.2f %d\n",
                new_player.name, new_player.max_lvl,
                new_player.highscores[0], new_player.highscores[1],
                new_player.highscores[2], new_player.highscores[3],
                new_player.highscores[4], new_player.highscores[5],
                new_player.music_volume, new_player.sfx_volume, new_player.selected_character);
        fclose(fptr);
        input_done = true;
    }
    appended_data=true;
}

//==================== Draw Signup Screen ======================
void draw_signup()
{
    // Background
    iSetColor(50, 10, 10);
    iFilledRectangle(0, 0, 1400, 800);

    // === Volume Animation Logic ===
    if (dragging_music)
        current_music_volume = music_volume;
    else
        current_music_volume += (music_volume - current_music_volume) * 0.15f;

    if (dragging_sfx)
        current_sfx_volume = sfx_volume;
    else
        current_sfx_volume += (sfx_volume - current_sfx_volume) * 0.15f;

    // Title Shadow
    iSetTransparentColor(0, 0, 0, 0.4);
    iShowText(402, 652, "Maze Explorer", font_title, 50);

    // Title
    iSetColor(255, 255, 255);
    iShowText(400, 650, "Maze Explorer", font_title, 50);

    if (input_done)
    {
        char msg[100];
        if(name_taken){
            sprintf(msg, "Welcome back %s!",new_player.name);
        }
        else{
            sprintf(msg, "Hello %s!",new_player.name);
        }
        iSetColor(255, 255, 180);
        iShowText(300, 570, msg, font_label, 24);
    }
    else
    {
        iSetColor(200, 200, 255);
        iShowText(300, 570, "Enter Your Name:", font_label, 24);

        iSetColor(255, 255, 255);
        iFilledRectangle(300, 500, 250, 40);
        iSetColor(180, 180, 255);
        iRectangle(300, 500, 250, 40);
        iSetColor(50, 50, 50);
        iShowText(310, 510, input_name, font_label, 22);
    }

    // OK Button
    if(!input_done){
        iSetColor(80, 255, 100);
        for (int r = 0; r < 3; r++)
            iRectangle(button_x - r, button_y - r, button_w + r * 2, button_h + r * 2);
        iSetColor(50, 205, 50);
        iFilledRectangle(button_x, button_y, button_w, button_h);
        iSetColor(0, 0, 0);
        iShowText(button_x + 28, button_y + 10, "OK", font_button, 22);
    }
    
    if(input_done){
        // === Character Selector ===
        int char_x = 950, char_y = 300, char_w = 200, char_h = 200;

        // Title
        iSetColor(200, 200, 255);
        iShowText(char_x, char_y + char_h + 40, "Select Character", font_label, 22);

        // Border Box
        iSetColor(180, 180, 255);
        iRectangle(char_x - 5, char_y - 5, char_w + 10, char_h + 10);

        // Character Image
        iShowImage(char_x, char_y,char_paths[selected_character], char_w, char_h);

        // Navigation Buttons
        iSetColor(255, 255, 255);
        iFilledRectangle(char_x - 40, char_y + 90, 30, 30); // left
        iFilledRectangle(char_x + char_w + 10, char_y + 90, 30, 30); // right

        iSetColor(0, 0, 0);
        iShowText(char_x - 35, char_y + 95, "<", font_button, 24);
        iShowText(char_x + char_w + 15, char_y + 95, ">", font_button, 24);

        // Select Button
        // Select / Selected Button
        bool is_current = (selected_character == new_player.selected_character);
        iSetColor(is_current ? 100 : 80, is_current ? 255 : 200, is_current ? 100 : 255);
        iFilledRectangle(char_x + 40, char_y - 50, 120, 35);
        iSetColor(0, 0, 0);
        iShowText(char_x + 50, char_y - 42, is_current ? "Selected" : "Select", font_button, 20);

        // Done Button
        iSetColor(80, 255, 100);
        iSetColor(50, 205, 50);
        iFilledRectangle(button_x, button_y-400, button_w+20, button_h+20);
        iSetColor(0, 0, 0);
        iShowText(button_x + 28, button_y -400 + 20, "Done", font_button, 30); 
    }
    


    if (input_done)
    {
        // Music Slider
        iSetColor(200, 200, 255);
        iShowText(music_slider_x, music_slider_y + 25, "Music Volume", font_label, 18);
        iSetColor(180, 180, 180);
        iFilledRectangle(music_slider_x, music_slider_y, slider_w, slider_h);
        int mx = music_slider_x + (int)(current_music_volume * slider_w);
        iSetColor(255, 255, 255);
        iFilledCircle(mx, music_slider_y + slider_h / 2, knob_r);
        iSetColor(100, 255, 100);
        iCircle(mx, music_slider_y + slider_h / 2, knob_r);

        // SFX Slider
        iSetColor(200, 200, 255);
        iShowText(sfx_slider_x, sfx_slider_y + 25, "SFX Volume", font_label, 18);
        iSetColor(180, 180, 180);
        iFilledRectangle(sfx_slider_x, sfx_slider_y, slider_w, slider_h);
        int sx = sfx_slider_x + (int)(current_sfx_volume * slider_w);
        iSetColor(255, 255, 255);
        iFilledCircle(sx, sfx_slider_y + slider_h / 2, knob_r);
        iSetColor(100, 255, 100);
        iCircle(sx, sfx_slider_y + slider_h / 2, knob_r);

        // Volume Labels
        char vol_text[20];
        sprintf(vol_text, "%d%%", (int)(music_volume * 100));
        iSetColor(255, 255, 255);
        iShowText(music_slider_x + slider_w + 20, music_slider_y - 2, vol_text, font_label, 16);
        sprintf(vol_text, "%d%%", (int)(sfx_volume * 100));
        iShowText(sfx_slider_x + slider_w + 20, sfx_slider_y - 2, vol_text, font_label, 16);
    }
}

#endif
