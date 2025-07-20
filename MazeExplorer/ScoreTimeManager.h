#include "iGraphics.h"
#include <bits/stdc++.h>
#include "MazeExplorer/Signup.h"
#include <bits/stdc++.h>
int highscore = 0;

int score[] = {1000, 1200, 1500, 2000, 2500, 3500};

void update_score(string type, int current_lvl)
{
    if(type=="kill_monster"){
        score[current_lvl-1]+=50;
    }
}

void calc_score(int time, int health, int current_lvl, char * player_name)
{
    score[current_lvl-1] -= time/90;
    score[current_lvl-1]  -= (100-health)*5;
    score[current_lvl-1]  = max(10,score[current_lvl-1]);
    highscore = get_highscore(player_name,current_lvl);
    if(score[current_lvl-1]>highscore){
        update_highscore(player_name,current_lvl,score[current_lvl-1]);
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
