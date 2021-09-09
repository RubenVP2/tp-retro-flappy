#pragma once

struct GameOptions
{
    int speed;
    int windowHeight;
    int gameMode = 0;
};

enum class MODE
{
    IN_GAME,
    DEATH_SCREEN
};
