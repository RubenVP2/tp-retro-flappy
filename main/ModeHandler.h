#ifndef _MAINMENU_h
#define _MAINMENU_h

#include "Globals.h"
#include "Player.h"
#include "ObstacleHandler.h"

// Classe qui permet de gérer l'ihm ( écran de jeu / écran de mort / ...)
class ModeHandler
{

public:
    ModeHandler();
    void showInGame();
    void showDeathScreen();
    void initScore();

    MODE getMode();
    int8_t getSpeed();
    int8_t getWindowHeight();

    void setMode(MODE newMode);
    void setSpeed(int8_t newSpeed);
    void setWindowHeight(int8_t newHeight);

private:
    GameOptions currentOptions;

    Player player;
    ObstacleHandler obstacleHandler;

    int8_t speedSelectorPositionX = 6;
    int8_t windowHeightSelectorPositionX = 39;

    int8_t topScores[8];
};

#endif
