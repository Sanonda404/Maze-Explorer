#ifndef LEVEL_COMPLETED_H
#define LEVEL_COMPLETED_H

#include "iGraphics.h"
#include "iFont.h"
#include <cstring>

#define SCREEN_W 1400
#define SCREEN_H 800
#define BTN_WIDTH 240
#define BTN_HEIGHT 70

// Typing Animation
char typing_texts[3][100] = {
    "Level Completed!",
    "",
    ""
};

int reveal_index = 0;

int typing_index = 0;
int typing_char_index = 0;
bool typing_done = false;

// Score Data
int show_score = 0;
int show_highscore = 0;
int completed_level = 1;

// Button Setup
const char *button_texts[4] = {"Next", "Menu", "Highscores", "Exit"};
int button_visible[4] = {0, 0, 0, 0};  // 0 = hidden, 1 = visible
float button_hover_scale[4] = {1, 1, 1, 1};
int button_y_start = 350;
int button_gap = 90;

// Fonts
const char *font_main = "MazeExplorer/assests/fonts/DynaPuff-Medium.ttf";
const char *font_score = "MazeExplorer/assests/fonts/Poppins-Regular.ttf";
const char *font_button2 = "MazeExplorer/assests/fonts/Roboto-Bold.ttf";


// Reset Function
void start_level_complete_screen(int score, int highscore, int lvl) {
    typing_index = 0;
    typing_char_index = 0;
    typing_done = false;
    show_score = score;
    show_highscore = highscore;
    completed_level = lvl;

    iSetColor(255, 100, 200);
    sprintf(typing_texts[1], "Score: %d", show_score);
    sprintf(typing_texts[2], "High Score: %d", show_highscore);

    // Reset button states
    for (int i = 0; i < 4; i++) button_visible[i] = 0;
    reveal_index = 0;

    // Change button[0] text if final level
    if (completed_level == 6) {
        button_texts[0] = "Play Again";
    } else {
        button_texts[0] = "Next";
    }
}

void load_level_complete_screen() {
    iLoadImage(&sign_bg, "MazeExplorer/assests/bg_purple.png");
}

// Drawing Logic
void draw_level_complete_screen() {
    iShowImage(0, 0, "MazeExplorer/assests/bg_purple.png");

    int center_x = SCREEN_W / 2;

    iSetColor(255, 255, 255);
    for (int i = 0; i < typing_index; i++) {
        if (i == 0)
            iShowText(center_x - 200, 600 - i * 60, typing_texts[i], font_main, 55);
        else
            iShowText(center_x - 150, 600 - i * 60, typing_texts[i], font_main, 42);
    }

    if (!typing_done) {
        char current_line[100];
        strncpy(current_line, typing_texts[typing_index], typing_char_index);
        current_line[typing_char_index] = '\0';

        if (typing_index == 0)
            iShowText(center_x - 200, 600 - typing_index * 60, current_line, font_main, 55);
        else
            iShowText(center_x - 150, 600 - typing_index * 60, current_line, font_main, 42);
    }

    for (int i = 0; i < 4; i++) {
        if (button_visible[i] != 1) continue;

        float scale = button_hover_scale[i];
        int btn_x = center_x - BTN_WIDTH / 2;
        int btn_y = button_y_start - i * button_gap;

        int w = BTN_WIDTH * scale;
        int h = BTN_HEIGHT * scale;
        int x = btn_x - (w - BTN_WIDTH) / 2;
        int y = btn_y - (h - BTN_HEIGHT) / 2;

        // Shadow
        iSetColor(30, 30, 30);
        iFilledRectangle(x + 4, y - 4, w, h);

        // Button Background
        int pink_r[4] = {255, 255, 255, 255};
        int pink_g[4] = {100, 130, 160, 190};
        int pink_b[4] = {180, 200, 220, 240};

        iSetColor(pink_r[i], pink_g[i], pink_b[i]);
        iFilledRectangle(x, y, w, h);

        // Shine
        iSetColor(255, 255, 255);
        iFilledRectangle(x, y, w, 3);

        // Border
        iSetColor(0, 0, 0);
        iRectangle(x, y, w, h);

        // Centered Text
        int text_w = strlen(button_texts[i]) * 10 * scale;
        int text_h = 28 * scale;
        int text_x = x + (w - text_w) / 2;
        int text_y = y + (h - text_h) / 2;

        // Outline
        iSetColor(0, 0, 0);
        iShowText(text_x + 2, text_y, button_texts[i], font_button2, 28 * scale);
        iShowText(text_x - 2, text_y, button_texts[i], font_button2, 28 * scale);
        iShowText(text_x, text_y + 2, button_texts[i], font_button2, 28 * scale);
        iShowText(text_x, text_y - 2, button_texts[i], font_button2, 28 * scale);

        // Foreground
        iSetColor(255, 255, 255);
        iShowText(text_x, text_y, button_texts[i], font_button2, 28 * scale);
    }
}

// Click Detection
int level_complete_mouse_click(int mx, int my) {
    if (!typing_done) return -1;
    int cx = SCREEN_W / 2 - BTN_WIDTH / 2;

    for (int i = 0; i < 4; i++) {
        if (button_visible[i] != 1) continue;
        int bx = cx;
        int by = button_y_start - i * button_gap;
        if (mx >= bx && mx <= bx + BTN_WIDTH &&
            my >= by && my <= by + BTN_HEIGHT) {
            return i; // Index of clicked button
        }
    }
    return -1;
}

// Hover Detection
void level_complete_mouse_move(int mx, int my) {
    if (!typing_done) return;
    int cx = SCREEN_W / 2 - BTN_WIDTH / 2;

    for (int i = 0; i < 4; i++) {
        if (button_visible[i] != 1) continue;
        int bx = cx;
        int by = button_y_start - i * button_gap;
        if (mx >= bx && mx <= bx + BTN_WIDTH &&
            my >= by && my <= by + BTN_HEIGHT) {
            button_hover_scale[i] = 1.1;
        } else {
            button_hover_scale[i] = 1.0;
        }
    }
}

// Typing animation: Call every 30–50ms
void update_typing_animation() {
    if (typing_done) return;

    if (typing_char_index < strlen(typing_texts[typing_index])) {
        typing_char_index++;
    } else {
        typing_index++;
        typing_char_index = 0;
        if (typing_index >= 3) {
            typing_done = true;
        }
    }
}

// Reveal Buttons Gradually: Call every 150–200ms
void reveal_buttons_step() {
    if (typing_done && reveal_index < 4) {
        button_visible[reveal_index++] = 1;
    }
}

#endif
