#include "iGraphics.h"

#define LEVEL_COUNT 6
#define ROLLER_NO 3

#define ROLLER_FRAME_COUNT 8

// Roller obstacle structure
typedef struct {
    Image frames[ROLLER_FRAME_COUNT]; // 5 animation frames per roller
    Sprite sprite;
    int direction_x; // 1 for right, -1 for left
    int direction_y; // 1 for up, -1 for down
} Roller;

// Declare the roller array
Roller roller[ROLLER_NO];

// Paths to each roller's animation frames
const char* roller_frame_paths[ROLLER_NO][ROLLER_FRAME_COUNT] = {
    {
        "MazeExplorer/assests/obstacles/roller_01.png",
        "MazeExplorer/assests/obstacles/roller_02.png",
        "MazeExplorer/assests/obstacles/roller_03.png",
        "MazeExplorer/assests/obstacles/roller_04.png",
        "MazeExplorer/assests/obstacles/roller_05.png",
        "MazeExplorer/assests/obstacles/roller_06.png",
        "MazeExplorer/assests/obstacles/roller_07.png",
        "MazeExplorer/assests/obstacles/roller_08.png"
        
        
    },
    {
        "MazeExplorer/assests/obstacles/roller_01.png",
        "MazeExplorer/assests/obstacles/roller_02.png",
        "MazeExplorer/assests/obstacles/roller_03.png",
        "MazeExplorer/assests/obstacles/roller_04.png",
        "MazeExplorer/assests/obstacles/roller_05.png",
        "MazeExplorer/assests/obstacles/roller_06.png",
        "MazeExplorer/assests/obstacles/roller_07.png",
        "MazeExplorer/assests/obstacles/roller_08.png"
        
    },
    {
        "MazeExplorer/assests/obstacles/roller_01.png",
        "MazeExplorer/assests/obstacles/roller_02.png",
        "MazeExplorer/assests/obstacles/roller_03.png",
        "MazeExplorer/assests/obstacles/roller_04.png",
        "MazeExplorer/assests/obstacles/roller_05.png",
        "MazeExplorer/assests/obstacles/roller_06.png",
        "MazeExplorer/assests/obstacles/roller_07.png",
        "MazeExplorer/assests/obstacles/roller_08.png"
    }

    
    
};

// X and Y positions of rollers per level
int roller_x[LEVEL_COUNT-2][ROLLER_NO] = {
 
    {1220, 1850, 2640},
    {-1200, -250,  -60},
    {-1150,-1490, 940},
    {110, 940, 230}
};

int roller_y[LEVEL_COUNT][ROLLER_NO] = {
    
    {680, 1855, 3550},
    {500, 1700, 800},
    {815, 2300, 1280},
    {1920, 740, 3800}
};

// Function to load frames and initialize rollers for a level
void loadRollerObstacles(int level) {
    for (int i = 0; i < ROLLER_NO; i++) {
        // Load 5 frames for each roller
        for (int j = 0; j < ROLLER_FRAME_COUNT; j++) {
            iLoadImage(&roller[i].frames[j], roller_frame_paths[i][j]);
        }

        // Initialize sprite
        iInitSprite(&roller[i].sprite, ROLLER_FRAME_COUNT);
        iChangeSpriteFrames(&roller[i].sprite, roller[i].frames, ROLLER_FRAME_COUNT);
        iSetSpritePosition(&roller[i].sprite, roller_x[level - 3][i], roller_y[level - 3][i]);
        iScaleSprite(&roller[i].sprite, 1.5); // Optional scale
       // iPlaySprite(&roller[i].sprite);       // Start animation
    }
}

// Function to draw rollers on screen
void drawRollerObstacles(int cam_x, int cam_y, int level) {
    for (int i = 0; i < ROLLER_NO; i++) {
        iSetSpritePosition(&roller[i].sprite,
            roller_x[level - 3][i] + cam_x,
            roller_y[level - 3][i] + cam_y);
        iShowSprite(&roller[i].sprite);
    }
}

// Function to animate all rollers 
void animateRollerObstacles() {
    for (int i = 0; i < ROLLER_NO; i++) {
        iAnimateSprite(&roller[i].sprite);
    }

}