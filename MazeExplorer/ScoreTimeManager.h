#include "iGraphics.h"
#include <bits/stdc++.h>
#include "MazeExplorer/Signup.h"
#include <bits/stdc++.h>
int highscore = 0;

int score[] = {2000, 3200, 3500, 4000, 4500, 5500};

void update_score(string type, int current_lvl)
{
    if(type=="kill_monster"){
        score[current_lvl-1]+=50;
    }
}

void update_highscore(char player_name[], int level, int new_score) {
    if (level < 1 || level > 6) {
        printf("Invalid level number. Must be 1-6.\n");
        return;
    }

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
        printf("XXPlayer not found.\n");
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
    printf("Highscore updated.\n");
}

int get_highscore(char player_name[], int level) {
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
    int max_lvl, scores[6], selected_char;
    float music, sfx;

    while (fscanf(fptr, "%s %d %d %d %d %d %d %d %f %f %d",
                  name,
                  &max_lvl,
                  &scores[0], &scores[1], &scores[2],
                  &scores[3], &scores[4], &scores[5],
                  &music, &sfx, &selected_char) == 11) {

        // Debug print
        // printf("Looking for [%s], Found [%s]\n", player_name, name);

        if (strcmp(name, player_name) == 0) {
            fclose(fptr);
            return scores[level - 1]; // 1-based level
        }
    }

    fclose(fptr);
    printf("Player '%s' not found in file.\n", player_name);
    return -1;
}


void calc_score(int time, int health, int current_lvl, char player_name[])
{
    score[current_lvl-1] -= time/90;
    score[current_lvl-1]  -= (100-health)*5;
    score[current_lvl-1]  = max(10,score[current_lvl-1]);
    highscore = get_highscore(player_name,current_lvl);
    printf("iS %d",get_highscore("Sanonda",1));
    if(score[current_lvl-1]>highscore){
        update_highscore(player_name,current_lvl,score[current_lvl-1]);
        highscore = score[current_lvl-1];
    }
}

void display_highscore(int x, int y, int current_lvl)
{
    char highscore_txt[50];
    char score_txt[50];
    //printf("%d",highscore);
    sprintf(highscore_txt, "High Score: %d", highscore);
    sprintf(score_txt, "Score: %d", score[current_lvl-1]);
    //cout<<score_txt<<endl;

    iSetColor(255,255,255);
    iText(x, y, score_txt, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(x, y-30, highscore_txt, GLUT_BITMAP_TIMES_ROMAN_24);
}

//loadHighScore();       // Load existing high score
//saveHighScore(score);  // Save if current score is higher

//printf("High Score: %d\n", highscore);
