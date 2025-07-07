#include "iGraphics.h"
#include "MazeExplorer/VolumeSlider.h"


void iDraw() {
    iClear();
    drawVolumeSlider();  // Draws the volume slider
}

void iMouseMove(int mx, int my) {
    volumeSliderMouseMove(mx, my);
}

void iMouse(int button, int state, int mx, int my) {
    volumeSliderMouse(button, state, mx, my);
}
