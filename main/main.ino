#include "Player.h"
#include "ObstacleHandler.h"
#include <Gamebuino-Meta.h>

Player player;
ObstacleHandler obstacleHandler;

void setup()
{
    gb.begin();
    player = Player(3, 5);
    player.initialize();
    obstacleHandler.initializeHandler(&player);
}

void loop()
{
    while (!gb.update())
        ;
    gb.display.clear();
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
    // SI LE PLAYER A PERDU
    showDeathScreen();
}

void showDeathScreen()
{
    gb.display.println("Game OVER!");
    gb.display.print("Mode: ");
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
    }
}