// ObstacleHandler.h
#ifndef _OBSTACLEHANDLER_h
#define _OBSTACLEHANDLER_h

#include "Obstacle.h"
#include "Player.h"

class ObstacleHandler
{
public:
    void initializeHandler(Player *player);
    void resetObstacles();
    void resetObstacles(int8_t scrolLSpeed, int8_t windowHeight);
    void drawObstacles() const;
    void moveObstacles();
    void setScrollSpeed(int8_t newScrollSpeed);
    int8_t getScrollSpeed();

    bool checkCollision() const;

    void setWindowHeight(int8_t newWindowHight);

private:
    Obstacle obstacles[4];
    int16_t obstacleX = 0;
    int16_t NUM_OF_OBSTACLES = 4;
    int16_t SPACE_BETWEEN_OBSTACLES = 36;
    Player *player = nullptr;
};

#endif