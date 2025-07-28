#include "iGraphics.h"


#define OBSTACLE_COUNT 4
#define LEVEL_COUNT 6
#define  SPIKEFRAME_COUNT 1 

typedef struct {
    Sprite sprite;
    Image frames[SPIKEFRAME_COUNT];
    int x, y;
} Obstacle;

Obstacle obstacles[OBSTACLE_COUNT];


const char* obstacle_paths[OBSTACLE_COUNT] = {
    "MazeExplorer/assests/obstacles/BlueGlossySpike.png",
    "MazeExplorer/assests/obstacles/PurpleSpike.png",
    "MazeExplorer/assests/obstacles/BlueGlossySpike.png",
    "MazeExplorer/assests/obstacles/PurpleSpike.png"
};

int obstacle_x[LEVEL_COUNT][4] = {{1150,1450, 2220,2130},{1350,1770,2180,2540},{720,1170, 2580,1580},{-970,-190, 420,-900},{850,350,-350,-455},{-200,-450,-350,760}};
int obstacle_y[LEVEL_COUNT][4]= {{550,960,1270, 1780},{300,900,1600,2240},{2510,1230,1920, 2480},{1830,29,1660, 1170},{620,2410,2500,330},{3450,2800,2100,1280}};

void loadSpikeObstacles(int level) {
    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        iLoadImage(&obstacles[i].frames[0], obstacle_paths[i]);

        iInitSprite(&obstacles[i].sprite);
        iChangeSpriteFrames(&obstacles[i].sprite, obstacles[i].frames, SPIKEFRAME_COUNT);
        iSetSpritePosition(&obstacles[i].sprite, obstacle_x[level-1][i], obstacle_y[level-1][i]);
        iScaleSprite(&obstacles[i].sprite, 1.5); // Adjust size 
    }
 
   }



void draw_SpikeObstacles(int cam_x, int cam_y,int level) {
    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        iSetSpritePosition(&obstacles[i].sprite, obstacle_x[level-1][i] + cam_x, obstacle_y[level-1][i] + cam_y);
        iShowSprite(&obstacles[i].sprite);
    }
  
    

}
