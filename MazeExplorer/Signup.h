#ifndef SIGNUP_H
#define SIGNUP_H

#include "iGraphics.h"
#include <cstring>
#include <cstdio>

struct Player_Info {
    char name[100];
    int max_lvl;
    int highscores[6];
};

Player_Info new_player = {"", 1, {0, 0, 0, 0, 0, 0}};
bool input_done = false;
bool name_taken = false;

char input_name[100] = "";
int name_len = 0;

int button_x = 600, button_y = 500, button_w = 100, button_h = 40;

bool name_exists(const char *name) {
    FILE *fptr = fopen("MazeExplorer/saves/info.txt", "r");
    if (!fptr) return false;

    char line[256];
    while (fgets(line, sizeof(line), fptr)) {
        char existing_name[100];
        sscanf(line, "%s", existing_name);
        if (strcmp(existing_name, name) == 0) {
            fclose(fptr);
            return true;
        }
    }
    fclose(fptr);
    return false;
}


void append_data(char * player_name) {
    player_name = input_name;
    if (name_exists(input_name)) {
        name_taken = true;
        return;
    }
    FILE *fptr = fopen("MazeExplorer/saves/info.txt", "a");
    if (fptr) {
        fprintf(fptr, "%s %d %d %d %d %d %d %d\n", 
            new_player.name, new_player.max_lvl,
            new_player.highscores[0], new_player.highscores[1],
            new_player.highscores[2], new_player.highscores[3],
            new_player.highscores[4], new_player.highscores[5]);
        fclose(fptr);
        input_done = true;
    }
}

void draw_signup() {
    iSetColor(255, 255, 255);
    iText(300, 550, "Enter Your Name:", GLUT_BITMAP_HELVETICA_18);
    iRectangle(300, 500, 250, 30);
    iText(310, 510, input_name, GLUT_BITMAP_HELVETICA_18);

    iSetColor(0, 255, 0);
    iFilledRectangle(button_x, button_y, button_w, button_h);
    iSetColor(0, 0, 0);
    iText(button_x + 30, button_y + 12, "OK", GLUT_BITMAP_HELVETICA_18);
}

#endif