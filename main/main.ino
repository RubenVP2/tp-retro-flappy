#include "Player.h"
#include "ObstacleHandler.h"
#include "ModeHandler.h"
#include <Gamebuino-Meta.h>

ModeHandler modeHandler;

// Phase de setup du jeu
void setup()
{
    gb.begin();
    modeHandler.initScore();
}

void loop()
{
    while (!gb.update())
        ;
    gb.display.clear();
    // Mode par défaut = écran de jeu
    switch (modeHandler.getMode())
    {
    // Démarre le jeu
    case MODE::IN_GAME:
        modeHandler.showInGame();
        break;
    // Montre l'écran de mort
    case MODE::DEATH_SCREEN:
        modeHandler.showDeathScreen();
        break;
    }
}
