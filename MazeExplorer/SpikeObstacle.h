#include "iGraphics.h"


#define OBSTACLE_COUNT 4
//#define LEVEL6_OBSTACLE_COUNT 6
#define LEVEL_COUNT 6
#define  SPIKEFRAME_COUNT 1 

typedef struct {
    Sprite sprite;
    Image frames[SPIKEFRAME_COUNT];
    int x, y;
} Obstacle;

Obstacle obstacles[OBSTACLE_COUNT];
//Obstacle level6_obstacles[LEVEL6_OBSTACLE_COUNT];

const char* obstacle_paths[OBSTACLE_COUNT] = {
    "MazeExplorer/assests/obstacles/BlueGlossySpike.png",
    "MazeExplorer/assests/obstacles/PurpleSpike.png",
    "MazeExplorer/assests/obstacles/BlueGlossySpike.png",
    "MazeExplorer/assests/obstacles/PurpleSpike.png"
};
/*const char* level6_obstacle_paths[LEVEL6_OBSTACLE_COUNT] = {
    
    "MazeExplorer/assests/obstacles/Silver_blade.png",
    "MazeExplorer/assests/obstacles/Silver_blade.png",
    "MazeExplorer/assests/obstacles/Silver_blade.png",
    "MazeExplorer/assests/obstacles/Silver_blade.png",
     "MazeExplorer/assests/obstacles/Green_spine.png",
    "MazeExplorer/assests/obstacles/Green_spine.png"
    
    
    
};*/
int obstacle_x[LEVEL_COUNT][4] = {{1200,1450, 2250,2150},{1350,1950,2250,2550},{680,1300, 2500,1700},{-1000,-190, 370,-900},{-660,-70, -350,-750},{-200,-550, -250,800}};
int obstacle_y[LEVEL_COUNT][4]= {{500,900,1250, 1780},{300,900,1650,2200},{2475,1200,1970, 2385},{1800,9,1500, 1140},{1165,770,2500, 1900},{3390,3150,2100, 1180}};
/*int level6_obstacle_x[LEVEL_COUNT][LEVEL6_OBSTACLE_COUNT] = {{},{},{},{},{},{-700,-500,700,220,320,500}};
int level6_obstacle_y[LEVEL_COUNT][LEVEL6_OBSTACLE_COUNT]= {{},{},{},{},{},{1200,1400,1550,2500,2755,3935}};*/
    
void loadSpikeObstacles(int level) {
    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        iLoadImage(&obstacles[i].frames[0], obstacle_paths[i]);

        iInitSprite(&obstacles[i].sprite, 5);
        iChangeSpriteFrames(&obstacles[i].sprite, obstacles[i].frames, SPIKEFRAME_COUNT);
        iSetSpritePosition(&obstacles[i].sprite, obstacle_x[level-1][i], obstacle_y[level-1][i]);
        iScaleSprite(&obstacles[i].sprite, 1.5); // Adjust size if needed
    }
 /*if(level==6) {for (int i = 0; i < LEVEL6_OBSTACLE_COUNT; i++) {
        iLoadImage(&level6_obstacles[i].frames[0], level6_obstacle_paths[i]);

        iInitSprite(&level6_obstacles[i].sprite, 5);
        iChangeSpriteFrames(&level6_obstacles[i].sprite, level6_obstacles[i].frames, SPIKEFRAME_COUNT);
        iSetSpritePosition(&level6_obstacles[i].sprite, level6_obstacle_x[level-6][i], level6_obstacle_y[level-6][i]);
        iScaleSprite(&level6_obstacles[i].sprite, 1.5); // Adjust size if needed
   }}*/
   }



void draw_SpikeObstacles(int cam_x, int cam_y,int level) {
    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        iSetSpritePosition(&obstacles[i].sprite, obstacle_x[level-1][i] + cam_x, obstacle_y[level-1][i] + cam_y);
        iShowSprite(&obstacles[i].sprite);
    }
  /*if(level==6){for (int i = 0; i < LEVEL6_OBSTACLE_COUNT; i++) {
        iSetSpritePosition(&level6_obstacles[i].sprite, level6_obstacle_x[level-6][i] + cam_x, level6_obstacle_y[level-6][i] + cam_y);
        iShowSprite(&level6_obstacles[i].sprite);
    
    

}}*/}


void animate_SpikeObstacles() {
    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        iAnimateSprite(&obstacles[i].sprite);
    }
}
