#ifndef CREDIT_H
#define CREDIT_H

#include "iGraphics.h"
#include <cstring>
#include <cmath>
#include "iFont.h"

//==================== Background ======================
Image credit_bg;

//==================== Font Handles ======================
extern const char *font_title;
extern const char *font_label;
extern const char *font_button;

// Final Y positions for each section
const int TITLE_Y_FINAL = 600;
const int DEVS_Y_FINAL = 350;
const int DEV2_OFFSET = -190;   // second developer below first
const int SUP_Y_FINAL = 360;    // supervisor Y
const int SUP_X_POS = 900;      // supervisor X (right middle-ish)

// Animation timing constants (frames at ~60fps)
const int ANIM_DURATION = 10;  // ~0.42 sec per animation
const int WAIT_BETWEEN = 1;    // ~0.08 sec pause between steps
// Define button position and size 
const int BACK_BTN_X = 1100;
const int BACK_BTN_Y = 30;
const int BACK_BTN_WIDTH = 150;
const int BACK_BTN_HEIGHT = 50;

// Animation state variables
int credit_step = 0;      // 0: title, 1: developers, 2: supervisor, 3: done
int credit_timer = 0;

// Control credit screen visibility
bool show_credit = true;

// Load background image
void load_credit_resources() {
    iLoadImage(&credit_bg, "MazeExplorer/assests/bg_purple.png");
}

// Reset animation state
void reset_credit_animation() {
    credit_step = 0;
    credit_timer = 0;
}

// Helper function for smooth sliding animation from startY to endY over duration frames
int slideY(int startY, int endY, int timer, int duration) {
    if (timer >= duration) return endY;
    float t = (float)timer / duration;
    return startY + (int)((endY - startY) * t);
}

void draw_credit() {
    // Draw background
    iShowImage(0, 0, "MazeExplorer/assests/bg_purple.png", 1920, 900);

    credit_timer++;

    // --- Title Animation ---
    if (credit_step == 0) {
        int y = slideY(-100, TITLE_Y_FINAL, credit_timer, ANIM_DURATION);
        iSetColor(255, 255, 255);
        iShowText(1280 / 2 - 250, y, "MAZE EXPLORER", font_title, 64);
        if (credit_timer >= ANIM_DURATION + WAIT_BETWEEN) {
            credit_step = 1;
            credit_timer = 0;
        }
    } else {
        // Fixed title after animation
        iSetColor(255, 255, 255);
        iShowText(1280 / 2 - 250, TITLE_Y_FINAL, "MAZE EXPLORER", font_title, 64);
    }

    // --- Developers Animation ---
    if (credit_step == 1) {
        int y1 = slideY(-200, DEVS_Y_FINAL, credit_timer, ANIM_DURATION);
        int y2 = slideY(-200, DEVS_Y_FINAL + DEV2_OFFSET, credit_timer, ANIM_DURATION);

        // Developer 1
        iSetColor(255, 215, 0); // Gold for titles
        iShowText(100, y1 + 130, "Developer 1", font_button, 36);
        iSetColor(255, 255, 255);
        iShowText(100, y1 + 90, "Sanonda Deb", font_label, 28);
        iShowText(100, y1 + 60, "ID: 2405021", font_label, 28);
        iShowText(100, y1 + 30, "Section: A1", font_label, 28);
        iShowText(100, y1, "Level 1, Term 1", font_label, 28);

        // Developer 2
        iSetColor(255, 215, 0);
        iShowText(100, y2 + 130, "Developer 2", font_button, 36);
        iSetColor(255, 255, 255);
        iShowText(100, y2 + 90, "Zarrin Tasnim Ishra", font_label, 28);
        iShowText(100, y2 + 60, "ID: 2405015", font_label, 28);
        iShowText(100, y2 + 30, "Section: A1", font_label, 28);
        iShowText(100, y2, "Level 1, Term 1", font_label, 28);

        if (credit_timer >= ANIM_DURATION + WAIT_BETWEEN) {
            credit_step = 2;
            credit_timer = 0;
        }
    } else if (credit_step > 1) {
        // Fixed developers after animation
        int y1 = DEVS_Y_FINAL;
        int y2 = DEVS_Y_FINAL + DEV2_OFFSET;

        iSetColor(255, 215, 0);
        iShowText(100, y1 + 130, "Developer 1", font_button, 36);
        iSetColor(255, 255, 255);
        iShowText(100, y1 + 90, "Sanonda Deb", font_label, 28);
        iShowText(100, y1 + 60, "ID: 2405021", font_label, 28);
        iShowText(100, y1 + 30, "Section: A1", font_label, 28);
        iShowText(100, y1, "Level 1, Term 1", font_label, 28);

        iSetColor(255, 215, 0);
        iShowText(100, y2 + 130, "Developer 2", font_button, 36);
        iSetColor(255, 255, 255);
        iShowText(100, y2 + 90, "Zarrin Tasnim Ishra", font_label, 28);
        iShowText(100, y2 + 60, "ID: 2405015", font_label, 28);
        iShowText(100, y2 + 30, "Section: A1", font_label, 28);
        iShowText(100, y2, "Level 1, Term 1", font_label, 28);
    }

    // --- Supervisor Animation ---
    if (credit_step == 2) {
        int y = slideY(-200, SUP_Y_FINAL, credit_timer, ANIM_DURATION);

        iSetColor(255, 215, 0);
        iShowText(SUP_X_POS, y + 70, "Supervisor", font_button, 36);
        iSetColor(255, 255, 255);
        iShowText(SUP_X_POS, y + 30, "Sadat Hossian", font_label, 28);
        iShowText(SUP_X_POS, y, "CSE,BUET", font_label, 28);

        if (credit_timer >= ANIM_DURATION + WAIT_BETWEEN) {
            credit_step = 3;  // animation done
            credit_timer = 0;
        }
    } else if (credit_step > 2) {
        // Fixed supervisor after animation
        iSetColor(255, 215, 0);
        iShowText(SUP_X_POS, SUP_Y_FINAL + 70, "Supervisor", font_button, 36);
        iSetColor(255, 255, 255);
        iShowText(SUP_X_POS, SUP_Y_FINAL + 30, "Sadat Hossian", font_label, 28);
        iShowText(SUP_X_POS, SUP_Y_FINAL, "CSE,BUET", font_label, 28);
    }

    // Draw Back Button rectangle (purple)
iSetColor(128, 0, 128); // Purple color
iFilledRectangle(BACK_BTN_X, BACK_BTN_Y, BACK_BTN_WIDTH, BACK_BTN_HEIGHT);

// Draw button label (white)
iSetColor(255, 255, 255);
iShowText(BACK_BTN_X + 40, BACK_BTN_Y + 15, "Back", font_button, 28);

}

void handle_credit_mouse(int button, int state, int mx, int my, int &page_no) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (mx >= BACK_BTN_X && mx <= BACK_BTN_X + BACK_BTN_WIDTH &&
            my >= BACK_BTN_Y && my <= BACK_BTN_Y + BACK_BTN_HEIGHT) {
            show_credit = false;
            reset_credit_animation();
            page_no = 0; 
        }
    }
}
// Optional keyboard exit
void handle_credit_key(unsigned char key) {
    if (key == 27) { // ESC
        show_credit = false;
        reset_credit_animation();
    }
}

#endif 