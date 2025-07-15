#include "iGraphics.h"
#include <bits/stdc++.h>
int highscore = 0;

int score = 1000;
const char *filename = "MazeExplorer/saves/highscore.txt";

// Load high score from file
void loadHighScore() {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fscanf(file, "%d", &highscore);
        fclose(file);
    } else {
        highscore = 0;
    }
}

// Save new high score if it's higher
void saveHighScore(int score) {
    loadHighScore();
    if (score > highscore) {
        FILE *file = fopen(filename, "w");
        if (file != NULL) {
            fprintf(file, "%d\n", score);
            fclose(file);
            highscore = score;
        }
    }
}

void update_score(string type)
{
    if(type=="kill_monster"){
        score+=50;
    }
}

void calc_score(int time, int health)
{
    score -= time/90;
    score -= (100-health)*5;
    score = max(10,score);
    saveHighScore(score);
}

void display_highscore(int x, int y)
{
    char highscore_txt[50];
    char score_txt[50];
    //printf("%d",highscore);
    sprintf(highscore_txt, "High Score: %d", highscore);
    sprintf(score_txt, "Score: %d", score);
    //cout<<score_txt<<endl;

    iSetColor(255,255,255);
    iText(x, y, score_txt, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(x, y-30, highscore_txt, GLUT_BITMAP_TIMES_ROMAN_24);
}

//loadHighScore();       // Load existing high score
//saveHighScore(score);  // Save if current score is higher

//printf("High Score: %d\n", highscore);
