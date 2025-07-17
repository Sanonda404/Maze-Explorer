#ifndef SLIME_H
#define SLIME_H

#include "iGraphics.h"
#include <string.h>

#define SLIME_NO 2
#define FRAME_COUNT 4

typedef struct {
    Image* frames;           // Pointer to current animation frames
    Sprite sprite;
    char direction[10];      // "up", "down", "left", "right"
    int isAlive;
    int isDying;
    int currentFrame;
    bool flipped;
} Slime;

Slime slimes[SLIME_NO];
int slime_x[SLIME_NO] = {2035, 1600};
int slime_y[SLIME_NO] = {400, 1135};

// Loaded animations
Image slime_walk_up[FRAME_COUNT];
Image slime_walk_down[FRAME_COUNT];
Image slime_walk_right[FRAME_COUNT];
Image slime_die_right[FRAME_COUNT];

int slime_time = 0;

void loadSlimeSheets() {
    iLoadFramesFromSheet(slime_walk_up, "MazeExplorer/assests/monsters/slime1/04_LargeSlime_Purple.png", 1, FRAME_COUNT);
    iLoadFramesFromSheet(slime_walk_down, "MazeExplorer/assests/monsters/slime1/02_LargeSlime_Purple.png", 1, FRAME_COUNT);
    iLoadFramesFromSheet(slime_walk_right, "MazeExplorer/assests/monsters/slime1/00_LargeSlime_Purple.png", 1, FRAME_COUNT);
    iLoadFramesFromSheet(slime_die_right, "MazeExplorer/assests/monsters/slime1/01_LargeSlime_Purple.png", 1, FRAME_COUNT);
}

void assignSlimeFrames(int i) {
    Slime* s = &slimes[i];

    if (s->isDying) {
        s->frames = slime_die_right;
        s->flipped = (strcmp(s->direction, "left") == 0);
    } else if (strcmp(s->direction, "up") == 0) {
        s->frames = slime_walk_up;
        s->flipped = false;
    } else if (strcmp(s->direction, "down") == 0) {
        s->frames = slime_walk_down;
        s->flipped = false;
    } else if (strcmp(s->direction, "right") == 0) {
        s->frames = slime_walk_right;
        s->flipped = false;
    } else if (strcmp(s->direction, "left") == 0) {
        s->frames = slime_walk_right; // mirror right
        s->flipped = true;
    }

    iChangeSpriteFrames(&s->sprite, &s->frames[0], 1);
    iMirrorSprite(&s->sprite, HORIZONTAL);
    s->currentFrame = 0;
}

void loadSlimes() {
    loadSlimeSheets();

    for (int i = 0; i < SLIME_NO; i++) {
        iInitSprite(&slimes[i].sprite, -1);
        strcpy(slimes[i].direction, "down");
        slimes[i].isAlive = 1;
        slimes[i].isDying = 0;
        assignSlimeFrames(i);
        iSetSpritePosition(&slimes[i].sprite, slime_x[i], slime_y[i]);
        iScaleSprite(&slimes[i].sprite, 0.5);
    }
}

void animateSlimes() {
    for (int i = 0; i < SLIME_NO; i++) {
        if (!slimes[i].isAlive && !slimes[i].isDying) continue;

        slimes[i].currentFrame = (slimes[i].currentFrame + 1) % FRAME_COUNT;
        iChangeSpriteFrames(&slimes[i].sprite, &slimes[i].frames[slimes[i].currentFrame], 1);
        iMirrorSprite(&slimes[i].sprite, HORIZONTAL);
    }
}

void drawSlimes(int offset_x, int offset_y) {
    for (int i = 0; i < SLIME_NO; i++) {
        if (slimes[i].isAlive || slimes[i].isDying) {
            iSetSpritePosition(&slimes[i].sprite, slime_x[i] + offset_x, slime_y[i] + offset_y);
            iShowSprite(&slimes[i].sprite);
        }
    }
}

void moveSlimesToward(int player_x, int player_y) {
    for (int i = 0; i < SLIME_NO; i++) {
        if (!slimes[i].isAlive || slimes[i].isDying) continue;

        int dx = 0, dy = 0;
        int sx = slimes[i].sprite.x;
        int sy = slimes[i].sprite.y;

        if (abs(sx - player_x) > abs(sy - player_y)) {
            if (sx < player_x) dx = 2, strcpy(slimes[i].direction, "right");
            else if (sx > player_x) dx = -2, strcpy(slimes[i].direction, "left");
        } else {
            if (sy < player_y) dy = 2, strcpy(slimes[i].direction, "up");
            else if (sy > player_y) dy = -2, strcpy(slimes[i].direction, "down");
        }

        slime_x[i] += dx;
        slime_y[i] += dy;

        assignSlimeFrames(i);
    }
}

void killSlime(int i) {
    slimes[i].isDying = 1;
    slimes[i].isAlive = 0;
    assignSlimeFrames(i);
    iAnimateSprite(&slimes[i].sprite);
}

void reset_slimes()
{
    for(int i=0; i<SLIME_NO; i++){
        slimes[i].isAlive = 1;
    }
}

#endif
