#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "iGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 100

typedef struct {
    char name[100];
    int max_lvl;
    int highscores[6];
} Player_Infos;

typedef struct {
    char name[100];
    int score;
} LeaderEntry;

Player_Infos players[MAX_PLAYERS];
int player_count = 0;
int current_level2 = 1;
LeaderEntry leaderboard[5];

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
    while (fscanf(fptr, "%s %d %d %d %d %d %d %d",
                  players[count].name,
                  &players[count].max_lvl,
                  &players[count].highscores[0],
                  &players[count].highscores[1],
                  &players[count].highscores[2],
                  &players[count].highscores[3],
                  &players[count].highscores[4],
                  &players[count].highscores[5]) == 8) {
        count++;
        if (count >= MAX_PLAYERS) break;
    }

    fclose(fptr);
    return count;
}

void generate_leaderboard(int level) {
    // Clear old entries
    for (int i = 0; i < 5; i++) {
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

    for (int i = 0; i < 5 && i < count; i++) {
        leaderboard[i] = temp[i];
    }
}

void draw_back_button() {
    iSetTransparentColor(220, 80, 80, alpha2);
    iFilledRectangle(back_btn_x, back_btn_y, back_btn_w, back_btn_h);
    iSetTransparentColor(255, 255, 255, alpha2);
    iText(back_btn_x + 20, back_btn_y + 12, "Back", GLUT_BITMAP_HELVETICA_18);
}

void draw_leaderboard() {
   // printf("%f",alpha2);
    int box_width = 600;
    int box_height = 400;
    int box_x = (1400 - box_width) / 2;
    int box_y = (800 - box_height) / 2;

    char title[50];
    sprintf(title, "Leaderboard - Level %d", current_level2);
    iSetTransparentColor(255, 215, 0, alpha2);
    iText(box_x + box_width / 2 - 90, box_y + box_height + 40, title, GLUT_BITMAP_HELVETICA_18);

    iSetTransparentColor(200, 200, 200, alpha2);
    iRectangle(box_x, box_y, box_width, box_height);

    for (int i = 0; i < 5; i++) {
        int y = box_y + box_height - 60 - i * 60;
        iSetTransparentColor(50 + i * 40, 100 + i * 30, 255 - i * 30, alpha2);
        iFilledRectangle(box_x + 10, y, box_width - 20, 50);

        iSetTransparentColor(0, 0, 0, alpha2);
        char line[200];
        sprintf(line, "%d. %-15s  Score: %d", i + 1, leaderboard[i].name, leaderboard[i].score);
        iText(box_x + 30, y + 15, line, GLUT_BITMAP_HELVETICA_18);
    }

    iSetTransparentColor(100, 255, 100, alpha2);
    iText(box_x + 80, box_y - 40, "Use LEFT/RIGHT arrows to change level", GLUT_BITMAP_HELVETICA_12);

    draw_back_button();
}

void leaderboard_transition(int page_no)
{
    if (transitioning) {
        if(page_no!=12){//back transiton/ fade out
            alpha2-=0.05;
            if(alpha2<=0.0){
                alpha2=0.0;
                transitioning = false;
            }
        }
        else{
           alpha2 += 0.05;
            if (alpha2 >= 1.0) {
                alpha2 = 1.0;
                transitioning = false;
            } 
        }
    }
}

#endif