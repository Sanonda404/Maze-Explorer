#include "iGraphics.h"

int time_passed = 0;

void update_time()
{
    time_passed += 50;
    
}

void display_time()
{
    int s = time_passed / 1000;
    int m = s / 60;
    s %= 60;
    

    char timeText[100];
    sprintf(timeText, "%02d:%02d:%03d", m, s, time_passed % 1000); // format mm:ss:ms

    iSetColor(255,255,255);
    iText(50, 700, timeText);
}
