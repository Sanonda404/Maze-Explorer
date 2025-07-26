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
int obstacle_x[LEVEL_COUNT][4] = {{1150,1450, 2220,2130},{1350,1770,2180,2540},{720,1170, 2580,1580},{-970,-190, 420,-900},{-660,-70, -350,-500},{-200,-450, -350,760}};
int obstacle_y[LEVEL_COUNT][4]= {{550,960,1270, 1780},{300,900,1600,2240},{2510,1230,1920, 2480},{1830,29,1660, 1170},{1165,870,2500,1960},{3450,2800,2100, 1280}};
/*int level6_obstacle_x[LEVEL_COUNT][LEVEL6_OBSTACLE_COUNT] = {{},{},{},{},{},{-700,-500,700,220,320,500}};
int level6_obstacle_y[LEVEL_COUNT][LEVEL6_OBSTACLE_COUNT]= {{},{},{},{},{},{1200,1400,1550,2500,2755,3935}};*/
    
void loadSpikeObstacles(int level) {
    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        iLoadImage(&obstacles[i].frames[0], obstacle_paths[i]);

        iInitSprite(&obstacles[i].sprite);
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