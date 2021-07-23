//
//
//

#include "ModeHandler.h"

ModeHandler::ModeHandler()
{
    currentOptions.gameMode = 0;
    player = Player(3, 5);
    player.initialize();
    obstacleHandler.initializeHandler(&player);
    currentOptions.speed = -1;
    currentOptions.windowHeight = 24;
}

void ModeHandler::showInGame()
{
    int16_t mapBaseDisplayCounter = 0;
    int16_t mapBGDisplayCounter = 0;

    while (player.isPlayerAlive())
    {
        while (!gb.update())
            ;
        gb.display.clear();

        player.updatePlayer();
        player.drawPlayer();

        obstacleHandler.drawObstacles();
        obstacleHandler.moveObstacles();

        gb.display.setColor(BLACK);
        gb.display.fillRect(-1, -1, player.getScore() >= 10 ? 10 : 6, 7);
        gb.display.setColor(WHITE);
        gb.display.drawRect(-1, -1, player.getScore() >= 10 ? 10 : 6, 8);
        gb.display.print(player.getScore());

        if (obstacleHandler.checkCollision() || player.checkOutOfBounds()) //if player hits an obstacle or goes out of bounds
        {
            player.changePlayerState(false);

            float playerX = player.getX();

            while (true) //continue moving thr player to display a death animation
            {
                while (!gb.update())
                    ;
                gb.display.clear();

                obstacleHandler.drawObstacles();
                player.updatePlayer();
                player.setX(playerX++);

                if (player.getY() > gb.display.width())
                {
                    return;
                }
            }
        }
    }

    this->setMode(MODE::DEATH_SCREEN);
    obstacleHandler.resetObstacles(this->getSpeed(), this->getWindowHeight());
}

void ModeHandler::showDeathScreen()
{
    gb.display.println("Game OVER!");
    gb.display.println("Your score: ");
    gb.display.setFontSize(2);
    gb.display.print("      ");
    gb.display.setColor(YELLOW);
    gb.display.println(player.getScore());

    gb.display.setFontSize(1);
    gb.display.setColor(YELLOW);
    gb.display.println("Press 'B' to Restart");

    if (gb.buttons.pressed(BUTTON_B))
    {
        player.initialize();
        this->setMode(MODE::IN_GAME);
    }
}

void ModeHandler::initScore()
{
    for (int i = 0; i < 8; i++)
    {
        topScores[i] = gb.save.get(i);
    }
}
MODE ModeHandler::getMode()
{
    switch (currentOptions.gameMode)
    {
    case 0:
        return MODE::IN_GAME;
        break;
    case 1:
        return MODE::DEATH_SCREEN;
        break;
    }
}

int8_t ModeHandler::getSpeed()
{
    return currentOptions.speed;
}

int8_t ModeHandler::getWindowHeight()
{
    return currentOptions.windowHeight;
}

void ModeHandler::setMode(MODE newMode)
{
    switch (newMode)
    {
    case MODE::IN_GAME:
        currentOptions.gameMode = 0;
        break;
    case MODE::DEATH_SCREEN:
        currentOptions.gameMode = 1;
        break;
    }
}

void ModeHandler::setSpeed(int8_t newSpeed)
{
    currentOptions.speed = newSpeed;
}

void ModeHandler::setWindowHeight(int8_t newHeight)
{
    currentOptions.windowHeight = newHeight;
}
