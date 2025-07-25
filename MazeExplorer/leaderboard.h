#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "iGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iFont.h"

#define MAX_PLAYERS 100
#define MAX_DISPLAY 10

typedef struct
{
    char name[100];
    int max_lvl;
    int highscores[6];
    float music_volume;
    float sfx_volume;
    int selected_character;
} Player_Infos;

typedef struct {
    char name[100];
    int score;
} LeaderEntry;

Player_Infos players[MAX_PLAYERS];
int player_count = 0;
int current_level2 = 1;
LeaderEntry leaderboard[MAX_DISPLAY];

int back_btn_x = 50, back_btn_y = 700, back_btn_w = 100, back_btn_h = 40;

float alpha2 = 0;
bool transitioning = false;
int transition_step = 0;

int compare_scores(const void *a, const void *b) {
    return ((LeaderEntry *)b)->score - ((LeaderEntry *)a)->score;
}

int load_players() {
    FILE *fptr = fopen("MazeExplorer/saves/info.txt", "r");
    if (!fptr) {
        printf("Failed to open info.txt\n");
        return 0;
    }

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
        if (count >= MAX_PLAYERS) break;
    }

    fclose(fptr);
    return count;
}

void generate_leaderboard(int level) {
    for (int i = 0; i < MAX_DISPLAY; i++) {
        leaderboard[i].score = 0;
        strcpy(leaderboard[i].name, "---");
    }

    LeaderEntry temp[MAX_PLAYERS];
    int count = 0;
    for (int i = 0; i < player_count; i++) {
        temp[count].score = players[i].highscores[level - 1];
        strcpy(temp[count].name, players[i].name);
        count++;
    }

    qsort(temp, count, sizeof(LeaderEntry), compare_scores);

    for (int i = 0; i < MAX_DISPLAY && i < count; i++) {
        leaderboard[i] = temp[i];
    }
}

void draw_back_button() {
    iSetTransparentColor(220, 80, 80, alpha2);
    iFilledRectangle(back_btn_x, back_btn_y, back_btn_w, back_btn_h);
    iSetTransparentColor(255, 255, 255, alpha2);
    iShowText(back_btn_x + 20, back_btn_y + 12, "Back", "MazeExplorer/assests/fonts/Poppins-Regular.ttf", 18);
}

void draw_leaderboard() {
    int box_width = 700;
    int box_height = 600;
    int box_x = (1400 - box_width) / 2;
    int box_y = (800 - box_height) / 2;

    char title[50];
    sprintf(title, "Leaderboard - Level %d", current_level2);
    iSetTransparentColor(255, 215, 0, alpha2);
    iShowText(box_x + box_width / 2 - 160, box_y + box_height + 50, title, "MazeExplorer/assests/fonts/DynaPuff-Medium.ttf", 50);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glColor4f(1, 1, 1, 1);
    iSetTransparency(1.0);

    iSetTransparentColor(180, 180, 180, alpha2);
    iFilledRectangle(box_x, box_y, box_width, box_height);

    for (int i = 0; i < MAX_DISPLAY; i++) {
        int y = box_y + box_height - 80 - i * 50;
        iSetTransparentColor(220 - i * 10, 230 - i * 15, 255 - i * 10, alpha2);
        iFilledRectangle(box_x + 10, y, box_width - 20, 40);

        iSetTransparentColor(20, 20, 20, alpha2);
        char line[200];
        sprintf(line, "%2d. %-15s  Score: %d", i + 1, leaderboard[i].name, leaderboard[i].score);
        iShowText(box_x + 30, y + 10, line, "MazeExplorer/assests/fonts/Poppins-Regular.ttf", 22);
    }

    iSetTransparentColor(100, 255, 100, alpha2);
    iShowText(box_x + 80, box_y - 40, "Use LEFT/RIGHT arrows to change level", "MazeExplorer/assests/fonts/Poppins-Regular.ttf", 16);

    draw_back_button();
}

void leaderboard_transition(int page_no) {
    if (transitioning) {
        if (page_no != 12) {
            alpha2 -= 0.05;
            if (alpha2 <= 0.0) {
                alpha2 = 0.0;
                transitioning = false;
            }
        } else {
            alpha2 += 0.05;
            if (alpha2 >= 1.0) {
                alpha2 = 1.0;
                transitioning = false;
            }
        }
    }
}

#endif
