#pragma once

struct GameOptions
{
    int speed;
    int windowHeight;
    int gameMode = 0; //defaults to TITLE_SCREEN (4) upon creation
};

enum class MODE
{
    IN_GAME,
    DEATH_SCREEN
};
