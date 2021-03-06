//
//
//

#include "Obstacle.h"

Obstacle::Obstacle() {}

Obstacle::Obstacle(int16_t windowY)
{
    resetRectangles(windowY);
}

Obstacle::Obstacle(int16_t windowY, int8_t windowHeight, int8_t scrollSpeed)
{
    this->windowHeight = windowHeight;
    this->obstacleScrollSpeed = scrollSpeed;
    resetRectangles(windowY);
}

void Obstacle::moveObstacle()
{
    topRectangle.x += obstacleScrollSpeed;
    bottomRectangle.x += obstacleScrollSpeed;
}

void Obstacle::drawObstacle() const
{
    gb.display.fillRect(topRectangle.x, topRectangle.y, topRectangle.w, topRectangle.l);
    gb.display.fillRect(bottomRectangle.x, bottomRectangle.y, bottomRectangle.w, bottomRectangle.l + (bottomRectangle.y - topRectangle.y));
}

void Obstacle::resetObstacle(int8_t previousWindowY)
{
    int8_t upperOffset;
    int8_t lowerOffset;

    if (previousWindowY > gb.display.height() - 20)
    {
        lowerOffset = -25;
        upperOffset = -10;
    }
    else if (previousWindowY < 20)
    {
        lowerOffset = 10;
        upperOffset = 25;
    }
    else
    {
        lowerOffset = -15;
        upperOffset = 15;
    }

    resetRectangles(previousWindowY + random(lowerOffset, upperOffset));
}

void Obstacle::setObstacleX(int16_t newX)
{
    topRectangle.x = newX;
    bottomRectangle.x = newX;
}

void Obstacle::setWindowHeight(int8_t newWindowHeight)
{
    windowHeight = newWindowHeight;
}

void Obstacle::changeScrollSpeed(int8_t newScrollSpeed)
{
    if (newScrollSpeed < 0 && newScrollSpeed > -3)
        obstacleScrollSpeed = newScrollSpeed;
}

int8_t Obstacle::getScrollSpeed()
{
    return obstacleScrollSpeed;
}

int16_t Obstacle::getObstacleX() const
{
    return topRectangle.x;
}

int16_t Obstacle::getObstacleTopY() const
{
    return topRectangle.y;
}

int16_t Obstacle::getObstacleBottomY() const
{
    return bottomRectangle.y;
}

int16_t Obstacle::getObstacleWindowY() const
{
    return bottomRectangle.y - windowHeight / 2;
}

void Obstacle::setObstacleWindowY(int8_t newWindowY)
{
    previousWindowY = newWindowY;
}

int16_t Obstacle::getWidth() const
{
    return topRectangle.w;
}

int16_t Obstacle::getTopHeight() const
{
    return topRectangle.l;
}

int16_t Obstacle::getBottomHeight() const
{
    return bottomRectangle.l;
}

int16_t Obstacle::getWindowHeight() const
{
    return windowHeight;
}

void Obstacle::resetRectangles(int16_t previousWindowY)
{
    // Nb d'obstacles par ??cran * distance entre chaque en pixel
    topRectangle.x = 4 * 35; //4 (amount of obstacles) * 35 (distance between each in pixels)
    topRectangle.y = 0;
    topRectangle.l = previousWindowY - windowHeight / 2;

    // Correction de bug : si le rectangle du haut est trop proche de la sortie du screen
    if (topRectangle.l < 0)
    {
        topRectangle.l = 7;
    }
    // reset la taille du rectangle du haut si celui-ci est trop grand (d??passe l'ihm)
    else if (topRectangle.l > gb.display.height() - windowHeight - 3)
    {
        topRectangle.l = gb.display.height() - windowHeight - 7;
    }

    bottomRectangle.x = topRectangle.x;
    bottomRectangle.y = topRectangle.l + windowHeight;
    bottomRectangle.l = gb.display.height() - bottomRectangle.y - 5;
}
