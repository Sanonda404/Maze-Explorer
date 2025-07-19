#include "iGraphics.h"
#include <bits/stdc++.h>
int highscore = 0;

int score[] = {1000, 1200, 1500, 2000, 2500, 3500};
const char *filename = "MazeExplorer/saves/highscore.txt";

// Load high score from file
void loadHighScore(int current_lvl) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char line[1000];
        int line_no = 0;
        while(fgets(line, 1000, file)!=NULL){
            line_no++;
            if(line_no==current_lvl){
                highscore = fscanf(file, "%d", &highscore);
                break;
            }
        }
        fclose(file);
    } else {
        highscore = 0;
    }
}

// Save new high score if it's higher
void saveHighScore(int score, int current_lvl) {
    loadHighScore(current_lvl);
    if (score > highscore) {
        FILE *file = fopen(filename, "r+");
        if (file != NULL) {
            char line[1000];
            int line_no = 0;
            while(fgets(line, 1000, file)!=NULL){
                line_no++;
                if(line_no==current_lvl){
                    fprintf(file, "%d", score);
                    break;
                }
            }
            fclose(file);
            highscore = score;
        }
    }
}

void update_score(string type, int current_lvl)
{
    if(type=="kill_monster"){
        score[current_lvl-1]+=50;
    }
}

void calc_score(int time, int health, int current_lvl)
{
    score[current_lvl-1] -= time/90;
    score[current_lvl-1]  -= (100-health)*5;
    score[current_lvl-1]  = max(10,score[current_lvl-1]);
    saveHighScore(score[current_lvl-1], current_lvl);
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
