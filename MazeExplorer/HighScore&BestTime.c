#include <stdio.h>

void saveHighScore(int currentScore)
{
    int highScore = loadHighScore();

    if (currentScore > highScore)
    {
        FILE *file = fopen("highscore.txt", "w");
        if (file != NULL)
        {
            fprintf(file, "%d", currentScore);
            fclose(file);
        }
    }
}

int loadHighScore()
{
    int highScore = 0;
    FILE *file = fopen("highscore.txt", "r");

    if (file != NULL)
    {
        fscanf(file, "%d", &highScore);
        fclose(file);
    }

    return highScore;
}

void saveBestTime(double currentTime)
{
    double bestTime = loadBestTime();

    if (bestTime == 0 || currentTime < bestTime)
    {
        FILE *file = fopen("besttime.txt", "w");
        if (file != NULL)
        {
            fprintf(file, "%.2f", currentTime);
            fclose(file);
        }
    }
}

double loadBestTime()
{
    double bestTime = 0;
    FILE *file = fopen("besttime.txt", "r");

    if (file != NULL)
    {
        fscanf(file, "%lf", &bestTime);
        fclose(file);
    }

    return bestTime;
}

