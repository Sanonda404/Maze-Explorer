
// VolumeSlider.h
#include "iGraphics.h"

int sliderX = 500, sliderY = 400;
int sliderWidth = 300, sliderHeight = 10;
int handleRadius = 10;
int handleX =sliderX+sliderWidth;
int isDragging = 1;
float volume = 1.0f;

Image ok_button;

void load_settings()
{
    iLoadImage(&ok_button, "MazeExplorer/assests/levels/button2.png");
    //iScaleImage(&ok_button, 0.1);

}
Mix_Music *bgMusic = NULL;

void initAudio() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    bgMusic = Mix_LoadMUS("background.mp3"); // Your music file
    Mix_PlayMusic(bgMusic, -1); // Loop music
}

void updateGameVolume() {
    Mix_VolumeMusic((int)(volume * MIX_MAX_VOLUME)); // Connect to your volume slider
}

void stopAudio() {
    Mix_FreeMusic(bgMusic);
    Mix_CloseAudio();
}


void drawVolumeSlider()
{
    iShowImage(1000, 100,"MazeExplorer/assests/levels/button2.png");//ok button
    iSetColor(0,0,0);
    iText(1060,120,"Ok",GLUT_BITMAP_TIMES_ROMAN_24 );

    iSetColor(200, 200, 200);
    iFilledRectangle(sliderX, sliderY, sliderWidth, sliderHeight);

    iSetColor(50, 150, 250);
    iFilledCircle(handleX, sliderY + sliderHeight / 2, handleRadius);

    char volText[20];
    sprintf(volText, "Volume: %.0f%%", volume * 100);
    iSetColor(255, 255, 255);
    iText(sliderX, sliderY + 25, volText, GLUT_BITMAP_HELVETICA_18);
}

bool volumeSliderMouse(int mx, int my)
{
    int centerY = sliderY + sliderHeight / 2;
    int dist = (mx - handleX) * (mx - handleX) + (my - centerY) * (my - centerY);
    if (dist <= handleRadius * handleRadius) {
        return true;
    }
    return false;
}

void volumeSliderMouseMove(int mx, int my)
{
    if (isDragging && volumeSliderMouse(mx,my)) {
        if (mx >= sliderX && mx <= sliderX + sliderWidth) {
            handleX = mx;
            volume = (float)(handleX - sliderX) / sliderWidth;
            printf("%f\n",volume);
        }
    }
}

float check_ok_pressed(float v, int mx, int my,int &page_no, int &pre_page)
{
    printf("%d %d\n",mx,my);
    if(mx>=100 && mx<=1150 && my>=100 && my<=150){
        printf("ok");
        page_no = pre_page;
        return volume;
    }
    return v;
}

