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

void update_highscore(const char *player_name, int level, int new_score) {
    if (level < 1 || level > 6) {
        printf("Invalid level number. Must be 1–6.\n");
        return;
    }

    FILE *fptr = fopen("MazeExplorer/saves/info.txt", "r");
    if (!fptr) {
        printf("Failed to open file for reading.\n");
        return;
    }

    Player_Info players[100]; // Max 100 players
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
    }
    fclose(fptr);

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (strcmp(players[i].name, player_name) == 0) {
            found = true;
            if (new_score > players[i].highscores[level - 1]) {
                players[i].highscores[level - 1] = new_score;
            }
            if (level > players[i].max_lvl) {
                players[i].max_lvl = level;
            }
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
        fprintf(fptr, "%s %d %d %d %d %d %d %d\n",
                players[i].name,
                players[i].max_lvl,
                players[i].highscores[0],
                players[i].highscores[1],
                players[i].highscores[2],
                players[i].highscores[3],
                players[i].highscores[4],
                players[i].highscores[5]);
    }

    fclose(fptr);
    printf("Highscore updated.\n");
}

int get_highscore(const char *player_name, int level) {
    if (level < 1 || level > 6) {
        printf("Invalid level. Must be between 1 and 6.\n");
        return -1;
    }

    FILE *fptr = fopen("MazeExplorer/saves/info.txt", "r");
    if (!fptr) {
        printf("Failed to open file.\n");
        return -1;
    }

    char name[100];
    int max_lvl, scores[6];

    while (fscanf(fptr, "%s %d %d %d %d %d %d %d",
                  name,
                  &max_lvl,
                  &scores[0], &scores[1], &scores[2],
                  &scores[3], &scores[4], &scores[5]) == 8) {
        if (strcmp(name, player_name) == 0) {
            fclose(fptr);
            return scores[level - 1];  // level is 1-based
        }
    }

    fclose(fptr);
    printf("Player not found.\n");
    return -1;
}


void append_data(char * player_name) {
    player_name = input_name;
    if (name_exists(input_name)) {
        name_taken = true;
        return;
    }
    update_highscore("Sanonda",2,200);
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