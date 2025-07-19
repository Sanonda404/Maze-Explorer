#include "iGraphics.h"

#define Level_COUNT 6
#define Explosion_NO 2

#define LEVEL6_OBSTACLE_COUNT 6

#define  SPIKEFRAME_COUNT 1 


#define EXPLOSION_FRAME_COUNT 10


// Roller obstacle structure
typedef struct {
    Image frames[EXPLOSION_FRAME_COUNT]; // 5 animation frames per roller
    Sprite sprite;
    int direction_x; // 1 for right, -1 for left
    int direction_y; // 1 for up, -1 for down
} Explosion;

// Declare the roller array
Explosion explosion[Explosion_NO];
Explosion level6_obstacles[LEVEL6_OBSTACLE_COUNT];

// Paths to each roller's animation frames
const char* explosion_frame_paths[Explosion_NO][EXPLOSION_FRAME_COUNT] = {
    {
        "MazeExplorer/assests/obstacles/Explosion_1.png",
        "MazeExplorer/assests/obstacles/Explosion_2.png",
        "MazeExplorer/assests/obstacles/Explosion_3.png",
        "MazeExplorer/assests/obstacles/Explosion_4.png",
        "MazeExplorer/assests/obstacles/Explosion_5.png",
        "MazeExplorer/assests/obstacles/Explosion_6.png",
        "MazeExplorer/assests/obstacles/Explosion_7.png",
        "MazeExplorer/assests/obstacles/Explosion_8.png",
        "MazeExplorer/assests/obstacles/Explosion_9.png",
       "MazeExplorer/assests/obstacles/Explosion_10.png"
        
        
    },
    {
       
        "MazeExplorer/assests/obstacles/Explosion_1.png",
        "MazeExplorer/assests/obstacles/Explosion_2.png",
       "MazeExplorer/assests/obstacles/Explosion_3.png",
        "MazeExplorer/assests/obstacles/Explosion_4.png",
        "MazeExplorer/assests/obstacles/Explosion_5.png",
        "MazeExplorer/assests/obstacles/Explosion_6.png",
        "MazeExplorer/assests/obstacles/Explosion_7.png",
        "MazeExplorer/assests/obstacles/Explosion_8.png",
        "MazeExplorer/assests/obstacles/Explosion_9.png",
       "MazeExplorer/assests/obstacles/Explosion_10.png"
        
    }
    

    
    
};
int level6_obstacle_x[Level_COUNT-5][LEVEL6_OBSTACLE_COUNT] = {{-700,-500,700,220,320,500}};
int level6_obstacle_y[Level_COUNT-5][LEVEL6_OBSTACLE_COUNT]= {{1200,1400,1550,2500,2755,3935}};
    

const char* level6_obstacle_paths[LEVEL6_OBSTACLE_COUNT] = {
    
    "MazeExplorer/assests/obstacles/Silver_blade.png",
    "MazeExplorer/assests/obstacles/Silver_blade.png",
    "MazeExplorer/assests/obstacles/Silver_blade.png",
    "MazeExplorer/assests/obstacles/Silver_blade.png",
     "MazeExplorer/assests/obstacles/Green_spine.png",
    "MazeExplorer/assests/obstacles/Green_spine.png"
    
    
    
};


// X and Y positions of rollers per level
int explosion_x[Level_COUNT-4][Explosion_NO] = {
 
    {-1400, -800},
    {420, 150 }
    
};

int explosion_y[Level_COUNT-4][Explosion_NO] = {
    
    {460, 2300},
    {3480, 1185}
    
};


// Function to load frames and initialize rollers for a level
void loadExplosionObstacles(int level) {
    for (int i = 0; i < Explosion_NO; i++) {
        // Load 5 frames for each roller
        for (int j = 0; j < EXPLOSION_FRAME_COUNT; j++) {
            iLoadImage(&explosion[i].frames[j],explosion_frame_paths[i][j]);
        }

        // Initialize sprite
        iInitSprite(&explosion[i].sprite, EXPLOSION_FRAME_COUNT);
        iChangeSpriteFrames(&explosion[i].sprite, explosion[i].frames, EXPLOSION_FRAME_COUNT);
        iSetSpritePosition(&explosion[i].sprite, explosion_x[level - 5][i], explosion_y[level - 5][i]);
        iScaleSprite(&explosion[i].sprite, 1.5); // Optional scale
       // iPlaySprite(&roller[i].sprite);       // Start animation
    }
    for (int i = 0; i < LEVEL6_OBSTACLE_COUNT; i++) {
        iLoadImage(&level6_obstacles[i].frames[0], level6_obstacle_paths[i]);

        iInitSprite(&level6_obstacles[i].sprite, 5);
        iChangeSpriteFrames(&level6_obstacles[i].sprite, level6_obstacles[i].frames, SPIKEFRAME_COUNT);
        iSetSpritePosition(&level6_obstacles[i].sprite, level6_obstacle_x[level-6][i], level6_obstacle_y[level-6][i]);
        iScaleSprite(&level6_obstacles[i].sprite, 1.5); // Adjust size if needed
   }
    
}

// Function to draw rollers on screen
void drawExplosionObstacles(int cam_x, int cam_y, int level) {
    for (int i = 0; i <Explosion_NO; i++) {
        iSetSpritePosition(&explosion[i].sprite,
            explosion_x[level - 5][i] + cam_x,
            explosion_y[level - 5][i] + cam_y);
        iShowSprite(&explosion[i].sprite);
    }
    
   if(level==6){for (int i = 0; i < LEVEL6_OBSTACLE_COUNT; i++) {
        iSetSpritePosition(&level6_obstacles[i].sprite, level6_obstacle_x[level-6][i] + cam_x, level6_obstacle_y[level-6][i] + cam_y);
        iShowSprite(&level6_obstacles[i].sprite);
    
    

}}}


    


// Function to animate all rollers 
void animateExplosionObstacles() {
    for (int i = 0; i < Explosion_NO; i++) {
        iAnimateSprite(&explosion[i].sprite);
    }
  
}