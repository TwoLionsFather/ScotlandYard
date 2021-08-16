#pragma once

#include "Map.hpp"
#include "VirtualMap.hpp"
#include "Player_mrx.hpp"
#include "Bot_sly.hpp"
#include <iostream>

namespace tlk
{
    enum State {WON_MRX, WON_SLY, MOVE_MRX, MOVE_SLY, ERROR};

    class Game
    {
    public:
        Game();
        ~Game();

        void setup();
        void play();

    private: 
        const Map  gameMap;
        VirtualMap vMap;

        Entity* const mrx;
        std::vector<Entity*> sly_units;

        unsigned int round = 0;
        State gameState;

        void printRoundStart();
    };
}